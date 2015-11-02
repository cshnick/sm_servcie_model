#ifndef INCLUDE_COMMON_MACOSX_FILEWATCHER_H_
#define INCLUDE_COMMON_MACOSX_FILEWATCHER_H_

#include <functional>
#include <CoreServices/CoreServices.h>
#include <pthread.h>
#include <atomic>
#include <future>
#include "sys/stat.h"

#include "core/exceptions.h"


namespace sm {
    BOSS_DECLARE_RUNTIME_EXCEPTION(FileWatcher)
    
    namespace Private {
        
        class FileWatcherImpl {
        public:
            
            FileWatcherImpl(const FileWatcherImpl&) = delete;
            FileWatcherImpl& operator=(const FileWatcherImpl&) = delete;
            FileWatcherImpl() = delete;
            
            FileWatcherImpl(const std::string &file_name, const std::function<void(std::string, int)> &f) : m_filename(file_name), m_func(f), m_flag(0) {
                if (m_filename.empty()) {
                    throw FileWatcherException("Filename is empty");
                }
                makeDirName(m_filename);
                CFStringRef arg = CFStringCreateWithCString(
                                                            kCFAllocatorDefault,
                                                            m_filename.c_str(),
                                                            kCFStringEncodingUTF8);
                CFArrayRef paths = CFArrayCreate(NULL, (const void**)&arg, 1, NULL);
                CFAbsoluteTime latency = 3.0;
                
                FSEventStreamContext * streamContext = (FSEventStreamContext *)malloc(sizeof(FSEventStreamContext));
                streamContext->version = 0;
                streamContext->info = this;//&fileDescriptor;
                streamContext->retain = NULL;
                streamContext->release = NULL;
                streamContext->copyDescription = NULL;
                
                m_stream = FSEventStreamCreate(
                                               NULL,
                                               &FileWatcherImpl::callback,
                                               streamContext,
                                               paths,
                                               kFSEventStreamEventIdSinceNow,
                                               latency,
                                               kFSEventStreamCreateFlagFileEvents);
                
                pthread_mutex_init(&m_mutex, nullptr);
                pthread_cond_init(&m_initiated, nullptr);
                pthread_create(&m_thread, nullptr, &FileWatcherImpl::thread_func, (void*)this);
                
                pthread_mutex_lock(&m_mutex);
                while (!m_flag) {
                    pthread_cond_wait(&m_initiated, &m_mutex);
                }
                pthread_mutex_unlock(&m_mutex);
            }
            ~FileWatcherImpl() {
                stop();
                m_flag = 3;
                pthread_mutex_lock(&m_mutex);
                CFRunLoopStop(m_runloop);
                FSEventStreamInvalidate(m_stream);
                FSEventStreamRelease(m_stream);
                pthread_mutex_unlock(&m_mutex);
                pthread_join(m_thread, 0);
                pthread_detach(m_thread);
                pthread_mutex_destroy(&m_mutex);
                pthread_cond_destroy(&m_initiated);
            }
            void start() {
                pthread_mutex_lock(&m_mutex);
                FSEventStreamStart(m_stream);
                pthread_mutex_unlock(&m_mutex);
                m_flag = 1;
                
                std::cout << "Started" << std::endl;
            }
            void stop() {
                m_flag = 0;
                pthread_mutex_lock(&m_mutex);
                FSEventStreamStop(m_stream);
                pthread_mutex_unlock(&m_mutex);
                std::cout << "Stopped watcher" << std::endl;
            }
            
        private:
            std::string m_filename;
            std::function<void(std::string, int)> m_func;
            FSEventStreamRef m_stream = nullptr;
            CFRunLoopRef m_runloop = nullptr;
            
            std::atomic_int m_flag; //0 - init, 1 - idle, 2 - run, 3 - destroy
            pthread_t m_thread;
            pthread_mutex_t m_mutex;
            pthread_cond_t m_initiated;
            
        private:
            static void callback(
                                 ConstFSEventStreamRef stream,
                                 void *callbackInfo,
                                 size_t numEvents,
                                 void *evPaths,
                                 const FSEventStreamEventFlags evFlags[],
                                 const FSEventStreamEventId evIds[])
            {
                char const **paths = (char const**)evPaths;
                FileWatcherImpl* me_ptr = reinterpret_cast<FileWatcherImpl*>(callbackInfo);

                for(int i = 0; i < numEvents; ++i) {
                    me_ptr->m_func(paths[i], 0);
                }
            }
            
            static void *thread_func(void *context) {
                reinterpret_cast<FileWatcherImpl*>(context)->thread_loop();
                return 0;
            }
            void thread_loop() {
                for (;;) {
                    if (m_flag == 0) { //init
                        pthread_mutex_lock(&m_mutex);
                        m_runloop = CFRunLoopGetCurrent();
                        FSEventStreamScheduleWithRunLoop(m_stream, m_runloop, kCFRunLoopDefaultMode);
                        m_flag = 1;
                        pthread_cond_broadcast(&m_initiated);
                        pthread_mutex_unlock(&m_mutex);
                    } else if (m_flag == 1) { //idle
                        sleep(1);
                        continue;
                    } else if (m_flag == 3) { //destroy
                        break;
                    }
                    
                    CFRunLoopRun();
                    std::cout << "CFRunLoopRun returned" << std::endl;
                }
            }
            
            //Mac Os X can't get access to main.db, monitor it's directroy instead
            std::string makeDirName(std::string &str) {
                int status;
                struct stat st_buf;
                status = stat (str.c_str(), &st_buf);
                if (status != 0) {
                    throw FileWatcherException("File does not exist: error: " + std::string(strerror(errno)));
                    return str;
                }
                if (S_ISDIR (st_buf.st_mode)) { //Ok it's a directory
                    return str;
                }
                if (S_ISREG(st_buf.st_mode)) { //Cut string to accept directory
                    int pos = str.find_last_of("/");
                    str.erase(str.begin() + pos + 1, str.end());
                    return str;
                }
                
                return str;
            }
        };
        
    } //namespace Private
    typedef Private::FileWatcherImpl filewatcher;
} //namespace sm

#endif /* INCLUDE_COMMON_MACOSX_FILEWATCHER_H_ */