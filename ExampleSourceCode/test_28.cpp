#include "ROVar.h"
#include "ROUn.h"
#include "ROVarDR.h"
#include "ROUnVarC.h"
#include "ROExpr.h"
#include "ROModel.h"
#include "ROObjective.h"
#include "ROConstraint.h"
#include "ROConstraintSet.h"
#include "roexprfunctions.h"
#include "ROTypedefs.h"


using namespace std;

int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                  ROME_CMP_2.m      
	   -----------------------------------------------------------------*/
	double sigma = 1, mu = 2;
	
	for(int i = -10; i < 10; i++ )
	{

	ROModel model;

	ROVar a;
	ROVarDR X;
	ROUn Z, U;

	X.addDR(Z);
	X.addDR(U);


	ROConstraintSet unConstSet;
	unConstSet.add(ROExpect(Z) == mu);
	unConstSet.add(ROSq(Z) <= U);
	unConstSet.add(ROExpect(U) == mu*mu+sigma*sigma);
	unConstSet.add(Z >= -mu);

	model.add(ROConstraint(X >= 0, unConstSet));
	model.add(ROConstraint(X >= -a + Z, unConstSet));
	model.add(a == i);

	model.add(ROMinimize(ROExpect(X), unConstSet));

	model.solve();
	std::cout << "--------------------------" << std::endl;

	std::cout << "obj value = " << model.getObjValue() << std::endl;



	std::cout <<" a = " << model.getVarValue(a) << std::endl;



	//std::cout << "b = " <<model.getVarValue(b) << std::endl;


		RONum val_a = model.getVarValue(a);
			//RONum val_b = model.getVarValue(b);
		double dVal = (sigma*sigma - mu*mu)/(2*mu), value;
		if(val_a>= 0)
		{
			if(val_a - mu >= dVal)
			{
				value = (-(val_a-mu) + sqrt(sigma*sigma + (val_a-mu)*(val_a-mu)))/2;
			}
			else
			{
				value = (-(val_a-mu)*mu*mu + mu*sigma*sigma)/(mu*mu + sigma*sigma);
			}
		}
		else
		{
			value = -(val_a-mu);
		}
		std::cout << "exact value = " << value << endl;

	}

	return 0;
}