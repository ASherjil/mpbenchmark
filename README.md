# mpbenchmark

Mpbenchmark is an application benchmark for evaluating the efficiency of multiprocessor support for parallel processing. Mpbenchmark was a revised version of "JetBench", written in many languagues such as C(OpenMP), Ada, C# and Java. This repository contains mpbenchmark writtein in mordern C++.  This is a command line application  used to analyse the real time performance of a multicore platform. The application is designed to be platform independent by avoiding target specific libraries and hardware counters and timers.

The original source code for `mpbenchmark` delivered optimal performance with implementations in Ada and C, attributed to their nature as compiled languages. As anticipated, Java and C# implementations yielded lower performance metrics. Given that the original codebase was dated, and faced challenges inherent to C—such as manual memory management and a lack of object-oriented programming features—it became imperative to transition to modern C++. With advancements in C++, especially the advent of `std::thread` introduced in C++11, memory management concerns have been significantly alleviated. It's intriguing to envisage how a modern compiled language like C++ compares in performance against the original C implementation.

# Performance comparision C(OpenMP) vs C++20

Measurements were taken using 16 threads using the following system:

CPU: Amd Ryzen 7 5800H

RAM: 16GB

OS: Ubuntu Linux 22.04.3 LTS 

![benchmark_results](https://github.com/ASherjil/mpbenchmark/assets/92602684/9ff36bc6-016e-4ba1-b7a2-b9a47daffbbb)
