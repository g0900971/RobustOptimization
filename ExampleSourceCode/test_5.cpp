#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_02
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 9, "X"), Y(0, 5, "Y");
	
	ROUn Z1, Z2;
	ROVarDR Y_DR;
	Y_DR.add(Z1);
	Y_DR.add(Z2);

	ROExpr obj_expr = X + 2*Y;

	model.add(ROMinimize(obj_expr));
	
	ROUnLinConstraintArray unLConstA = ROUnLinConstraintArray(4);
	unLConstA[0] = (Z1 <= 1);
	unLConstA[1] = (-1 <= Z1);
	unLConstA[2] = (Z2 <= 3);
	unLConstA[3] = (0 <= Z1);


	ROBaseConstraint baseConst = (((X-3)*Z1 - Y_DR.getExpr()) <= 8);
	

	ROConstraint roConst = ROConstraint(baseConst, unLConstA);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}