//
//  randFunctions.h
//  Simulator (For random number generation)
//
//  Created by Meilin Zhang on 23/11/12.
//  Copyright (c) 2012 __Random_Simulator__. All rights reserved.
//

#ifndef Simulator_randFunctions_h
#define Simulator_randFunctions_h

enum RandDist {POISSION, UNIFORM, UNIFORMINT, NORMAL, LOGNORMAL, BERNOULLI, BINOMIAL, 
	CAUCHY, EXPONENTIAL, GEOMETRIC, TRIANGLE};

double RandPOISSION(double p_lambda);

double RandUNIFORM(double p_min, double p_max);
int RandUNIFORMINT(int p_min, int p_max);

double RandNORMAL(double p_mu, double p_sigma);
double RandLOGNORMAL(double p_mu, double p_sigma);

bool RandBERNOULLI(double p_rate);
int RandBINOMIAL(int p_no, double p_rate);

double RandEXPONENTIAL(double p_lambda);

int RandGEOMETRIC(double p_rate);

double RandCAUCHY(double p_location, double p_scale);

double RandTRIANGLE(double p_lower, double p_mode, double p_upper);

#endif