/*
 * win_filewatcher.h
 *
 *  Created on: 05 ���. 2015 �.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_
#define INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_

#include <windows.h>
#include <functional>
#include <atomic>
#include <string>
#include "core/exceptions.h"
#include "common/time_calculator.h"
#include "common/sm_debug.h"

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
	
	static constexpr const int latency = 100; //100 ms

	FileWatcherImpl(const FileWatcherImpl&) = delete;
	FileWatcherImpl& operator=(const FileWatcherImpl&) = delete;
	FileWatcherImpl() = delete;

	FileWatcherImpl(const std::string &file_name, const std::function<void(std::string, int)> &f)
		: m_filename(file_name), m_func(f), m_flag(0) {

		InitializeCriticalSection(&mSection);
		std::size_t found = file_name.find_last_of("/\\");
		if (m_filename.empty()) {
			throw FileWatcherException("Filename is empty");
		}
		m_dirname = file_name.substr(0, found);
		m_watch_directory = CreateFile(
			m_dirname.c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED | FILE_FLAG_BACKUP_SEMANTICS,
			NULL
			);

		if (m_watch_directory == INVALID_HANDLE_VALUE) {
			throw FileWatcherException("Can't create handle for directory");
		}
		DWORD Id = 0;
		if (!(m_thread = CreateThread(0, 0, &FileWatcherImpl::ThreadFunc, this, 0, &Id))) {
			throw FileWatcherException("Can't create thread");
		}
	}
	void start() {
		m_flag = 1;
	}
	void stop() {
		SetEvent(m_dwChangeHandles[1]);
		m_flag = 0;
	}
	~FileWatcherImpl() {
		m_flag = 2;
		CloseHandle(m_thread);
		CloseHandle(m_dwChangeHandles[0]);
		CloseHandle(m_dwChangeHandles[1]);
		CloseHandle(m_watch_directory);
		DeleteCriticalSection(&mSection);
	}

private:
	BOOL   m_isRun;
	HANDLE m_dwChangeHandles[2]; //m_dwChangeHandles[1] exit handle
	std::atomic_int m_flag; //0 - idle, 1 - run, 2 - destroy
	HANDLE m_thread;
	std::string m_filename;
	std::string m_dirname;
    CRITICAL_SECTION mSection;
	HANDLE m_watch_directory = INVALID_HANDLE_VALUE;
	std::function<void(std::string, int)> m_func;

private:
	static DWORD CALLBACK ThreadFunc(PVOID context) {
		reinterpret_cast<FileWatcherImpl*>(context)->thread_loop();
		return 0;
	}
	inline void lock() {EnterCriticalSection(&mSection);}
	inline void  unlock() { LeaveCriticalSection(&mSection);}
	inline void sleep(int secs) {
		Sleep(1000 * secs);
	}
	void thread_loop() {
		for (;;) {

			if (m_flag == 0) {
				sleep(1);
				continue;
			}
			else if (m_flag == 2) {
				break;
			}
			lock();
			m_dwChangeHandles[0] = FindFirstChangeNotification(
				m_dirname.c_str(),             // directory to watch 
				FALSE,                         // do not watch subtree 
				FILE_NOTIFY_CHANGE_FILE_NAME); // watch file name changes 

			m_dwChangeHandles[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
			unlock();

			if (m_dwChangeHandles[0] == INVALID_HANDLE_VALUE) {
				throw FileWatcherException("Thread handle error in filewatcher : " + m_filename);
			}
			if (m_dwChangeHandles[1] == INVALID_HANDLE_VALUE) {
				throw FileWatcherException("Event handle error in filewatcher : " + m_filename);
			}

			for (;;) {
				if (m_flag == 0) {
					break;
				}
				else if (m_flag == 2) {
					break;
				}

				DWORD dwWaitStatus = WaitForMultipleObjects(2, m_dwChangeHandles, FALSE, INFINITE);

				switch (dwWaitStatus) {
				case WAIT_OBJECT_0: {
					lock();
					if (FindNextChangeNotification(m_dwChangeHandles[0]) == FALSE) {
						dcout << "ERROR: FindNextChangeNotification function failed." << std::endl;
						ExitProcess(GetLastError());
					}
					/*CHAR szBuffer[1024 * 128];
					DWORD byteRet = 0;
					if (ReadDirectoryChangesW(m_watch_directory,
						szBuffer,
						sizeof(szBuffer),
						FALSE,
						FILE_NOTIFY_CHANGE_LAST_WRITE,
						&byteRet,
						NULL,
						NULL)) {
						DWORD dwOffset = 0;
						FILE_NOTIFY_INFORMATION* pInfo;
						do {
							pInfo = (FILE_NOTIFY_INFORMATION*)&szBuffer[dwOffset];
							dwOffset += pInfo->NextEntryOffset;
							if (pInfo->FileNameLength == 14 && !memcmp(pInfo->FileName, L"main.db", pInfo->FileNameLength)) {
								break;
							}
						} while (pInfo->NextEntryOffset != 0);
					}*/
					Sleep(latency);
					m_func(m_filename, 0);
					unlock();
					break;

				} case WAIT_OBJECT_0 + 1:

					// A directory was created, renamed, or deleted.
					// Refresh the tree and restart the notification.

					//RefreshTree(lpDrive);
					dcout << "Stopping filewatcher" << std::endl;
					break;

				case WAIT_TIMEOUT:
					printf("\nNo changes in the timeout period.\n");
					break;

				default:
					printf("\n ERROR: Unhandled dwWaitStatus.\n");
					ExitProcess(GetLastError());
					break;
				}
			}
		}
	}
};

} //namespace Private
	typedef Private::FileWatcherImpl filewatcher;
} //namespace sm

#endif /* INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_ */
