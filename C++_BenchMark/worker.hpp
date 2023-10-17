#ifndef WORKER_HPP
#define WORKER_HPP

#include "utilities.hpp"
#include "sharedPerformanceData.hpp"

class Worker{
    public:
        Worker(SharedPerformanceData& sharedData, int engine, int id);
        void operator()();
    private:
        SharedPerformanceData& m_sharedData;
        const int m_engine;
        const int m_id;

        // readonly variables 
		static constexpr double g0 = 32.2;
		static constexpr double gama = 1.4;
		static constexpr double tt4 = 2500.0;
		static constexpr double tt7 = 2500.0;
		static constexpr double p3p2d = 8.0;
		static constexpr double p3fp2d = 2.0;
		static constexpr double byprat = 1.0;
		static constexpr double fhv = 18600.0;
		static constexpr double acore = 2.0;
		static constexpr double afan = 2.0;
		static constexpr double dfan = 293.02;
		static constexpr double dcomp = 293.02;
		static constexpr double dburner = 515.2;
		static constexpr double dturbin = 515.2;
		static constexpr double dnozl = 515.2;

        // variables for calculations
        std::array<double, 20> trat;
        std::array<double, 20> tt;
        std::array<double, 20> prat;
        std::array<double, 20> pt;
        std::array<double, 20> eta;
        std::array<double, 20> gam;
        std::array<double, 20> cp;
        double altd, u0d;
		double throtl;
		double weight;
		double Rgas, alt, ts0, ps0, a0, u0, fsmach, q0, tsout, psout, rho0, cpair;
		double a8, a8d, a4, m2, mfr, isp;
		double epr, etr, npr, snpr;
		double fnet, fgros, dram, sfc, fa, eair, uexit, ues;
		double fnlb, fglb, drlb, flflo;
		double pexit, pfexit;
		double a8max, a8rat, a4p;
		double lcomp, lburn, lturb, lnoz, ncomp, nturb;
		double sblade, hblade, tblade, xcomp, ncompd;

        // private functions for computations
        void initializeParam();
        void deduceInputs();
        void getThermo();
        void calcPerf();
        void getGeo();

};

#endif // WORKER_HPP
