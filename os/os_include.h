#ifndef OS_INCLUDE_H
#define OS_INCLUDE_H

#include "os_core.h"

#if OS_LINUX
#   include "os_linux.h"
#else
#   error OS window layer not implemented for this operating system.
#endif

#endif // OS_INCLUDE_H
