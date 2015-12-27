/*
 * nix_filewatcher.h
 *
 *  Created on: 05 ���. 2015 �.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_
#define INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_

#include <functional>
#include <atomic>
#include "core/exceptions.h"
#include "common/time_calculator.h"

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

	static constexpr const int latency = 100 * 1000; //100 ms

	FileWatcherImpl(const FileWatcherImpl&) = delete;
	FileWatcherImpl& operator=(const FileWatcherImpl&) = delete;
	FileWatcherImpl() = delete;

	FileWatcherImpl(const std::string &file_name, const std::function<void(std::string, int)> &f) {
	}
	void start() {
	}
	void stop() {
	}
	~FileWatcherImpl() {
	}

};

} //namespace Private
	typedef Private::FileWatcherImpl filewatcher;
} //namespace sm

#endif /* INCLUDE_COMMON_NIX_NIX_FILEWATCHER_H_ */
