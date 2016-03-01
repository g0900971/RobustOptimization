#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_13
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(-3, 9, "X"), Y(1, 5, "Y");
	
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));

	ROConstraintSet baseConstSet;

	baseConstSet.add( (ROSq(X) + Y <= 8) );


	model.add(baseConstSet);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}