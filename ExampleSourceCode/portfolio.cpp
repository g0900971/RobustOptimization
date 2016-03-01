#include "ROAllFiles.h"

//-------------------------------------------------- ROME_CMP_3.cpp ---------------------------------------------------
// Description: 
//		A warehouse management problem.
// 
// Model Setup.
// Input data:
//		T			finite number of time periods
//		M			number of product types
//		N			number of storage locations
//		s[]			unit storage cost for different locations
//		r[]			unit retreve cost for different locations
//		c[]			capacities for different locations
//		a[][]		scheduled arrival quantity of all products in all time periods
//		mu[][]		mean of products demand
//		sigma		demand deviation
//		
//	Decision variables:
//		V[][][]		number of arriving pallets of product i assigned to storage j at start of t
//		W[][][]		number of product i retrieved from storage j after demand realized in period t
//		X[][][]		number of pallets of product i in storage j at the start of each period t
//
//	Objective:
//		minimize	Expect(sum(i,j,t)s[]*V[][][] + sum(i,j,t)r[]*W[][][])
//	Constraints:
//			s.t.	sum(j)V[i][j][t] = a[i][t], for all i, t
//					sum(j)W[i][j][t] = d[i][t], for all i, t
//					X[i][j][t+1] = X[i][j][t] + V[i][j][t] - W[i][j][t], for all i, j, t
//					X[i][j][1] = 0, for all i, j 
//					sum(i)(X[i][j][t] + V[i][j][t]) <= c[j], for all j, t
//					V[i][j][t] >= 0, W[i][j][t] >= 0, X[i][j][t] >= 0, for all i, j, t
//
//---------------------------------------------------------------------------------------------------------------------

using namespace std;

int main(int argc, char**argv)
{
	/* ---------------------------------------------------------------------------
	/*	                  ROME_CMP_3.m      
	   -------------------------------------------------------------------------*/

	ROModel model;

	typedef ROArray<ROVarDRArray> ROVar2DDRArray;
	typedef ROArray<ROVar2DDRArray> ROVar3DDRArray;
	typedef ROArray<ROExprArray> ROExpr2DArray;
	typedef ROArray<ROUnArray> ROUn2DArray;

	
	int T = 3, M = 3, N = 5;
	double s[5]={1, 1.5, 2, 3, 100}, r[5]={1, 1.5, 2, 3, 100}, c[5]={150, 300, 450, 600, 10000},
		sigma = 0;

	double a[3][3]={{350, 350, 350}, {350, 350, 450}, {100, 100, 250}}, 
		mu[3][3]={{290, 190, 450}, {100, 470, 370}, {60, 70, 200}};

	ROExpr2DArray D(M);
	ROVar3DDRArray V(M), W(M), X(M);
	for(int i = 0; i < M; i++)
	{
		D[i] = ROExprArray(T);
		V[i] = ROVar2DDRArray(N);
		W[i] = ROVar2DDRArray(N);
		X[i] = ROVar2DDRArray(N);

		for(int j = 0; j < N; j++)
		{
			V[i][j] = ROVarDRArray(T);
			W[i][j] = ROVarDRArray(T);
			X[i][j] = ROVarDRArray(T+1);
		}
	}

	// ------------------------ Linear Decision Rule -----------------------------
	*/
	for(int i = 0; i < M; i++)
	{
		for(int t = 0; t < T; t++)
		{
			D[i][t] = mu[i][t];
		}
	}
		
	// ------------------------------- Constraints -------------------------------
	// X[i][j][0] == 0, X[i][j][t], V[i][j][t], W[i][j][t] >= 0
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			model.add((X[i][j][0] == 0));
			for(int t = 0; t <= T; t++)
			{
				model.add((X[i][j][t] >= 0));
				if(t < T)
				{
					model.add((V[i][j][t] >= 0));
					model.add((W[i][j][t] >= 0));
				}
			}
		}
	}
	
	// sum(j)V[i][j][t] == a[i][t], for all i, t
	// sum(j)W[i][j][t] == d[i][t], for all i, t
	for(int i = 0; i < M; i++)
	{
		for(int t = 0; t < T; t++)
		{
			ROExpr sumVj, sumWj;
			for(int j = 0; j < N; j++)
			{
				sumVj += V[i][j][t];
				sumWj += W[i][j][t];
			}
			model.add((sumVj == a[i][t]));
			model.add((sumWj == D[i][t]));
		}
	}

	// X[i][j][t+1] = X[i][j][t] + V[i][j][t] - W[i][j][t], for all i, j, t
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			for(int t = 0; t < T; t++)
			{
				model.add((X[i][j][t+1] == X[i][j][t] + V[i][j][t] - W[i][j][t]));
			}
		}
	}

	
	// sum(i)(X[i][j][t] + V[i][j][t]) <= c[j], for all j, t
	for(int j = 0; j < N; j++)
	{
		for(int t = 0; t < T; t++)
		{
			ROExpr sumXVi;
			for(int i = 0; i < M; i++)
			{
				sumXVi += (X[i][j][t] + V[i][j][t]);
			}
			model.add((sumXVi <= c[j]));
		}
	}
	// ---------------------------------------------------------------------------
	

	// -------------------------------- Objective --------------------------------
	// Expect(sum(i,j,t)s[]*V[][][] + sum(i,j,t)r[]*W[][][])
	ROExpr obj_expr, temObjExpr;
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			for(int t = 0; t < T; t++)
			{
				temObjExpr += (s[j] * V[i][j][t] + r[j] * W[i][j][t]);
			}
		}
	}
	// ---------------------------------------------------------------------------


	model.add(ROMinimize(temObjExpr));
	
	model.solve();

	std::cout << model.getStatus() << std::endl;
	std::cout << model.getObjValue() << std::endl;

	//model.exportModel();

	return 0;
}