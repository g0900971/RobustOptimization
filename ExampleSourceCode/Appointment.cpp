#include "ROAllFiles.h"


//-------------------------------------------------- test_appointment_scheduling.cpp ---------------------------------------------------
// Description: 
//		Appointment scheduling problem in health care.
// 
// Model Setup.
// Input data:
//		n			total number of patients to be scheduled;
//		L			session length pre-determined for the consultation of n patients;
//		tau[i]		the tolerance threshold of delay of i_th patient, for all i=1,..,n;		
//		tau[n+1]	doctor's tolerance on his/her overtime;
//	
//	Uncertain variables:
//		s[i]		service time of the i_th patient, for all i=1,..n;
//		w[i]		waiting time of the i_th patient, for all i=1,..,n;
//		w[n+1]		doctor's overtime;
//
//	Decision variables:
//		X[i]		appointment time for the i_th patient;
//		X[n+1]		where X[n+1] = L;
//		alpha		worst case DUM.
//
//
//	Objective:
//		minimize	alpha
//	Constraints:
//			s.t.	Expect( ROPos(a(w[i] - tau[i]) + 1) ) <= alpha, for all i=1,..,n
//					w[1] == 0,
//					w[i] == max{w[i-1] + s[i-1] - (x[i]- x[i-1]), 0}, for all i=2,..,n+1
//					x[1] == 0,
//					x[i-1] <= x[i], for all i=2,..,n+1
//					x[n+1] == L,
//					alpha \in {0, 1}
//---------------------------------------------------------------------------------------------------------------------



using namespace std;

int main(int argc, char**argv)
{
	/* ---------------------------------------------------------------------------
	/*	            Appointment scheduling for homogeneous patients    
	   -------------------------------------------------------------------------*/

	ROModel model;

	int n = 1;
	double L = 5, tau = 4, mu = 2, sigma = 2, z_L = -1, z_H = 1;

	//double epsilon[] = {1, 1.5, 2, 2.5, 3, 3.5, 4};
	double epsilon[] = {0.4};

	// define basic variables without uncertainty attached
	ROVar X1, X2(0, ROInfinity, "X2");	// single variables
	ROVar X_array(n);					// an array of basic variables

	// define uncertain variables
	ROUn Z1, Z2, Z3;						// single uncertain variables
	ROUnArray Z_array(n);				// an array of uncertain variables

	// define adjustable or decision rule variables
	ROVarDR Y1;							// single adjustable variables
	ROVarDRArray Y_arrayDR(n);			// an array of adjustable variables

	// attach the relevant uncertaint variables to adjustable variables
	Y1.addDR(Z1);

	// expression definition
	ROExpr expr1, expr2, expr3;
	expr1 += X1 + 3*X2 + X_array[0];
	expr2 += ROExpect(X1*Z1 + 2*Z2);	// the expected form of expression
	expr3 += X2*X2 + X1*X2;

	// Uncertainty Set :
	ROConstraintSet unconstSet;

	unconstSet.add(Z1 <= 10);
	unconstSet.add(Z1 + 2*Z2 <= 0);

	ROExprArray exprArray1(2), exprArray2(2);						// an array of uncertain expressions
	exprArray1[0] = Z1 + 1;
	exprArray1[1] = 3*Z2;
	exprArray2[0] = Z1;
	exprArray2[1] = Z2;

	unconstSet.add(ROUnSOCConstraint(exprArray1, (5*Z1 + 2)));		// SOCP uncertain constraint
	unconstSet.add(RORotateSOC(exprArray2, Z3));					// rotated SOCP uncertain constraint
	unconstSet.add(ROExpect(Z2) ==3);								// expected form of uncertain constraint
	unconstSet.add(RONorm1(exprArray1) <= 1);						// norm1 uncertain constraint


	ROVarArray X(n+1, 0, ROInfinity, "X"), a(n+1, 0, ROInfinity, "a");
	ROVarDRArray X_DR(n+1), S_DR(n);
	ROUnArray w(n+1), z(n);

	ROVar alpha(0, 1, "alpha");

	// Decision Rule :
	for(int i = 0; i < n; i++)
	{
		X_DR[i+1].addDR(w[i+1]);
		S_DR[i].addDR(z[i]);
	}


	// Uncertainty Set :
	ROConstraintSet unConstSet;
	
	unConstSet.add(w[0] == 0);
	for(int i = 0; i < n; i++)
	{
		unConstSet.add(ROExpect(z[i]) == 0);
		//unConstSet.add(ROAbs(z[i]) <= 1);
		unConstSet.add(z[i] <= z_H);
		unConstSet.add(z_L <= z[i]);
		unConstSet.add(w[i+1] >= 0);

		
		ROExpr iExpr;
		for(int j = 0; j <= i; j++)
		{
			iExpr += z[j];
		}
		unConstSet.add( ROExpect( ROAbs(iExpr) ) <= epsilon[i] );
		
	}

	// Constraints :
	model.add(X[0] == 0);
	for(int i = 1; i <= n; i++)
	{
		model.add(ROConstraint(X_DR[i] >= 0, unConstSet));
		model.add(ROConstraint(X_DR[i] >= a[i]*(w[i] - tau) + 1, unConstSet));

		model.add(ROConstraint(S_DR[i-1] == sigma*z[i-1] + mu));

		model.add(ROConstraint(ROExpect(X_DR[i]) <= alpha, unConstSet));

		model.add(ROConstraint(w[i] >= w[i-1] + S_DR[i-1] - (X[i] - X[i-1]), unConstSet));

		model.add(X[i-1] <= X[i]);
	}
	model.add(X[n] == L);

	model.add(ROMinimize(alpha));
	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;

	
	for(int i = 0; i < n; i++)
	{
		std::cout << model.getVarValue(X[i]) << std::endl;
		//std::cout << model.getVarValue(a[i]) << std::endl;
	}
	


	return 0;
}