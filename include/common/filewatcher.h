/*
 * filewatcher.h
 *
 *  Created on: 05 окт. 2015 г.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_FILEWATCHER_H_
#define INCLUDE_COMMON_FILEWATCHER_H_

#ifdef _WIN32
#include "win/filewatcher.h"
#else
#ifdef __unix
#include "nix/nix_filewatcher.h"
#else
#error Unsupporetd OS
#endif
#endif



#endif /* INCLUDE_COMMON_FILEWATCHER_H_ */
