# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(mpbenchmark)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the threads package, which handles platform-specific threading libraries
find_package(Threads REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Define the source files we will use
# Assuming the source files are now in the current directory
file(GLOB SOURCES "*.cpp")
message("SOURCES = ${SOURCES}")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Since CMakeLists.txt is now in the same directory as source files, adjust accordingly
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

# Compiler optimisation
# Compiler optimizations including AVX2
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -mavx2 -mfma)

# Link the fmt library (this uses the imported targets from find_package)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Link the threading library. This is done after the other setup and will handle the platform-specific aspects of threading.
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

