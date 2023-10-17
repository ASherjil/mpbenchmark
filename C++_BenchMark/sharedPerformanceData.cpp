#include "sharedPerformanceData.hpp"
#include <fmt/core.h>

SharedPerformanceData::SharedPerformanceData(const std::vector<std::vector<double>>& inputArray)
    :m_lineCount{inputArray.size()}, m_inputDataRef{inputArray}, m_outputArray{m_lineCount, std::vector<double>(18, 0.0)}{}

bool   SharedPerformanceData::isLineCountGreaterThanNumPoints()const{
    std::lock_guard<std::mutex> guard(m_mutexLock);
    return m_numPoints < m_lineCount; 
}


int    SharedPerformanceData::nextNumPoints(){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_numPoints++;
    return m_numPoints;
}

void   SharedPerformanceData::decrementNextNumPoints(){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_numPoints--;
}

void  SharedPerformanceData::increaseTotalTime(double totalTime){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_totalTime += totalTime;
}

void  SharedPerformanceData::increaseTotalUsed(double totalUsed){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_totalTime += totalUsed;
}

void  SharedPerformanceData::increaseNumMissed(int missed){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_numMissed += missed;
}

void  SharedPerformanceData::increaseTotalTimePoint(double totalTimePoint){
    std::lock_guard<std::mutex> guard(m_mutexLock);
    m_totalTimePoint += totalTimePoint;
}

int SharedPerformanceData::getLineCount()const{
    return m_lineCount;
}

int SharedPerformanceData::getNumMissed()const{
    std::lock_guard<std::mutex> guard(m_mutexLock);
    return m_numMissed;
}

double SharedPerformanceData::getInputArrayElement(int row, int column)const{
    return m_inputDataRef[row][column];
}

void   SharedPerformanceData::setOutputArrayElement(int row, int column, double data){
    m_outputArray[row][column] = data;
}

void   SharedPerformanceData::printPerformanceData()const{
    // Printing the header of the table.
	fmt::print("T,ExecTime,  Spd| Alt |  Thr| Mach|Press| Temp| Fnet|Fgros|RamDr|FlFlo|TSFC|Airfl|Weight|Fn/W\n");

	// Iterating through 'm_outputArray' and printing each entry.
	for (int i = 0; i < m_lineCount; i++) {
	    fmt::print("{},{:7f}, {:4.0f}|{:5.0f}|{:5.1f}|{:5.3f}|{:5.2f}|{:5.1f}|{:5.0f}|{:5.0f}|{:5.0f}|{:5.0f}|{:4.2f}|{:5.1f}|{:6.2f}|{:4.2f}\n     {:3.1f}% used for point {}\n",
	                            static_cast<int>(m_outputArray[i][0]), m_outputArray[i][1], m_outputArray[i][2], m_outputArray[i][3],
	                            m_outputArray[i][4], m_outputArray[i][5], m_outputArray[i][6], m_outputArray[i][7],
	                            m_outputArray[i][8], m_outputArray[i][9], m_outputArray[i][10], m_outputArray[i][11],
	                            m_outputArray[i][12], m_outputArray[i][13], m_outputArray[i][14], m_outputArray[i][15],
	                            m_outputArray[i][16], static_cast<int>(m_outputArray[i][17]));
	}

	// Additional print statements.
	fmt::print("{}\n", m_numMissed);
	fmt::print("Thread response time sum:{:f}\n", m_totalTime);
	fmt::print("Number of points : {}\n", m_numPoints);
}