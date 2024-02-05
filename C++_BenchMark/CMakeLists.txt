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

# Compiler optimizations
include(CheckCXXCompilerFlag)

# Check and enable AVX2 and FMA for x86_64 architecture
CHECK_CXX_COMPILER_FLAG("-mavx2" COMPILER_SUPPORTS_AVX2)
CHECK_CXX_COMPILER_FLAG("-mfma" COMPILER_SUPPORTS_FMA)
if(COMPILER_SUPPORTS_AVX2 AND COMPILER_SUPPORTS_FMA)
  target_compile_options(${PROJECT_NAME} PRIVATE -mavx2 -mfma)
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  # For ARMv8-A (aarch64), NEON is always available. No need for -mfpu=neon
  # We can set architecture-specific flags if necessary, but for NEON, it's not required.
endif()

# General optimization flag
target_compile_options(${PROJECT_NAME} PRIVATE -O2)

# Link the fmt library (this uses the imported targets from find_package)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Link the threading library. This is done after the other setup and will handle the platform-specific aspects of threading.
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


