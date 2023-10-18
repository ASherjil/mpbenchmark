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

/**
 * @brief A class resposible for handling all File IO operations including reading and writing data 
 * to the provided .txt files. 
 */
class FileDataLoader{
    public:
        /**
         * @brief Construct a new File Data Loader object. Loads all input data into an array. 
         * @param inputPath Relative input file path to the input .txt file.
         * @param outPathBenchmark Relative file path to the folder to store benchmark timing results.
         * @param outPathDeadline Relative file path to the folder to store deadline missed results. 
         */
        FileDataLoader(std::string_view inputPath, std::string_view outPathBenchmark, std::string_view outPathDeadline);

        /**
         * @brief Writes the provided data into the output file(s);
         * @param threads Number of threads used for the benchmark.
         * @param benchmarkTime Total benchmark time.
         * @param deadlinesMissed Number of deadlines missed. 
         */
        void writeDataToFile(int threads, double benchmarkTime, int deadlinesMissed);

        /**
         * @brief Get the Input Array object.
         * @return const std::vector<std::vector<double>>& 
         */
        const std::vector<std::vector<double>>& getInputArray()const;
    private:
        std::string m_inputFilePath;
        std::string m_outputFilePathBenchmark;
        std::string m_outputFilePathDeadline;
        std::vector<std::vector<double>> m_inputArray;
};

}


#endif  // UTILITIES_HPP
