#include "ROAllFiles.h"


//-------------------------------------------------- ROME_CMP_4.cpp ---------------------------------------------------
// Description: 
//		A Simple Portfolio Allocation Problem.
// 
// Model Setup.
// Input data:
//		N			number of stocks;
//		mu[]		mean return of stocks;
//		sigma[]		deviation of stocks;
//		gamma		"budget of uncertainty";
//		
//  Uncertain factors:
//		r[]			returns of stocks;
//
//	Decision variables:
//		X[]			portfolio weights
//
//	Objective:
//		maximize	sum(i)[(mu[i] + sigma[i] * Z[i])*X[i]]	
//	Constraints:
//			s.t.	sum(i)X[i] = 1,
//					X[i] >= 0, for all i=1,..,N
//
//---------------------------------------------------------------------------------------------------------------------

using namespace std;

int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                  ROME_CMP_4.m      
	   -----------------------------------------------------------------*/

	ROModel model;

	int N = 150;
	double mu[150], sigma[150], gamma = 4;
	for(int i = 0; i < N; i++)
	{
		mu[i] = 1.15 + (i+1)* (0.05/150);
		double dVal = 2 * (i+1) * N * (N+1);
		sigma[i] = (0.05/450) * sqrt(dVal);
	}

	ROVarArray X(N, 0, ROInfinity, "X");
	ROUnArray Z(N);
	ROUnArray U(N);

	int i = X.getSize();

	// -------------- Uncertainty Set --------------
	ROConstraintSet unConstSet;
	
	for(int i = 0; i < N; i++)
	{

		unConstSet.add(U[i] >= Z[i]);
		unConstSet.add(U[i] >= (-1)*Z[i]);
		unConstSet.add(U[i] <= 1);
	}
	//unConstSet.add(ROUnSOCConstraint(Z, gamma));
	unConstSet.add(RONorm1(Z) <= gamma);
	//unConstSet.add(ROSum(U) <= gamma);
	// ---------------------------------------------

	// Return relations with uncertain factors
	ROExprArray R(N);
	for(int i = 0; i < N; i++)
	{
		R[i] = mu[i] + sigma[i] * Z[i];
	}

	// Constraint
	model.add(ROSum(X) == 1);

	// Objective
	ROExpr obj_expr;
	for(int i = 0; i < N; i++)
	{
		obj_expr += R[i] * X[i];
	}

	model.add(ROMaximize(obj_expr, unConstSet));
	
	model.solve();


	model.exportModel();

	for(int i = 0; i < N; i++)
	{
		std::cout << model.getVarValue(X[i]) << std::endl;
	}

	std::cout << model.getObjValue() << std::endl;

	return 0;
}