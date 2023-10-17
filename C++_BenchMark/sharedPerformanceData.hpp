#ifndef SHARED_PERFORMANCE_DATA_HPP
#define SHARED_PERFORMANCE_DATA_HPP

#include <mutex>
#include <vector>

class SharedPerformanceData{
    public:
        SharedPerformanceData(const std::vector<std::vector<double>>& inputArray);
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
        void printPerformanceData()const;
    private:
        mutable std::mutex m_mutexLock;
        const int m_lineCount;
        int    m_numPoints{}; 
        int    m_numMissed{};
	    double m_totalTimePoint{};
	    double m_totalTime{}; 
        double m_totalUsed {};
        const std::vector<std::vector<double>>& m_inputDataRef;
        std::vector<std::vector<double>> m_outputArray;
};

#endif // SHARED_PERFORMANCE_DATA_HPP
