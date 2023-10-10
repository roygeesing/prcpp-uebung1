cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

#=====================#
# (1) Main executable #
#=====================#
project(Astro)

# Define a variable with all header files
set(Astro_INC
    ./include/image.hpp
    ./include/histogram.hpp
    ./include/filter.hpp
    )

# Define a variable with all implementation files
set(Astro_SRC
    ./src/image.cpp
    ./src/histogram.cpp
    ./src/filter.cpp
    )

# Built binaries are output at ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Define the main build target "astro_lib", a library depending on all source files
add_library(astro_lib STATIC ${Astro_SRC} ${Astro_INC})
# Add an include directory to allow imports to work properly
target_include_directories(astro_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Create the main executable and link to library
add_executable(astro ./src/main.cpp)
target_include_directories(astro PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(astro PUBLIC astro_lib)

# Enable strict compiler warnings
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(astro PRIVATE -Wall -Wextra)
endif()
if ( MSVC )
    target_compile_options(astro PRIVATE /W4)
endif()

#=================#
# (2) Test assets #
#=================#
# Add test implementation files
set(Astro_TEST_SRC
    test/utils.cpp
    test/test_task1.cpp
    test/test_task2.cpp
    test/test_task3.cpp
    test/test_task4.cpp
)

# Add header file for test utils
set(Astro_TEST_HEADER
    test/utils.hpp
)

# Fetch Google Test dependency from GitHub
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
# [Windows] Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create a text executable
add_executable(astro_test ${Astro_TEST_SRC} ${Astro_TEST_HEADER})
# Link executable with our main library and the Google Test library
target_link_libraries(astro_test astro_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(astro_test)
