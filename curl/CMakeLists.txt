cmake_minimum_required(VERSION 3.0)
project(TestProject)

set(CMAKE_CXX_STANDARD 20)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

set (INCLUDEDIRS
src
)

add_executable(TestProject ${SOURCES})

target_compile_options(
    TestProject

    PRIVATE

    /Z7
)

target_link_options(
    TestProject

    PRIVATE

    /DEBUG /OPT:REF /OPT:ICF

)


target_include_directories(TestProject PRIVATE INCLUDEDIRS)

# Link against kernel32 library
target_link_libraries(TestProject PRIVATE kernel32)