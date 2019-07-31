//
//  RandGen.h
//  Simulator (For random number generation)
//
//  Created by Meilin Zhang on 23/11/12.
//  Copyright (c) 2012 __Random_Simulator__. All rights reserved.
//

#ifndef Simulator_RandGen_h
#define Simulator_RandGen_h

#include <boost/random.hpp>

class RandGen
{
public:
	static RandGen& instance();

	double getPOISSION(double p_lambda);

	double getUNIFORM(double p_min, double p_max);
	int getUNIFORMINT(int p_min, int p_max);

	double getNORMAL(double p_mu, double p_sigma);
	double getLOGNORMAL(double p_mu, double p_sigma);

	bool getBERNOULLI(double p_rate);
	int getBINOMIAL(int p_no, double p_rate);

	double getEXPONENTIAL(double p_lambda);

	int getGEOMETRIC(double p_rate);

	double getCAUCHY(double p_location, double p_scale);

	double getTRIANGLE(double p_lower, double p_mode, double p_upper);

private:
	static RandGen* m_instance;
	boost::mt19937_64 m_gen;
};

#endif