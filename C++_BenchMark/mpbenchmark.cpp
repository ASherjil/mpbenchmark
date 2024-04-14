#include <string>
#include <thread>
#include <fmt/core.h> // Include the fmt library header for printing 
#include "utilities.hpp"
#include "sharedPerformanceData.hpp"
#include "worker.hpp"


int main(int argc,char *argv[]){

    int engine{};
    int numThreads{};

    if (argc > 1) {
        engine = std::atoi(argv[1]); // Convert the argument to an integer
    }

    if (argc > 2) {
        numThreads = std::atoi(argv[2]); // Convert the argument to an integer
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

    fmt::print("Using {} threads\n", numThreads);

    // Load data from input .txt file into an array.
	Utilities::FileDataLoader fileHandler("../../IOFiles/InputFile.txt",
										  "../../IOFiles/C++/ResponseTimeForCore",
										  "../../IOFiles/C++/DeadLineForCore");

    // Pass the input data from the .txt file into the SharedPerformanceObject.
	SharedPerformanceData performanceData(fileHandler.getInputArray(), numThreads);

	std::vector<std::thread> threadPool; // create a threadpool
	threadPool.reserve(numThreads);

//----------START TIMING NOW 
	auto BenchmarkStartTime = std::chrono::high_resolution_clock::now();
	for (int i{};i<numThreads;++i){ // start the threads 
		Worker worker(performanceData, engine, i);// each worker thread has access to the SharedPerformanceData object 
		threadPool.emplace_back(std::thread(worker));
	}

	for (std::thread &t : threadPool) {// wait for the threads to finish 
        t.join();
	}
	auto BenchmarkEndTime = std::chrono::high_resolution_clock::now();
//-----------END TIMING NOW 

	double benchmarkTotalTime = std::chrono::duration<double>(BenchmarkEndTime - BenchmarkStartTime).count();
	
/* Uncomment this line to see the calculations and performance data 
	performanceData.printPerformanceData();
*/
	fmt::print("{:6f}\n", benchmarkTotalTime);

	// Write all the necessary data to .txt file 
	fileHandler.writeDataToFile(numThreads, benchmarkTotalTime, performanceData.getNumMissed());

	return 0;
}
