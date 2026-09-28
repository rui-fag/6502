cmake_minimum_required(VERSION 3.14)

project(sfot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC
    src/fsm.cpp
    src/memory.cpp
    src/opcodes.cpp
    src/sfot.cpp
    src/loader.cpp
)

add_library(sfot_lib STATIC ${SRC})
target_include_directories(sfot_lib PUBLIC src)
target_include_directories(sfot_lib PUBLIC include)
target_compile_options(sfot_lib PUBLIC -fcontracts)
target_link_options(sfot_lib PUBLIC -fcontracts)

add_executable(sfot src/main.cpp)
target_link_libraries(sfot PRIVATE sfot_lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sfot_lib PRIVATE -fdiagnostics-color=always)
    target_compile_options(sfot PRIVATE -fdiagnostics-color=always)
endif()

enable_testing()
add_subdirectory(tests)
include_directories(include)
