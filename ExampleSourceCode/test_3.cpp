#include "ROAllFiles.h"

using namespace std;



int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                
	   -----------------------------------------------------------------*/

	ROUnImplManager::instance().add(boost::shared_ptr<ROUnImpl>(new ROUnImpl(0)));
	ROUnImplManager::instance().clear();
	ROUnImplManager::destroy();
	/*
	ROModel model;

	ROVar X(0, 9, "X"), Y(0, 5, "Y");
	ROVar2DArray var2D_X = ROVar2DArray(2);
	var2D_X[0] = ROVarArray(2);

	var2D_X[1] = ROVarArray(2);

	ROUn Z1;
	*/
	/*
	ROExpr obj_expr = X + 2*Y + var2D_X[0][0] - var2D_X[0][1] * 2 + var2D_X[1][0] + var2D_X[1][1]/2;
	model.add(ROMinimize(obj_expr));

	model.add(var2D_X[0][0] >= 1);
	model.add(var2D_X[0][1] <=10);
	model.add(var2D_X[1][0] >= 0);
	model.add(var2D_X[1][1] >= 5);
	
	
	ROUnLinConstraintArray baseConstZ = ROUnLinConstraintArray(2);
	baseConstZ[0] = (Z1 <= 1);
	baseConstZ[1] = (-1 <= Z1);
	


	ROBaseConstraint baseConstX = (((X-3)*Z1 - Y) == 0);


	ROConstraint roConstA = ROConstraint(baseConstX, baseConstZ);


	model.add(roConstA);


	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;
	*/

	return 0;
}