/*
 * callstack.h
 *
 *  Created on: Oct 4, 2015
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_NIX_CALLSTACK_H_
#define INCLUDE_COMMON_NIX_CALLSTACK_H_

#include <Windows.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>

namespace Private {

template <class CharT, class TraitsT = std::char_traits<CharT>>
class basic_debugbuf :	public std::basic_stringbuf<CharT, TraitsT> {
public:
	virtual ~basic_debugbuf() {sync();}
protected:
	int sync() {
		output_debug_string(str().c_str());
		str(std::basic_string<CharT>());    // Clear the string buffer
		return 0;
	}
	void output_debug_string(const CharT *text) {}
};
template<>
void basic_debugbuf<char>::output_debug_string(const char *text) {
	::OutputDebugStringA(text);
}
template<>
void basic_debugbuf<wchar_t>::output_debug_string(const wchar_t *text) {
	::OutputDebugStringW(text);
}
template<class CharT, class TraitsT = std::char_traits<CharT> >
class basic_dostream : public std::basic_ostream<CharT, TraitsT> {
public:
	 basic_dostream() : std::basic_ostream<CharT, TraitsT>(new basic_debugbuf<CharT, TraitsT>()) {}
	~basic_dostream() {delete rdbuf();}
};

typedef basic_dostream<char>    dostream;
typedef basic_dostream<wchar_t> wdostream;

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline bool callstack_dump(std::ostream &out, unsigned int max_frames = 63)
{
	std::cout << "callstack_dubmp() not implemented" << std::endl;
}

} // namespace Private



#endif /* INCLUDE_COMMON_NIX_CALLSTACK_H_ */
