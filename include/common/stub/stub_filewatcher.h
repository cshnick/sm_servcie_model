#ifndef INCLUDE_COMMON_STUB_FILEWATCHER_H_
#define INCLUDE_COMMON_STUB_FILEWATCHER_H_

#include <functional>

namespace sm {
    namespace Private {
        
        class FileWatcherImpl {
        public:
            
            FileWatcherImpl(const FileWatcherImpl&) = delete;
            FileWatcherImpl& operator=(const FileWatcherImpl&) = delete;
            FileWatcherImpl() = delete;
            
            FileWatcherImpl(const std::string &file_name, const std::function<void(std::string, int)> &f) {}
            void start() {}
            void stop() {}
        };
        
    } //namespace Private
    typedef Private::FileWatcherImpl filewatcher;
} //namespace sm

#endif /* INCLUDE_COMMON_STUB_FILEWATCHER_H_ */