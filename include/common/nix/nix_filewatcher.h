/*
 * nix_filewatcher.h
 *
 *  Created on: 05 окт. 2015 г.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_
#define INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_

#include <functional>
#include <sys/inotify.h>
#include <limits.h>
#include "unistd.h"
#include <pthread.h>
#include <atomic>

#include "core/exceptions.h"

namespace sm {
BOSS_DECLARE_RUNTIME_EXCEPTION(FileWatcher)

namespace Private {

class FileWatcherImpl {
public:
	enum mod_flag {
		e_undefined = 0x0,
		e_access = 0x2,
		e_modify = 0x4
	};

	FileWatcherImpl(const FileWatcherImpl&) = delete;
	FileWatcherImpl& operator=(const FileWatcherImpl&) = delete;
	FileWatcherImpl() = delete;

	FileWatcherImpl(const std::string &file_name, const std::function<void(std::string, int)> &f)
	: m_filename(file_name), m_func(f), m_flag(0) {
		if (m_filename.empty()) {
			throw FileWatcherException("Filename is empty");
		}
		m_inotify_fd = inotify_init();
		if (m_inotify_fd == -1) {
			throw FileWatcherException("inotify_init");
		}
		pthread_mutex_init(&m_mutex, nullptr);
		pthread_create(&m_thread, nullptr, &FileWatcherImpl::thread_func, (void*)this);
	}
	void start() {
		m_flag = 1;
	}
	void stop() {
		inotify_rm_watch(m_inotify_fd, m_inotify_wd);
		m_inotify_fd = m_inotify_wd = -1;
		m_flag = 0;
	}

	~FileWatcherImpl() {
		stop();
		m_flag = 2;
		pthread_join(m_thread, 0);
		pthread_detach(m_thread);
	}

private:
	static constexpr int buf_len = (10 * (sizeof(struct inotify_event) + NAME_MAX + 1));

	std::function<void(std::string, int)> m_func;
	std::string m_filename;
	int m_inotify_fd = -1, m_inotify_wd = -1;
	std::atomic_int m_flag; //0 - idle, 1 - run, 2 - destroy
	pthread_t m_thread;
	pthread_mutex_t m_mutex;

private:
	void displayInotifyEvent(struct inotify_event *i) {
		mod_flag sendflag = e_undefined;

		if (i->mask & IN_ACCESS) {
			sendflag = e_access;
		} else if (i->mask & IN_MODIFY) {
			sendflag = e_modify;
		}

		if (!sendflag) {
			return;
		}

		m_func(m_filename, static_cast<int>(sendflag));
	}
	static void *thread_func(void *context) {
		reinterpret_cast<FileWatcherImpl*>(context)->thread_loop();
		return 0;
	}
	void thread_loop() {
		for (;;) {

			if (m_flag == 0) {
				sleep(1);
				continue;
			} else if (m_flag == 2) {
				break;
			}

			pthread_mutex_lock(&m_mutex);
			int inotify_fd = m_inotify_fd, inotify_wd = m_inotify_wd;
			pthread_mutex_unlock(&m_mutex);
			char buf[buf_len] __attribute__ ((aligned(8)));
			ssize_t numRead;
			char *p;
			struct inotify_event *event;

			inotify_wd = inotify_add_watch(inotify_fd, m_filename.c_str(), IN_ALL_EVENTS);
			if (inotify_wd == -1) {
				throw FileWatcherException("inotify_add_watch");
			}

			for (;;) {
				numRead = read(inotify_fd, buf, buf_len);
				if (m_flag == 0) {
					continue;
				} else if (m_flag == 2) {
					break;
				}
				//printf("numread: %d\n", (int)numRead);
				if (numRead == 0) {
					throw FileWatcherException("read() from inotify fd returned 0!");
				}
				if (numRead == -1)
					throw FileWatcherException("read");

				/* Process all of the events in buffer returned by read() */

				for (p = buf; p < buf + numRead; ) {
					event = (struct inotify_event *) p;
					displayInotifyEvent(event);

					p += sizeof(struct inotify_event) + event->len;
				}
			}
		}
	}
};

} //namespace Private
	typedef Private::FileWatcherImpl filewatcher;
} //namespace sm

#endif /* INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_ */
