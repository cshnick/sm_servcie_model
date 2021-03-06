/*
 * sm_debug.h
 *
 *  Created on: Oct 4, 2015
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_SM_DEBUG_H_
#define INCLUDE_COMMON_SM_DEBUG_H_

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#  include <direct.h>
#  include "win/win_sm_debug.h"
#  define SM_GET_CWD _getcwd
#else
#  if (defined(__linux__) || defined __APPLE__)
#    include <common/nix/nix_sm_debug.h>
#	 include "unistd.h"
#    define SM_GET_CWD getcwd
#  else
//Stub
namespace PrivateSM {
static inline bool callstack_dump(std::ostream &, unsigned int max_frames = 63) {
	return false;
}
} //namespace Private
#  endif
#endif

namespace Private {
class CallstackImpl {
public:
	static std::vector<std::string> stack_lines() {
		std::vector<std::string> res;
		m_strm.clear();
		callstack_dump(m_strm);
		std::string str;
		while (std::getline(m_strm, str)) {
			res.push_back(str);
		}
		return res;
	}
	static void print() {
		callstack_dump(std::cout);
	}
private:
	static std::stringstream m_strm;
};

} //namespace private

namespace sm {
	typedef ::Private::CallstackImpl callstack;
	typedef ::Private::dostream dostream;

	extern dostream dcout;

	std::string cwd();
	std::pair<std::string, std::string> split_argv0(const std::string& str);
}

#endif /* INCLUDE_COMMON_SM_DEBUG_H_ */
