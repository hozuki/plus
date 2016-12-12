cmake_minimum_required(VERSION 3.6)
project(plus1s)

set(CMAKE_C_STANDARD 99)
set(CMAKE_USE_RELATIVE_PATHS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${TARGET_ARCH}/${CMAKE_BUILD_TYPE})

if ("${CYGWIN}" OR "${MINGW}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif ()

set(SOURCE_FILES src/main.c src/env.h src/plus1s.h src/machine_code/code_win32.c src/platform_specific/memory_win.c src/code_block.c src/machine_code/code.c src/compile.c)
add_executable(plus1s ${SOURCE_FILES})