#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	           RO_V0.02_Case_16     
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(-3, 9, "X"), Y(1, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));

	ROExprArray varExprA = ROExprArray(2);
	varExprA[0] = X+1;
	varExprA[1] = X-1;

	ROConstraintSet baseConstSet = RORotateSOC(varExprA, (2*X+2), (X+1));

	model.add(baseConstSet);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}