#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	             RO_V0.03_Case_3                
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 3, "X"), Y(-3, 5, "Y");
	
	ROUn Z1, Z2;

	ROVarDR Y_DR;
	Y_DR.add(Z1);
	Y_DR.add(Z2);

	ROUnVarC obj_expr = X + 2*RONeg(Y_DR.getExpr());

	ROConstraintSet unConstSet;
	
	unConstSet.add(Z1 <= 1);
	unConstSet.add(Z1 >= -1);
	unConstSet.add(Z2 <= 3);
	unConstSet.add(Z2 >= 0);

	model.add(ROMinimize(obj_expr, unConstSet));


	ROBaseConstraint baseConst = ((X*Z1 + Y_DR.getExpr()) <= 8);


	ROConstraint roConst = ROConstraint(baseConst, unConstSet);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}