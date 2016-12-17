#pragma once

#if defined(__x86_64__) || defined(_M_AMD64)
#define __ENV_BIT_64__
#define PRIiN PRIi64
#else
#define __ENV_BIT_32__
#define PRIiN PRIi32
#endif

#if defined(__unix__) || defined(__APPLE__)
#define __ENV_PLATFORM_UNIX__
#elif defined(_WIN32)
#define __ENV_PLATFORM_WINDOWS__
#else
#error Platform unsupported.
#endif

#if defined(__LP64__) || defined(_LP64)
typedef long nint;
typedef unsigned long unint;
#else
#if defined(__ENV_BIT_32__)
typedef int nint;
typedef unsigned int unint;
#elif defined(__ENV_BIT_64__)
typedef long long nint;
typedef unsigned long long unint;
#else
#error Unsupported bits.
#endif
#endif

#define PAGE_SIZE (4096)
#define ROUND_TO_PAGE(X) ((((X) - 1) / PAGE_SIZE + 1) * PAGE_SIZE)
