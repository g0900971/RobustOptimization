#include "ROAllFiles.h"

//-------------------------------------------------- ROME_CMP_2.cpp ---------------------------------------------------
// Description: 
//		A service-constrained inventory management problem.
// 
// Model Setup.
// Input data:
//		T		finite number of time periods;
//		mu		mean of demand "Z(t)";
//		zRange	bound deviation for demand "Z(t)"
//		xMax	order quantity upper limit
//		c		unit ordering cost
//		h		unit holding cost
//		b		unit backorder cost
//		beta	target fill rate
//		
//	Decision variables:
//		X[t]	order quantity in time period t
//		Y[t]	inventory balance at the end of time period t
//
//	Objective:
//		minimize	sum(t)c*X[t] + sum(t)h*Expect(Pos(Y[t]))) + sum(t)b*Expect(Neg(Y[t]))
//	Constraints:
//			s.t.	Y[1] == X[1] - Z[1],
//					Y[t] == Y[t-1] + X[t] - Z[t], for all t =2,..,T
//					Expect(Neg(Y[t])) <= mu*(1-beta), for all t=1,..,T
//					Abs(Z[t]-mu) <= zRange, for all t=1,..,T
//					Expect(Z[t]) = mu, for all t=1,..,T
//---------------------------------------------------------------------------------------------------------------------



using namespace std;

int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                  ROME_CMP_2.m      
	   -----------------------------------------------------------------*/

	ROModel model;

	int T = 2;
	double mu = 220, zRange = 20, xMAX = 260;

	double c = 0.1, h = 0.02, b = 0.2, bEnd = 2, beta = 0.9;

	//ROVarDRArray X(T), Y(T), Y_pos(T), Y_neg(T);
	ROVarDR X1, X2, Y1, Y2, Y_pos1, Y_pos2, Y_neg1, Y_neg2;
	ROUnArray Z(T);

	// Linear Decision Rule :
	X2.addDR(Z[0]);
	Y1.addDR(Z[0]);
	Y2.addDR(Z[0]);
	Y2.addDR(Z[1]);

	Y_pos1.addDR(Z[0]);
	Y_pos2.addDR(Z[0]);
	Y_pos2.addDR(Z[1]);

	Y_neg1.addDR(Z[0]);
	Y_neg2.addDR(Z[0]);
	Y_neg2.addDR(Z[1]);
	/*
	for(int i = 1; i < T; i++)
	{
		for(int j = 0; j < i; j++)
		{
			X[i].addDR(Z[j]);
		}
	}

	for(int i = 0; i < T; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			Y[i].addDR(Z[j]);
		}
		Y_pos[i].addDR(Y[i]);
		Y_neg[i].addDR(Y[i]);
	}
	*/
	// -------- LDR ---------

	ROConstraintSet unConstSet;
	
	for(int i = 0; i < T; i++)
	{
		//unConstSet.add(ROAbs(Z[i]-mu) <= zRange);

		unConstSet.add(Z[i]-mu <= zRange);
		unConstSet.add(Z[i]-mu >= (-1)*zRange);

		unConstSet.add(ROExpect(Z[i]) == mu);
	}

	model.add(ROConstraint((Y1 == X1 - Z[0]), unConstSet));

	model.add(ROConstraint((Y2 == Y1 + X2 - Z[1]), unConstSet));

	/*
	for(int i = 1; i < T; i++)
	{
		model.add(ROConstraint((Y[i] == Y[i-1] + X[i] - Z[i]), unConstSet));
	}
	*/
	/*
	// Fill rate constraint
	for(int i = 0; i < T; i++)
	{
		model.add( ROConstraint((ROExpect(Y_neg[i]) <= mu*(1-beta)), unConstSet));
	}
	*/
	
	// Order quantity limits
		model.add(ROConstraint((X1 >= 0), unConstSet));
		model.add(ROConstraint((X1 <= xMAX), unConstSet));
		model.add(ROConstraint((X2 >= 0), unConstSet));
		model.add(ROConstraint((X2 <= xMAX), unConstSet));
	/*
	for(int i = 0; i < T; i++)
	{
		model.add(ROConstraint((X[i] >= 0), unConstSet));
		model.add(ROConstraint((X[i] <= xMAX), unConstSet));
	}
	*/


	ROUnVarC obj_expr;

		obj_expr += (c*(X1) + h*(Y_pos1) + b*(Y_neg1));

		model.add(ROConstraint((Y_pos1 >= 0), unConstSet));
		model.add(ROConstraint((Y_pos1 >= Y1), unConstSet));

		model.add(ROConstraint((Y_neg1 >= 0), unConstSet));
		model.add(ROConstraint((Y_neg1 >= (-1)*Y1), unConstSet));

		obj_expr += (c*(X2) + h*(Y_pos2) + b*(Y_neg2));

		model.add(ROConstraint((Y_pos2 >= 0), unConstSet));
		model.add(ROConstraint((Y_pos2 >= Y2), unConstSet));

		model.add(ROConstraint((Y_neg2 >= 0), unConstSet));
		model.add(ROConstraint((Y_neg2 >= (-1)*Y2), unConstSet));
	/*
	for(int i = 0; i < T; i++)
	{
		obj_expr += (c*ROExpect(X[i]) + h*ROExpect(Y_pos[i]) + b*ROExpect(Y_neg[i]));

		model.add(ROConstraint((Y_pos[i] >= 0), unConstSet));
		model.add(ROConstraint((Y_pos[i] >= Y[i]), unConstSet));

		model.add(ROConstraint((Y_neg[i] >= 0), unConstSet));
		model.add(ROConstraint((Y_neg[i] >= (-1)*Y[i]), unConstSet));

	}
	*/

	model.add(ROMinimize(obj_expr, unConstSet));
	
	model.solve();


	model.exportModel();

	std::cout << model.getObjValue() << std::endl;


	return 0;
}