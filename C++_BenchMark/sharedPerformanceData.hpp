#ifndef SHARED_PERFORMANCE_DATA_HPP
#define SHARED_PERFORMANCE_DATA_HPP

#include <mutex>
#include <vector>

/**
 * @brief A class that holds all the necessary performance data for the benchmark. This object would be
 * shared across all worker threads. The class contains a mutex for protecting against race conditions. 
 */
class SharedPerformanceData{
    public:
        /**
         * @brief Construct a new Shared Performance Data object.
         * @param inputArray readonly access to the input data array.
         * @param numThreads Number of threads used for the benchmark.
         */
        SharedPerformanceData(const std::vector<std::vector<double>>& inputArray, int numThreads);

        // Functions to manilpulate the performance data----------------
        bool isLineCountGreaterThanNumPoints()const;
        int  nextNumPoints();
        void decrementNextNumPoints();
        void increaseTotalTime(double totalTime);
        void increaseTotalUsed(double totalUsed);
        void increaseNumMissed(int missed);
        void increaseTotalTimePoint(double totalTimePoint);
        double getInputArrayElement(int row, int column)const;
        int  getLineCount()const;
        int  getNumMissed()const;
        void setOutputArrayElement(int row, int column, double data);
        //--------------------------------------------------------------

        /**
         * @brief Print all the related benchmark data stored stored by threads in the output array. 
         */
        void printPerformanceData()const;
    private:
        mutable std::mutex m_mutexLock;
        const long unsigned int m_lineCount;
        const int m_numThreads;
        int    m_numPoints{}; 
        int    m_numMissed{};
	    double m_totalTimePoint{};
	    double m_totalTime{}; 
        double m_totalUsed {};
        const std::vector<std::vector<double>>& m_inputDataRef;
        std::vector<std::vector<double>> m_outputArray;
};

#endif // SHARED_PERFORMANCE_DATA_HPP
