#pragma once

#include "env.h"

#if defined(__ENV_PLATFORM_UNIX__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#elif defined(__ENV_PLATFORM_WINDOWS__)
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#endif