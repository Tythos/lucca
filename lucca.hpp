/**
 * lucca.hpp
 */

#pragma once

#include <iostream>
#include <cmath>
#include <exception>
#include <string>
#include <Eigen/Dense>

// this is not strictly necessarily for compiling or runtime but does help with LSP
#ifndef M_PI
    #define M_PI 3.1415926535897932384626433
#endif

namespace lucca {
    namespace exceptions {
        class xUnknown : public std::exception {
        public:
            virtual const char* what() const throw();
        };
    }
	
	enum OrbitRegime { ORBREG_LEO, ORBREG_MEO, ORBREG_GEO, ORBREG_HEO };

	class Orbel {
		protected:
			float a_m;
			float e;
			float i_rad;
			float O_rad;
			float w_rad;
			float M_rad;
			float t_jd;
		public:
			Orbel();
			void toAnomaly(float tht_rad, Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
			void toEci(float tInp_jd, Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
			void fromRv(float tInp_jd, Eigen::Vector3f rEci_m, Eigen::Vector3f vEci_mps);
			void fromGeo(float tInp_jf, float lon_rad, float inc_rad, float phase_rad);
			void toEcf(float tInp_jd, Eigen::Vector3f &rEcf_m, Eigen::Vector3f &vEcf_mps);
			void toLla(float tInp_jd, Eigen::Vector3f &rLla_radm, Eigen::Vector3f &vDlla_radmps);
			void fromGibbs(Eigen::Vector3f obs1_m, Eigen::Vector3f obs2_m, Eigen::Vector3f obs3_m, float tObs2_jd);
			void fromLambert(Eigen::Vector3f obs1_m, float tObs1_jd, Eigen::Vector3f obs2_m, float tObjs2_jd);
			void fromTrack(float range_m, float az_rad, float el_rad, float dr_mps, float dAz_radps, float dEl_radps, Eigen::Vector3f rStationLla_radm, float tObs_jd);
			void fromAngles(float az1_rad, float el1_rad, float t1_jd, float az2_rad, float el2_rad, float t2_jd, float az3_rad, float el3_rad, float t3_jd, Eigen::VectorXf rStationLla_radm);
			Eigen::VectorXf getH();
			float getEnergy();
			float getPeriod();
			void fromRegime(OrbitRegime orbReg);
			void fromShape(float perAlt_m, float apoAlt_m);
			Eigen::MatrixXf getCoverage(float time_jd, float lookLon_rad, float lookLat_rad, float fovHalfAngle);
			Eigen::MatrixXf getPqwFrame();
			void getAscNode(Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
			void getDescNode(Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
			void getApogee(Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
			void getPerigee(Eigen::Vector3f &rEci_m, Eigen::Vector3f &vEci_mps);
	};
	
	class Kepler {
		protected:
			float tolerance;
			Eigen::Vector3f rEci_m;
			Eigen::Vector3f vEci_mps;
		public:
			Kepler();
			Orbel solveTrajectory(float dt_s);
			float solveAnomaly(float dt_s);
	};
	
	class Lambert {
		private:
			float dTheta_rad;
			float A;
			float r1;
			float r2;
			float y0;
		protected:
			Eigen::Vector3f r1Eci_m;
			Eigen::Vector3f r2Eci_m;
			float mu;
			float F(float z, float dt, float subsetIndices);
			float dFdz(float z, float subsetIndices);
			float y(float z, float subsetIndices);
		public:
			Lambert();
			void solve(float dt_s, bool isPrograde, Eigen::Vector3f &v1Eci_mps, Eigen::Vector3f &v2Eci_mps);
			float charTime();
			Orbel charOrb();
	};
	
	class Maneuver {
		protected:
			Orbel source;
			Orbel dest;
		public:
			Maneuver();
			Orbel getHohmann();
			Orbel getDirect();
	};
	
	class Thruster {
		protected:
			float ri_m;
			float rf_m;
			float m0_kg;
			float isp_s;
			float thrust_N;
		public:
			Thruster();
			float getFlightTime(float ispInp_s, float thrustInp_N);
			float getPropellantUsed(float ispInp_s, float thrustInp_N);
			void integrateTransit(float ispInp_s, float thrustInp_N, Eigen::VectorXf &t_s, Eigen::MatrixXf &rEci_m, Eigen::VectorXf &vEci_mps);
			//Eigen::Vector6f thrustEquation(float t_s, Eigen::Vector6f x);
	};

	namespace anomaly {
		float true2ecc(float tht_rad, float e);
		float true2mean(float tht_rad, float e);
		float mean2true(float M_rad, float e);
        float mean2ecc(float M_rad, float e);
		float ecc2true(float E_rad, float e);
        float ecc2mean(float E_rad, float e);
        float angmod(float ang_rad);
	}
	
	namespace AstroTime {
		extern float tzOffset;
		extern float jd1900;
		//extern Eigen::Vector12f daysInMonths;
		
		float jd2nasa(float jd);
		float nasa2jd(float nasa);
		
		float jd2nist(float jd);
		float nist2jd(float nist);
		
		//Eigen::Vector6f jd2dv(float jd);
		//float dv2jd(Eigen::Vector6f dv);
		
		float jd2ml(float jd);
		float ml2jd(float ml);
		
		Eigen::Vector2f jd2yd(float jd);
		float yd2jd(Eigen::Vector2f);
		
		long int jd2unix(float jd);
		float unix2jd(long int unix);
		
		std::string str2jd(float jd);
		float str2jd(std::string str);
		
		float now();
		//Eigen::Vector12i getNetMonthLen(int year);
		bool isLeapYear(int year);
		float jd2gmst(float jd);
	}
	
	namespace earth {
		extern const float alb;
		extern const float radius_m;
		extern const float mass_kg;
		extern const float rotVel_radps;
		extern const float flat;
		//extern Orbel orbit;
		extern const float mu_m3ps2;
		//extern float e2;
		extern const float g0_mps2;
		
		Eigen::Vector3f aer2rdr(Eigen::Vector3f rAer_radm, Eigen::Vector3f rStationLla_radm, float t_jd);
		float g(float alt_m);
		//Eigen::Matrix33f ecf2eci(float t_jd);
		Eigen::Vector3f ecf2lla(Eigen::Vector3f rEcf_m);
		//Eigen::Matrix33f eci2ecf(float t_jd);
		Eigen::Vector3f lla2ecf(Eigen::Vector3f rLla_radm);
		Eigen::Vector3f nutationParams(float t_jd);
		Eigen::Matrix3f polarMotion(float t_jd, float xPmc, float yPmc);
		Eigen::Vector3f rdr2aer(Eigen::VectorXf rdr_radm, Eigen::Vector3f rStationLla_radm, float t_jd);
		//Eigen::Matrix33f precession(float t_jd);
		//Eigen::Matrix33f nutation(float t_jd);
		//Eigen::Matrix33f spin(float t_jd);
	}
	
	namespace stumpff {
		float sine(float x);
		float cosine(float x);
	}
}
