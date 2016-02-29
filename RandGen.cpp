//
//  RandGen.cpp
//  Random number generator
//
//  Created by Meilin Zhang on 23/11/12.
//
//

#include "RandGen.h"

RandGen* RandGen::m_instance = NULL;

RandGen& RandGen::instance()
{
	if(m_instance == NULL)
	{
		m_instance = new RandGen();
	}
	return *m_instance;
}


double RandGen::getPOISSION(double p_lambda)
{
	boost::poisson_distribution<> poisson(p_lambda);
	boost::variate_generator<boost::mt19937_64&, boost::poisson_distribution<> > poisson_sampler(m_gen, poisson);

	return poisson_sampler();
}


double RandGen::getUNIFORM(double p_min, double p_max)
{
	boost::uniform_real<> uniform(p_min, p_max);
	boost::variate_generator<boost::mt19937_64&, boost::uniform_real<> > uniform_sampler(m_gen, uniform);

	return uniform_sampler();
}

int RandGen::getUNIFORMINT(int p_min, int p_max)
{
	boost::uniform_int<> uniformInt(p_min, p_max);
	boost::variate_generator<boost::mt19937_64&, boost::uniform_int<> > uniform_sampler(m_gen, uniformInt);

	return uniform_sampler();
}

double RandGen::getNORMAL(double p_mu, double p_sigma)
{
	boost::normal_distribution<> normal(p_mu, p_sigma);
	boost::variate_generator<boost::mt19937_64&, boost::normal_distribution<> > normal_sampler(m_gen, normal);

	return normal_sampler();
}


double RandGen::getLOGNORMAL(double p_mu, double p_sigma)
{
	boost::lognormal_distribution<> lognormal(p_mu, p_sigma);
	boost::variate_generator<boost::mt19937_64&, boost::lognormal_distribution<> > lognormal_sampler(m_gen, lognormal);

	return lognormal_sampler();
}


bool RandGen::getBERNOULLI(double p_rate)
{
	boost::bernoulli_distribution<> bernoulli(p_rate);
	boost::variate_generator<boost::mt19937_64&, boost::bernoulli_distribution<> > bernoulli_sampler(m_gen, bernoulli);

	return bernoulli_sampler();
}

int RandGen::getBINOMIAL(int p_no, double p_rate)
{
	boost::binomial_distribution<> binomial(p_no, p_rate);
	boost::variate_generator<boost::mt19937_64&, boost::binomial_distribution<> > binomial_sampler(m_gen, binomial);

	return binomial_sampler();
}


double RandGen::getEXPONENTIAL(double p_lambda)
{
	boost::exponential_distribution<> exponential(p_lambda);
	boost::variate_generator<boost::mt19937_64&, boost::exponential_distribution<> > exponential_sampler(m_gen, exponential);

	return exponential_sampler();
}


int RandGen::getGEOMETRIC(double p_rate)
{
	boost::geometric_distribution<> geometric(p_rate);
	boost::variate_generator<boost::mt19937_64&, boost::geometric_distribution<> > geometric_sampler(m_gen, geometric);

	return geometric_sampler();
}


double RandGen::getCAUCHY(double p_location, double p_scale)
{
	boost::cauchy_distribution<> cauchy(p_location, p_scale);
	boost::variate_generator<boost::mt19937_64&, boost::cauchy_distribution<> > cauchy_sampler(m_gen, cauchy);

	return cauchy_sampler();
}

double RandGen::getTRIANGLE(double p_lower, double p_mode, double p_upper)
{
	boost::triangle_distribution<> triangle(p_lower, p_mode, p_upper);
	boost::variate_generator<boost::mt19937_64&, boost::triangle_distribution<> > triangle_sampler(m_gen, triangle);

	return triangle_sampler();
}