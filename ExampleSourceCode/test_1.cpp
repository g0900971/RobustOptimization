//
//  ROVar.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 2/9/12.
//  Modifed by Tianjue Lin on 2/9/12
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                 define data for Bike_LP input
	   -----------------------------------------------------------------*/
	/*
	if(argc != 2)
	{
		cerr << "cmd data_path" << endl;
		return -1;
	}
	*/

	//string dataPath = string(argv[1]);

	ROModel model;

	ROVar X(0, 9, "X"), Y(1, 5, "Y");
	ROUn Z;

	ROExpr obj_expr = X + 2*Y;
	model.add(ROMinimize(obj_expr));

	
	ROUnLinConstraintArray baseConstZ = ROUnLinConstraintArray(3);
	baseConstZ[0] = (Z <= 1);
	baseConstZ[2] = (ROExpect(Z) == 0);

	baseConstZ[1] = (-1 <= Z);
	ROBaseConstraint baseConstX = (ROExpect(X*Z - Z) <= 8);

	
	ROExprArray expr_norm_array = ROExprArray(2);
	expr_norm_array[0] = (Z+1);
	expr_norm_array[1] = (Z-1);

	ROExpr expr_norm = (2*Z+2);

	ROUnSOCConstraint normConst = ROUnSOCConstraint(expr_norm, expr_norm_array);
	
	

	ROConstraint roConstA = ROConstraint(baseConstX, baseConstZ, normConst);


	model.add(roConstA);

	model.solve();

	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	std::cout << "Value X = " << model.getVarValue(X) << std::endl;


	return 0;
}


