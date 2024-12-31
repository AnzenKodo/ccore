#ifndef STD_OS_H
#define STD_OS_H

#if OS_LINUX
#   include "std/os/os_linux.h"
#else
#   error OS layer not implemented for this operating system.
#endif


#endif // STD_OS_H
