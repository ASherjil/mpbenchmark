// utilities.hpp
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string_view>
#include <vector>
#include <string>


namespace Utilities{

constexpr double PRECISION = 0.0001;

/* Utility to convert degree in radian */
double deg2rad(double deg,double pi);

/* Utility to get gamma as a function of temperature */
double getGama(double temp);

double power(double x, int y);

double fabs(double x);

double expo(double x);

double log(double x);

double fpow(double x, double y);

double sqroot(double number);

/* Utility to get the corrected airflow per area given the Mach number */
double getAir(double mach, double gama2);

/* Utility to get the Mach number given the corrected airflow per area */
double getMach(int sub, double corair, double gama1);

/* Analysis for Rayleigh flow */
double getRayleighLoss(double mach1, double ttrat, double tlow);

/* Utility to get cp as a function of temperature */
double getCp(double temp);

class FileDataLoader{
    public:
        FileDataLoader(std::string_view inputPath, std::string_view outPathBenchmark, std::string_view outPathDeadline);
        void writeDataToFile(int threads, double benchmarkTime, int deadlinesMissed);
        const std::vector<std::vector<double>>& getInputArray()const;
    private:
        std::string m_inputFilePath;
        std::string m_outputFilePathBenchmark;
        std::string m_outputFilePathDeadline;
        std::vector<std::vector<double>> m_inputArray;
};

}


#endif  // UTILITIES_HPP
