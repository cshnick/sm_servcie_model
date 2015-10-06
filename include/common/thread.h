#ifndef __THREAD_H__
#define __THREAD_H__

#ifdef _WIN32
#include "win/win_thread.h"
#else
#ifdef _OS_NIX
#include "nix/nix_thread.h"
#else
#error Unsupporetd OS
#endif
#endif

#endif  // !__THREAD_H__
