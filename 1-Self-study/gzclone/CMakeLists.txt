cmake_minimum_required(VERSION 3.20)

project(gzclone VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gzclone
    src/main.cpp
    src/core/Log.cpp
)

target_include_directories(gzclone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(gzclone PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
