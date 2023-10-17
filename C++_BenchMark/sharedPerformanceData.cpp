#include "sharedPerformanceData.hpp"

SharedPerformanceData::SharedPerformanceData(const std::vector<std::vector<double>>& inputArray)
    :m_inputDataRef{inputArray}, m_lineCount{inputArray.size()}{}

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

double SharedPerformanceData::getInputArrayElement(int row, int column)const{
    return m_inputDataRef[row][column];
}

void   SharedPerformanceData::setOutputArrayElement(int row, int column, double data){
    m_outputArray[row][column] = data;
}