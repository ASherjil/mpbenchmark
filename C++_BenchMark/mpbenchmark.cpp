#include "utilities.hpp"
#include "sharedPerformanceData.hpp"
#include "worker.hpp"
#include <string>
#include <thread>
#include <fmt/core.h> // Include the fmt library header for printing 


int main(int argc,char *argv[]){

    int engine = 3; // Default to Turbofan
    unsigned int numThreads = 0; // Will be determined based on hardware or user input

    if (argc > 1) {
        engine = std::atoi(argv[1]); // Convert the argument to an integer
    }

    if (argc > 2) {
        numThreads = static_cast<unsigned int>(std::atoi(argv[2])); // Convert the argument to an integer
    }

    // If number of threads not specified, default to maximum available
    if (numThreads == 0) {
        numThreads = std::thread::hardware_concurrency();
    }

    // Handling engine selection
    switch (engine) {
        case 1:
            fmt::print("Turbojet is selected\n");
            break;
        case 2:
            fmt::print("Afterburner is selected\n");
            break;
        case 3:
            fmt::print("Turbofan is selected\n");
            break;
        default:
            fmt::print("Turbofan (default) is selected\n");
            engine = 3; // Reset to default
            break;
    }
    // Informing the user about the number of threads
    fmt::print("Using {} threads\n", numThreads);

	Utilities::FileDataLoader fileHandler("..//IOFiles//InputFile.txt",
										  "..//IOFiles//C//ResponseTimeForCore",
										  "..//IOFiles//C//DeadLineForCore");

	SharedPerformanceData performanceData(fileHandler.getInputArray());
	std::vector<std::thread> threadPool;
	threadPool.reserve(numThreads);

	// Get the time point at the start of the benchmark
	auto BenchmarkStartTime = std::chrono::high_resolution_clock::now();

	for (int i{};i<numThreads;++i){ // start the threads 
		Worker worker(performanceData, engine, i);
		threadPool.emplace_back(std::thread(worker));
	}

	for (std::thread &t : threadPool) {// wait for the threads to finish 
    	if (t.joinable()) {
    	    t.join(); 
    	}
	}

	// Get the time point at the end of the benchmark
	auto BenchmarkEndTime = std::chrono::high_resolution_clock::now();
	double benchmarkTotalTime = std::chrono::duration<double>(BenchmarkEndTime - BenchmarkStartTime).count();

	// uncomment below to see the printed results
	//performanceData.printPerformanceData();
	fmt::print("{:5f}\n", benchmarkTotalTime);

	// Write all the necessary data to .txt file 
	fileHandler.writeDataToFile(numThreads, benchmarkTotalTime, performanceData.getNumMissed());

	return 0;
}
