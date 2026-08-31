cmake_minimum_required(VERSION 3.29)
project(snake LANGUAGES CXX)

if(WIN32)
  set(snake_console_source src/platform/Console_windows.cpp)
else()
  set(snake_console_source src/platform/Console_posix.cpp)
endif()

add_executable(snake src/main.cpp src/domain/Snake.cpp ${snake_console_source})

target_compile_features(snake PRIVATE cxx_std_23)

set_target_properties(snake PROPERTIES CXX_EXTENSIONS OFF CXX_SCAN_FOR_MODULES OFF)

target_include_directories(snake PRIVATE src)
