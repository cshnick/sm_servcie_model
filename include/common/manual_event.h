#ifndef __MANUAL_EVENT_H__
#define __MANUAL_EVENT_H__

#ifdef _WIN32
#include "win/win_manual_event.h"
#else
#ifdef _OS_NIX
#include "nix/nix_manual_event.h"
#else
#error Unsupporetd OS
#endif
#endif

#endif  // !__MANUAL_EVENT_H__
