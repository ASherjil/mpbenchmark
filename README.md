# mpbenchmark

Mpbenchmark is an application benchmark for evaluating the efficiency of multiprocessor support for parallel processing. Mpbenchmark was a revised version of "JetBench", written in many languagues such as C(OpenMP), Ada, C# and Java. This repository contains mpbenchmark writtein in mordern C++.  This is a command line application  used to analyse the real time performance of a multicore platform. The application is designed to be platform independent by avoiding target specific libraries and hardware counters and timers.

The original source code for `mpbenchmark` delivered optimal performance with implementations in Ada and C, attributed to their nature as compiled languages. As anticipated, Java and C# implementations yielded lower performance metrics. Given that the original codebase was dated, and faced challenges inherent to C—such as manual memory management and a lack of object-oriented programming features—it became imperative to transition to modern C++. With advancements in C++, especially the advent of `std::thread` introduced in C++11, memory management concerns have been significantly alleviated. It's intriguing to envisage how a modern compiled language like C++ compares in performance against the original C implementation.

Moreover, an alternative version is also produced to leverage SIMD instructions(the application will determine whether to use AVX2 or NEON depending on the CPU). The SIMD optimised version perfoms over 50% faster than the previous solutions in C(OpenMP) and Ada, please see the benchmark time plot below. 

# Performance comparision of the improved benchmark solution 

Measurements were taken using 16 threads using the following system:

CPU: Amd Ryzen 7 5800H

RAM: 16GB

OS: Ubuntu Linux 22.04.3 LTS 

![speedup_plot_desktop](https://github.com/ASherjil/mpbenchmark/assets/92602684/af78a2ef-554f-473a-8f93-b95fde38df81)

The C++ solution especially the optimised SIMD version darastically outperforms all the solutions.  

# Installation and usage

**Linux:**

1- First make sure to install CMake and the `fmt` C++ library. CMake and `fmt` can be installed on Debian/Ubuntu distribution like shown below:

  1.1 - Intall CMake using `sudo apt install cmake`. Then verify the intallation `cmake --version`.

  1.2 - Install `fmt` library using the command `sudo apt install libfmt-dev`. 

2- Clone this repository. 

  2.1 - To use the SIMD optimised version(recommended). Checkout to the `WFD` branch, run `git checkout WFD`.
  
  2.2 - To use the regular C++ version without SIMD stay on this branch. 

Now create a "build" folder inside "C++_BenchMark". You can do this by running the commands:

```
cd C++_BenchMark 
mkdir build && cd build
```

3- Now run cmake and build the project. You can use these commands:

```
cmake ..

cmake --build .
```

4- Once the build is successfull then run the executable. You can supply it with the engine type(1, 2 or 3) and specify the threads to use as the command line arguments. You can also leave this blank to use the default parameters.
Run this for the default configuration:

`
./mpbenchmark 
`

Run this to use engine 1 and 12 threads:

`
./mpbenchmark 1 12
`

**Windows(MinGW):**

Here we make use of the MinGW compiler for windows. 

1- Firstly install cmake and the `fmt` library C++ library. `fmt` library can be installed via `vcpkg`. Installing `fmt` is more tricky on Windows so I will share these steps. 

2- Installing `fmt` : 

  2.1 - Clone the git repo `git clone https://github.com/microsoft/vcpkg.git`.
  
  2.2 - Navigate inside the folder `cd vcpkg`. Then run the `.bat` file: `.\bootstrap-vcpkg.bat`.

  2.3 - Now install the static library for MinGW. `./vcpkg install fmt:x64-mingw-static`. Dynamic library can also be used but I used static for this example. 

3- Once `fmt` is installed. Navigate inside the mpbenchmark folder that contains the cloned repo. Create a new folder for building `mkdir build`.  Now we need to run CMake using the MinGW compiler, specify where to look for the `vcpkg` toolchain and specify the triplet here for MinGW compiler:

```
cmake -G "MinGW Makefiles" -B [build directory] -S [source directory] -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-mingw-static
```

Example for my pc would be:

```
cmake -G "MinGW Makefiles" -B "C:\Users\user1\Desktop\mpbenchmark\build" -S "C:\Users\user1\Desktop\mpbenchmark" -DCMAKE_TOOLCHAIN_FILE="C:\Users\user1\Documents\vcpkg\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-mingw-static

```

4- Now we build the project. `cmake --build "C:\Users\user1\Desktop\mpbenchmark\build"`

5- Once built, find and execute the executable produced in the build folder. 


