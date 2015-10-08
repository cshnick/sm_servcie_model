/*
 * sm_debug.h
 *
 *  Created on: Oct 4, 2015
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_SM_DEBUG_H_
#define INCLUDE_COMMON_SM_DEBUG_H_

#ifdef _WIN32
#  include "win/callstack.h"
#else
#  if (defined(__linux__) || defined (__unix__))
#    include "nix/callstack.h"
#  else
#    error "Unknown OS"
#  endif
#endif

#include <vector>
#include <sstream>

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
}

namespace sm {
	typedef Private::CallstackImpl callstack;
}



#endif /* INCLUDE_COMMON_SM_DEBUG_H_ */