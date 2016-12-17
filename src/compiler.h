#pragma once

#include "plus1s.h"

extern bytecode_compiler g_compiler;

void compiler_init();

void compiler_destroy();

void compiler_append_plus1s();

void compiler_enter_loop(const char *people_count);

void compiler_exit_loop();
