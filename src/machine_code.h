#pragma once

#include "plus1s.h"

// We want cdecl function explicitly.
typedef __cdecl nint (*plus1s_func)();

extern machine_code_template g_machine_code;

machine_code_template *init_machine_code_template();
