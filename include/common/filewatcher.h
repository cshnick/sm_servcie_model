/*
 * filewatcher.h
 *
 *  Created on: 05 ���. 2015 �.
 *      Author: ilia
 */

#ifndef INCLUDE_COMMON_FILEWATCHER_H_
#define INCLUDE_COMMON_FILEWATCHER_H_

#if defined(_WIN32)
#  include "win/win_filewatcher.h"
#elif defined(__unix)
#  include "nix/nix_filewatcher.h"
#elif defined(__APPLE__)
#  include "macosx/macosx_filewatcher.h"
#else
#  include "stub/stub_filewatcher.h"
#endif //defined(_WIN32)


#endif /* INCLUDE_COMMON_FILEWATCHER_H_ */
