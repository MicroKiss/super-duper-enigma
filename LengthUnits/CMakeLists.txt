cmake_minimum_required(VERSION 3.26)                                                                                                                 
project(TDD CXX)               
enable_testing()
set(CMAKE_CXX_STANDARD 17)     



set (TESTSOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable (unitTest ${TESTSOURCES})

target_include_directories(
    unitTest

    PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
    unitTest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unitTest)