#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	             RO_V0.03_Case_1                
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 4, "X"), Y(-2, 5, "Y");
	
	ROUn Z;

	ROVarDR Y_DR;
	Y_DR.add(Z);

	ROUnVarC obj_expr = X + ROAbs(Y);

	model.add(ROMinimize(obj_expr));


	ROBaseConstraint baseConst = (((X-3)*Z + Y_DR.getExpr()) <= 8);

	ROConstraintSet unConstSet;
	
	unConstSet.add(Z <= 1);
	unConstSet.add(Z >= -1);

	ROConstraint roConst = ROConstraint(baseConst, unConstSet);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}