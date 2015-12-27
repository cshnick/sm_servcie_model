/*
 * callstack.h
 *
 *  Created on: Oct 4, 2015
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_CALLSTACK_H_
#define INCLUDE_COMMON_NIX_CALLSTACK_H_

#include <ostream>

namespace Private {

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline bool callstack_dump(std::ostream &out, unsigned int max_frames = 63)
{
	std::cout << "callstack_dubmp() not implemented" << std::endl;
}
} // namespace Private



#endif /* INCLUDE_COMMON_NIX_CALLSTACK_H_ */
