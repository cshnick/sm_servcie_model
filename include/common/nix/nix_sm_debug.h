/*
 * callstack.h
 *
 *  Created on: Oct 4, 2015
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_NIX_SM_DEBUG_H_
#define INCLUDE_COMMON_NIX_NIX_SM_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <ostream>

namespace Private {

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline bool callstack_dump(std::ostream &out, unsigned int max_frames = 63)
{
	int ret = 0;
	// storage array for stack trace address data
	void* addrlist[max_frames+1];

	// retrieve current stack addresses
	int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

	if (addrlen == 0) {
		out << "<empty, possibly corrupt>" << std::endl;
		return ret = -1;
	}

	// resolve addresses into strings containing "filename(function+address)",
	// this array must be free()-ed
	char** symbollist = backtrace_symbols(addrlist, addrlen);

	// allocate string which will be filled with the demangled function name
	size_t funcnamesize = 256;
	char* funcname = (char*)malloc(funcnamesize);

	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (int i = 2; i < addrlen; i++) {
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		for (char *p = symbollist[i]; *p; ++p) {
			if (*p == '(')
				begin_name = p;
			else if (*p == '+')
				begin_offset = p;
			else if (*p == ')' && begin_offset) {
				end_offset = p;
				break;
			}
		}

		if (begin_name && begin_offset && end_offset
				&& begin_name < begin_offset) {
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';

			// mangled name is now in [begin_name, begin_offset) and caller
			// offset in [begin_offset, end_offset). now apply
			// __cxa_demangle():

			int status;
			char* ret = abi::__cxa_demangle(begin_name,
					funcname, &funcnamesize, &status);
			if (status == 0) {
				funcname = ret; // use possibly realloc()-ed string
				out << symbollist[i] << ": " << funcname << "+" << begin_offset << std::endl;
			} else {
				// demangling failed. Output function name as a C function with
				// no arguments.
				out << symbollist[i] << ": " << begin_name << "()+" << begin_offset << std::endl;
			}
		} else {
			// couldn't parse the line? print the whole line.
			out << symbollist[i] << std::endl;
		}
	}

	free(funcname);
	free(symbollist);

	return ret;
}

template <class CharT, class TraitsT = std::char_traits<CharT>>
class basic_debugbuf :	public std::basic_stringbuf<CharT, TraitsT> {
public:
	virtual ~basic_debugbuf() {sync();}
protected:
	int sync() {
		output_debug_string(this->str().c_str());
		this->str(std::basic_string<CharT>());    // Clear the string buffer
		return 0;
	}
	void output_debug_string(const CharT *text) {std::cout << text;}
};

template<class CharT, class TraitsT = std::char_traits<CharT> >
class basic_dostream : public std::basic_ostream<CharT, TraitsT> {
public:
	 basic_dostream() : std::basic_ostream<CharT, TraitsT>(new basic_debugbuf<CharT, TraitsT>()) {}
	~basic_dostream() {delete this->rdbuf();}
};

typedef basic_dostream<char>    dostream;
typedef basic_dostream<wchar_t> wdostream;

} // namespace Private



#endif /* INCLUDE_COMMON_NIX_NIX_SM_DEBUG_H_ */
