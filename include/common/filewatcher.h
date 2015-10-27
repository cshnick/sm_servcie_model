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
#include "stub/stub_filewatcher.h"
#endif
#endif



#endif /* INCLUDE_COMMON_FILEWATCHER_H_ */
