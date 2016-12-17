#pragma once

/* Environment detection */
#include "env.h"

/* Type definitions */
#include "types.h"

/* Machine code*/
#include "machine_code.h"

/* Memory functions */
#include "memory.h"

/* Code block functions */
#include "code_block.h"

/* Utilities */
#include "utils.h"

/* Various operating system functions */
#include "sysincl.h"

/* Compilation */
#include "compiler.h"

/* Interpretation */
#include "interpreter.h"

#if !defined(TRUE)
#define TRUE (1)
#endif
#if !defined(FALSE)
#define FALSE (0)
#endif
