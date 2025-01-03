#ifndef OS_H
#define OS_H

#if OS_LINUX
#   include "core/os/os_linux.h"
#else
#   error OS layer not implemented for this operating system.
#endif

#endif // OS_H
