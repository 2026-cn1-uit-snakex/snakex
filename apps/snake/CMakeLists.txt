cmake_minimum_required(VERSION 3.29)
project(snake LANGUAGES CXX)

if(WIN32)
  set(snake_console_source src/platform/Console_windows.cpp)
else()
  set(snake_console_source src/platform/Console_posix.cpp)
endif()

add_library(
  snake_domain STATIC
  src/domain/Snake.cpp
  src/domain/Game.cpp
)
target_compile_features(snake_domain PUBLIC cxx_std_23)
set_target_properties(
  snake_domain PROPERTIES
  CXX_EXTENSIONS OFF
  CXX_SCAN_FOR_MODULES OFF
)
target_include_directories(snake_domain PUBLIC src)

add_executable(
  snake
  src/main.cpp
  ${snake_console_source}
)
target_link_libraries(snake PRIVATE snake_domain)
target_compile_features(snake PRIVATE cxx_std_23)
set_target_properties(
  snake PROPERTIES
  CXX_EXTENSIONS OFF
  CXX_SCAN_FOR_MODULES OFF
)
target_include_directories(snake PRIVATE src)

enable_testing()

add_executable(
  snake_tests
  tests/main.cpp
  tests/PlayFieldTests.cpp
  tests/GameStartTests.cpp
  tests/MovementTests.cpp
  tests/FoodAndGrowthTests.cpp
  tests/CollisionTests.cpp
  tests/ResetTests.cpp
)
target_link_libraries(snake_tests PRIVATE snake_domain)
target_compile_features(snake_tests PRIVATE cxx_std_23)
set_target_properties(
  snake_tests PROPERTIES
  CXX_EXTENSIONS OFF
  CXX_SCAN_FOR_MODULES OFF
)
target_include_directories(snake_tests PRIVATE src tests)

add_test(NAME snake_tests COMMAND snake_tests)
