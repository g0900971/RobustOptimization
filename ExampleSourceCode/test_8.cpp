#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_05
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 9, "X"), Y(1, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));


	ROBaseConstraint baseConst = ((X*Z - 2*Z) <= 8);

	ROConstraintSet unConstSet;
	unConstSet.add((RONeg(Z) <= 1));
	unConstSet.add(Z <= 3);
	

	ROConstraint roConst = ROConstraint(baseConst, unConstSet);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}