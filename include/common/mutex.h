#ifndef __MUTEX_H__
#define __MUTEX_H__

#ifdef _WIN32
#include "win/win_mutex.h"
#else
#if (defined (__unix__) || defined (__APPLE__))
#include "nix/nix_mutex.h"
#else
#error Unsupporetd OS
#endif
#endif

#endif  // !__MUTEX_H__
