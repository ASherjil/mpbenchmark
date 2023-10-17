#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<cstring>
#include<vector>



int NumPoints{}, NumMissed{};
double TotalTimePoint{};
double TotalTime{}, TotalUsed {};



int main(int argc,char *argv[]);
void InitializeArray();
void printResult();

int engine = 3;
double BenchmarkStartTime, BenchmarEndTime;
int NUM_THREADS = 8;
// global constant variables
const double g0 = 32.2;
const double gama = 1.4;
const double tt4 = 2500.0;
const double tt7 = 2500.0;
const double p3p2d = 8.0;
const double p3fp2d = 2.0;
const double byprat = 1.0;
const double fhv = 18600.0;
const double acore = 2.0;
const double afan = 2.0;
const double dfan = 293.02;
const double dcomp = 293.02;
const double dburner = 515.2;
const double dturbin = 515.2;
const double dnozl = 515.2;
// arrays, store input and output data
std::vector<std::vector<double>> inputArray;
std::vector<std::vector<double>> outputArray;

int LineCount = 0;