#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef _WIN32
#include "win/win_timer.h"
#else
#ifdef _OS_NIX
#include "nix/nix_timer.h"
#else
#error Unsupporetd OS
#endif
#endif

#endif  // !__TIMER_H__
