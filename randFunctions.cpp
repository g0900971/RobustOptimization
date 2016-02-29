//
//  randFunctions.cpp
//  Simulator (For random number generation)
//
//  Created by Meilin Zhang on 23/11/12.
//  Copyright (c) 2012 __Random_Simulator__. All rights reserved.
//

#include "randFunctions.h"
#include "RandGen.h"

double RandPOISSION(double p_lambda)
{
	return RandGen::instance().getPOISSION(p_lambda);
}

double RandUNIFORM(double p_min, double p_max)
{
	return RandGen::instance().getUNIFORM(p_min, p_max);
}

int RandUNIFORMINT(int p_min, int p_max)
{
	return RandGen::instance().getUNIFORMINT(p_min, p_max);
}

double RandNORMAL(double p_mu, double p_sigma)
{
	return RandGen::instance().getNORMAL(p_mu, p_sigma);
}

double RandLOGNORMAL(double p_mu, double p_sigma)
{
	return RandGen::instance().getLOGNORMAL(p_mu, p_sigma);
}

bool RandBERNOULLI(double p_rate)
{
	return RandGen::instance().getBERNOULLI(p_rate);
}

int RandBINOMIAL(int p_no, double p_rate)
{
	return RandGen::instance().getBINOMIAL(p_no, p_rate);
}


double RandEXPONENTIAL(double p_lambda)
{
	return RandGen::instance().getEXPONENTIAL(p_lambda);
}

int RandGEOMETRIC(double p_rate)
{
	return RandGen::instance().getGEOMETRIC(p_rate);
}


double RandCAUCHY(double p_location, double p_scale)
{
	return RandGen::instance().getCAUCHY(p_location, p_scale);
}


double RandTRIANGLE(double p_lower, double p_mode, double p_upper)
{
	return RandGen::instance().getTRIANGLE(p_lower, p_mode, p_upper);
}
