/*
 * filewatcher.h
 *
 *  Created on: 05 ���. 2015 �.
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
