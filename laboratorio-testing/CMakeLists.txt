cmake_minimum_required(VERSION 3.14)
project(LaboratorioTesting LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_library(project_lib
  src/calculator.cpp
  src/string_utils.cpp
  src/grade_utils.cpp
)
target_include_directories(project_lib PUBLIC include)
add_executable(run_tests
  tests/test_calculator.cpp
  tests/test_string_utils.cpp
  tests/test_grade_utils.cpp
)
target_link_libraries(run_tests PRIVATE project_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(run_tests)
