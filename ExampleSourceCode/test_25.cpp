#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	             RO_V0.03_Case_6               
	   -----------------------------------------------------------------*/

	ROModel model;

	ROVar X(0, 3, "X"), Y(-3, 5, "Y");
	
	ROUn Z1, Z2;

	ROVarDR Y_DR;
	Y_DR.add(Z1);
	Y_DR.add(Z2);

	ROUnVarC obj_expr = X + 2*ROExpect(ROPos(Y_DR.getExpr()));

	ROConstraintSet unConstSet1, unConstSet2;
	
	unConstSet1.add(Z1 <= 1);
	unConstSet1.add(Z1 >= -1);
	unConstSet1.add(Z2 <= 3);
	unConstSet1.add(Z2 >= -1);

	unConstSet2.add(unConstSet1);
	unConstSet2.add(ROExpect(Z1) <= 1 );
	unConstSet2.add(ROExpect(Z2) <= 2 );

	model.add(ROMinimize(obj_expr, unConstSet2));


	ROConstraintSet baseConst = ((X*Z1 + Y_DR.getExpr()) <= 8);

	if(baseConst.getROBaseConst().get() == NULL)
	{
		cout << "Empty main base constraint" << endl;
	}

	ROConstraint roConst = ROConstraint(baseConst, unConstSet1);


	model.add(roConst);

	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}