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
	/*	                  ROME_CMP_1.m      
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, ROInfinity, "X", EnumROBool), Y(0, ROInfinity, "X");
	
	ROUn Z;

	ROExpr obj_expr = X*12 + 15*Y;

	ROConstraintSet unConstSet;
	
	unConstSet.add(Z >= 1.5);
	unConstSet.add(Z <= 2.5);

	model.add(ROMaximize(obj_expr));


	ROBaseConstraintArray baseConstA(2);
	baseConstA[0] = (X + Z*Y <= 40);
	baseConstA[1] = (4*X + 3*Y <= 120);

	ROConstraintArray roConstA(2);

	roConstA[0] = ROConstraint((X + Z*Y <= 40), unConstSet);
	roConstA[1] = ROConstraint((4*X + 3*Y <= 120), unConstSet);

	model.add(roConstA);
	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}