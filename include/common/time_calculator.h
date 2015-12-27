/*
 * time_calculator.h
 *
 *  Created on: 14 ���. 2015 �.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_TIME_CALCULATOR_H_
#define INCLUDE_COMMON_TIME_CALCULATOR_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

#include "sstream"


namespace Boss {
/* Remove if already defined */
typedef long long int64; typedef unsigned long long uint64;

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux. */

uint64 GetTimeMs64()
{
#ifdef _WIN32
 /* Windows */
 FILETIME ft;
 LARGE_INTEGER li;

 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
  * to a LARGE_INTEGER structure. */
 GetSystemTimeAsFileTime(&ft);
 li.LowPart = ft.dwLowDateTime;
 li.HighPart = ft.dwHighDateTime;

 uint64 ret = li.QuadPart;
 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

 return ret;
#else
 /* Linux */
 struct timeval tv;

 gettimeofday(&tv, NULL);

 uint64 ret = tv.tv_usec;
 /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
 ret /= 1000;

 /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
 ret += (tv.tv_sec * 1000);

 return ret;
#endif
}

std::string human_readable(Boss::uint64 val) {
	using namespace Boss;
	std::stringstream ss;
	uint64 msecs = val % 1000;
	uint64 seconds = (val/1000) % 60;
	uint64 minutes = val/1000/60;
	uint64 hours =  val/1000/60/60;
	if (hours)   ss << hours   << "h ";
	if (minutes) ss << minutes << "min ";
	if (seconds) ss << seconds << "s ";
	             ss << msecs   << "ms" << std::endl;

	return ss.str();
}

} //namespace Boss

#endif /* INCLUDE_COMMON_TIME_CALCULATOR_H_ */
