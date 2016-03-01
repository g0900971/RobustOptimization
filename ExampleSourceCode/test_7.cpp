#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_03
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 9, "X"), Y(0, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));
	
	/*
	ROUnLinConstraintArray unLConstA = ROUnLinConstraintArray(2);
	unLConstA[0] = (Z <= 1);
	unLConstA[1] = (-1 <= Z);
	*/


	ROBaseConstraint baseConst = ((X*Z + Y) <= 8);
	

	ROConstraint roConst = ROConstraint(baseConst, (ROAbs(Z) <= 1));


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}