# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MPBenchmark)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the threads package, which handles platform-specific threading libraries
find_package(Threads REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Define the source files we will use
file(GLOB SOURCES "C++_BenchMark/*.cpp")
message("SOURCES = ${SOURCES}")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Define the directories that the compiler should look for headers
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/C++_BenchMark")

# Compiler optimisation 
target_compile_options(${PROJECT_NAME} PRIVATE -O2)

# Link the fmt library (this uses the imported targets from find_package)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Link the threading library. This is done after the other setup and will handle the platform-specific aspects of threading.
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

