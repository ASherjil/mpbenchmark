# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MPBenchmark)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the threads package, which handles platform-specific threading libraries
find_package(Threads REQUIRED)

# Define the source files we will use
file(GLOB SOURCES "C++_BenchMark/*.cpp")
message("SOURCES = ${SOURCES}")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Define the directories that the compiler should look for headers
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/C++_BenchMark")

# Set the compilation options. Here's where you might add options like -O2 for optimization.
# You can also add them conditionally based on the compiler being used.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-O2" COMPILER_SUPPORTS_O2)
if(COMPILER_SUPPORTS_O2)
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()

# If you are using libraries, you need to link them. In this example, we're linking the 'fmt' library.
find_library(FMT_LIBRARY fmt)
if(FMT_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${FMT_LIBRARY})
else()
    message(FATAL_ERROR "fmt library not found")
endif()

# Link the threading library. This is done after the other setup and will handle the platform-specific aspects of threading.
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

