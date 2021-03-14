#pragma once

_declspec(selectany) int b;

#include <windows.h>

#ifdef __cplusplus    // If used by C++ code, 
extern "C"            // we need to export the C interface
#endif

__declspec(dllexport) int __cdecl getB();
