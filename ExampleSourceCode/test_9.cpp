#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_06
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 9, "X");
	ROIntVar Y(1.5, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));


	ROBaseConstraint baseConst = ((X*Z - Z) <= X);

	ROConstraintSet unConstSet;
	
	unConstSet.add(ROSq(Z) <= 2);

	ROConstraint roConst = ROConstraint(baseConst, unConstSet);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;

	std::cout << "Value Y = " << model.getVarValue(Y) << std::endl;


	return 0;
}