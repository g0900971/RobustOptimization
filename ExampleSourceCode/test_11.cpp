#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_09
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 9, "X"), Y(1, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));


	ROBaseConstraint baseConst = ((X*Z - 2*Z) <= 4);

	ROExprArray unExprA = ROExprArray(2);
	unExprA[0] = Z + 1;
	unExprA[1] = Z - 1;

	ROConstraintSet unConstSet = RORotateSOC(unExprA, (2*Z+2));

	ROConstraint roConst = ROConstraint(baseConst, unConstSet);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}