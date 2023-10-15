#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main();
void InitializeArray();
void printResult();
double deg2rad(double deg,double pi);
double sqroot(double numb1er);
double fabs(double x);
double log(double x);
double expo(double x);
double fpow(double x, double y);
double power(double x, int y);
double getCp(double temp);
double getRayleighLoss(double mach1, double ttrat, double tlow);
double getAir(double mach, double gama2);
double getMach(int sub, double corair, double gama1);
double getGama(double temp);

int engine = 3;
double BenchmarkStartTime, BenchmarEndTime;
int NUM_THREADS = 8;
const double PRECISION = 0.0001;
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
double** inputArray;
double** outputArray;

int LineCount = 0;
int NumPoints = 0, NumMissed = 0;
double TotalTimePoint = 0;
double TotalTime = 0, TotalUsed = 0;