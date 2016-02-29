//
//  roexprfunctions.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 3/9/12.
//
//

#include "roexprfunctions.h"
#include "ROObjective.h"
#include "ROBaseConstraint.h"
#include "ROConstraintSet.h"
#include "ROUnSOCConstraint.h"
#include "ROExprImpl.h"
#include "ROExpr.h"
#include "ROVar.h"
#include "ROIntVar.h"
#include "ROBinVar.h"
#include "ROUn.h"
#include "ROVarDR.h"
#include "ROUnVarC.h"
#include "rotempimpl.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Objective Function

ROObjective ROMinimize(const ROExpr& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMin);
}

ROObjective ROMinimize(const ROVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMin);
}

ROObjective ROMinimize(const ROIntVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMin);
}

ROObjective ROMinimize(const ROBinVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMin);
}

ROObjective ROMinimize(const ROExpr& p_expr, const ROConstraintSet& p_constSet)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), p_constSet, EnumMin);
}

ROObjective ROMinimize(const ROUnVarC& p_unVarC)
{
	return ROObjective(p_unVarC, EnumMin);
}

ROObjective ROMinimize(const ROUnVarC& p_unVarC, const ROConstraintSet& p_constSet)
{
	return ROObjective(p_unVarC, p_constSet, EnumMin);
}


ROObjective ROMaximize(const ROExpr& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMax);
}

ROObjective ROMaximize(const ROVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMax);
}

ROObjective ROMaximize(const ROIntVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMax);
}

ROObjective ROMaximize(const ROBinVar& p_expr)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), EnumMax);
}

ROObjective ROMaximize(const ROExpr& p_expr, const ROConstraintSet& p_constSet)
{
	return ROObjective(boost::shared_ptr<ROExpr>(new ROExpr(p_expr)), p_constSet, EnumMax);
}

ROObjective ROMaximize(const ROUnVarC& p_unVarC)
{
	return ROObjective(p_unVarC, EnumMax);
}

ROObjective ROMaximize(const ROUnVarC& p_unVarC, const ROConstraintSet& p_constSet)
{
	return ROObjective(p_unVarC, p_constSet, EnumMax);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Functional Operations related to "expect" "positive" "negative" "absolute"
// 

#define ROSUM_IMPL(ELEMENT_TYPE, ARRAY) \
	ELEMENT_TYPE val = 0; \
\
	size_t iSize = ARRAY.getSize(); \
	for(int i = 0; i < iSize; i++) \
	{ \
	 	val += ARRAY[i]; \
	} \
	return val;

RONum ROSum(const RONumArray& p_numArray)
{
	ROSUM_IMPL(RONum, p_numArray);
}

ROExpr ROSum(const ROExprArray& p_exprArray)
{
	ROSUM_IMPL(ROExpr, p_exprArray);
}

// TBA -----------------
ROExpr ROSum(const ROVarArray& p_varArray)
{
	ROSUM_IMPL(ROExpr, p_varArray);
}

ROExpr ROSum(const ROUnArray& p_unArray)
{
	ROSUM_IMPL(ROExpr, p_unArray);
}


ROExpr ROExpect(const ROUn& p_un)
{
	ROExpr expr;
	expr.expect(p_un);
	return expr;
}

ROExpr ROExpect(const ROExpr& p_expr)
{
	ROExpr expr;
	expr.expect(p_expr);
	return expr;
}

ROExpr ROExpect(const ROVarDR& p_varDR)
{
	return ROExpect(p_varDR.getExpr());
}


ROUnVarC ROExpect(const ROUnVarC& p_unVarC)
{
	ROExpr expr, expr1;
	expr = *(p_unVarC.getExpr().get());
	if(expr.getImpl()->getType() != EnumVar && expr.getImpl()->getType() != EnumQVar)
	{
		expr1.expect(expr);
	}
	else
	{
		expr1 = expr;
	}

	ROUnVarC unVarC;
	unVarC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr1)));
	unVarC.setConstSet(p_unVarC.getConstSet());

	return unVarC;
}


ROUnVarC ROPos(const ROUn& p_un)
{
	ROExpr p_expr;
	p_expr += p_un;

	return ROPosNeg<ROUn, std::plus<RONum> >(p_expr);
}


ROUnVarC ROPos(const ROVar& p_var)
{
	ROExpr p_expr;
	p_expr += p_var;

	return ROPosNeg<ROVar, std::plus<RONum> >(p_expr);
}

ROUnVarC ROPos(const ROIntVar& p_var)
{
	return ROPos(p_var.getVar());
}

ROUnVarC ROPos(const ROBinVar& p_var)
{
	return ROPos(p_var.getVar());
}

ROUnVarC RONeg(const ROIntVar& p_var)
{
	return RONeg(p_var.getVar());
}

ROUnVarC RONeg(const ROBinVar& p_var)
{
	return RONeg(p_var.getVar());
}

ROUnVarC ROPos(const ROExpr& p_expr)
{
	ROExprType type = p_expr.getImpl()->getType();

	// TBA
	if(type == EnumUn || type == EnumExUn)
	{
		return ROPosNeg<ROUn, std::plus<RONum> >(p_expr);
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		return ROPosNeg<ROVar, std::plus<RONum> >(p_expr);
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}

ROUnVarC ROPos(const ROVarDR& p_varDR)
{
	return ROPos(p_varDR.getExpr());
}

ROUnVarC ROPos(const ROUnVarC& p_unC)
{
	ROExprType type = p_unC.getExpr()->getImpl()->getType();

	// TBA
	if(type == EnumUn || type == EnumExUn)
	{
		ROExpr expr;
		ROUn un_Z;
		expr += un_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(un_Z >= *(p_unC.getExpr().get()));
		uncertaintySet.add(un_Z >= 0);
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		ROExpr expr;
		ROVar var_Z;
		expr += var_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(var_Z >= *(p_unC.getExpr().get()));
		uncertaintySet.add(var_Z >= 0);
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}

ROUnVarC RONeg(const ROUn& p_un)
{
	ROExpr p_expr;
	p_expr += p_un;

	return ROPosNeg<ROUn, std::minus<RONum> >(p_expr);
}

ROUnVarC RONeg(const ROVar& p_var)
{
	ROExpr p_expr;
	p_expr += p_var;

	return ROPosNeg<ROVar, std::minus<RONum> >(p_expr);
}


ROUnVarC RONeg(const ROExpr& p_expr)
{
	ROExprType type = p_expr.getImpl()->getType();

	// TBA
	if(type == EnumUn || type == EnumExUn)
	{
		return ROPosNeg<ROUn, std::minus<RONum> >(p_expr);
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		return ROPosNeg<ROVar, std::minus<RONum> >(p_expr);
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}

ROUnVarC RONeg(const ROVarDR& p_varDR)
{
	return RONeg(p_varDR.getExpr());
}

ROUnVarC RONeg(const ROUnVarC& p_unC)
{
	ROExprType type = p_unC.getExpr()->getImpl()->getType();

	// TBA
	if(type == EnumUn || type == EnumExUn)
	{
		ROExpr expr;
		ROUn un_Z;
		expr += un_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(un_Z >= (-1) * (*(p_unC.getExpr().get())));
		uncertaintySet.add(un_Z >= 0);
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		ROExpr expr;
		ROVar var_Z;
		expr += var_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(var_Z >= (-1) * (*(p_unC.getExpr().get())));
		uncertaintySet.add(var_Z >= 0);
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}


ROUnVarC ROAbs(const ROUn& p_un)
{
	ROExpr p_expr;
	p_expr += p_un;

	return ROAbsolute<ROUn>(p_expr);
}

ROUnVarC ROAbs(const ROVar& p_var)
{
	ROExpr p_expr;
	p_expr += p_var;

	return ROAbsolute<ROVar>(p_expr);
}

ROUnVarC ROAbs(const ROIntVar& p_var)
{
	return ROAbs(p_var.getVar());
}

ROUnVarC ROAbs(const ROBinVar& p_var)
{
	return ROAbs(p_var.getVar());
}

ROUnVarC ROAbs(const ROExpr& p_expr)
{
	ROExprType type = p_expr.getImpl()->getType();

	// TBA
	if(type == EnumUn || type == EnumExUn)
	{
		return ROAbsolute<ROUn>(p_expr);
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		return ROAbsolute<ROVar>(p_expr);
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}

ROUnVarC ROAbs(const ROVarDR& p_varDR)
{
	return ROAbs(p_varDR.getExpr());
}


ROUnVarC ROAbs(const ROUnVarC& p_unC)
{
	ROExprType type = p_unC.getExpr()->getImpl()->getType();

	// TBA 
	if(type == EnumUn || type == EnumExUn)
	{
		ROExpr expr;
		ROUn un_Z;
		expr += un_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(un_Z >= (-1) * (*(p_unC.getExpr().get())));
		uncertaintySet.add(un_Z >= (*(p_unC.getExpr().get())));
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else if(type == EnumVar || type == EnumQVar || type == EnumNull)
	{
		ROExpr expr;
		ROVar var_Z;
		expr += var_Z;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add(var_Z >= (-1) * (*(p_unC.getExpr().get())));
		uncertaintySet.add(var_Z >= (*(p_unC.getExpr().get())));
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));
	
		return unC;
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}


ROUnVarC ROSq(const ROUn& p_un)
{
	ROExpr p_expr;
	p_expr += p_un;

	return ROSquare<ROUn>(p_expr);
}

/*
#define ROSQ_IMPL(ELEMENT_A, ELEMENT_B, ELEMENT_C, ELEMENT_TYPE)  \ 
		ROExpr p_expr; \
		p_expr = p_expr + ELEMENT_A; \
\
		return ROPolyApprox<ELEMENT_TYPE>(p_expr, ELEMENT_B, ELEMENT_C); 

		*/

// Global Function Version 0.2
// A Polyhedral Approximation for SOCP
// Date: 2013-04-30
ROUnVarC ROSq(const ROUn& p_un, int p_n, double p_beta)
{
	ROExpr p_expr;
	p_expr += p_un;

	return ROPolyApprox<ROUn>(p_expr, p_n, p_beta);
	//ROSQ_IMPL(p_un, p_n, p_beta, ROUn);
}

// Global Function Version 0.2
// A Polyhedral Approximation for SOCP
// Date: 2013-04-30
ROUnVarC ROSq(const ROVar& p_var, int p_n, double p_beta)
{
	ROExpr p_expr;
	p_expr += p_var;

	return ROPolyApprox<ROVar>(p_expr, p_n, p_beta);
}

ROUnVarC ROSq(const ROIntVar& p_var, int p_n, double p_beta)
{
	return ROSq(p_var.getVar(), p_n, p_beta);
}

ROUnVarC ROSq(const ROBinVar& p_var, int p_n, double p_beta)
{
	return ROSq(p_var.getVar(), p_n, p_beta);
}

// Global Function Version 0.2
// A Polyhedral Approximation for SOCP
// Date: 2013-04-30
ROUnVarC ROSq(const ROExpr& p_expr, int p_n, double p_beta)
{
	return ROPolyApprox<ROExpr>(p_expr, p_n, p_beta);
}

// ----------- ROSq( ROVar& )------------
ROUnVarC ROSquareVar(const ROExpr& p_expr)
{
	ROExpr expr;
	ROVar un_X(0, ROInfinity, "Sq");
	expr += un_X;

	ROConstraintSet uncertaintySet;
	uncertaintySet.add( (p_expr * p_expr) <= un_X);

	ROUnVarC unC;
	unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
	unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

	return unC;
}
// ---------------- End -----------------

ROUnVarC ROSq(const ROVar& p_var)
{
	ROExpr p_expr;
	p_expr += p_var;

	return ROSquareVar(p_expr);
}

ROUnVarC ROSq(const ROIntVar& p_var)
{
	return ROSq(p_var.getVar());
}

ROUnVarC ROSq(const ROBinVar& p_var)
{
	return ROSq(p_var.getVar());
}

ROUnVarC ROSq(const ROExpr& p_expr)
{
	ROExprType type = p_expr.getImpl()->getType();
	if(type == EnumUn)
	{
		return ROSquare<ROUn>(p_expr);
	}
	else if(type == EnumVar)
	{
		return ROSquareVar(p_expr);
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}

ROUnVarC ROSq(const ROVarDR& p_varDR)
{
	return ROSq(p_varDR.getExpr());
}


ROUnVarC ROSq(const ROUnVarC& p_unC)
{
	ROExprType type = p_unC.getExpr()->getImpl()->getType();
	ROExpr& expr0 = *(p_unC.getExpr().get());
	
	if(type == EnumUn)
	{
		ROExpr expr1;
		ROUn un_Z;
		expr1 += un_Z;

		ROConstraintSet uncertaintySet;
		ROExprArray expr_array = ROExprArray(2);
		expr_array[0] += expr0;
		expr_array[1] += (un_Z - 1)/2;
		ROExpr expr_rhs = (un_Z + 1)/2;
		ROUnSOCConstraint unSOCConst(expr_array, expr_rhs);
		uncertaintySet.add(unSOCConst);
		uncertaintySet.add(*(p_unC.getConstSet().get()));


		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr1)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return unC;
	}
	else if(type == EnumVar)
	{
		ROExpr expr2;
		ROVar un_X(0, ROInfinity, "Sq");
		expr2 += un_X;

		ROConstraintSet uncertaintySet;
		uncertaintySet.add( (expr0 * expr0) <= un_X );
		uncertaintySet.add(*(p_unC.getConstSet().get()));

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr2)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return unC;		
	}
	else
	{
        ROExceptionTypeIncompatible exp;
		throw exp;
	}
}

// --------------------------------------------------------------------------------------------------------------------

ROUnVarC RONormInf(const ROExprArray& p_exprArray)
{
	size_t iSizeArray = p_exprArray.getSize();
	if(iSizeArray < 1)
	{
		ROExceptionOutRange exp;
        throw exp;		
	}

	ROExprType exprType = (p_exprArray[0]).getImpl()->getType();
	if(exprType == EnumVar)
	{
		ROExpr expr1;
		ROVar var_X(RONInfinity, ROInfinity, "NormInf");
		expr1 += var_X;

		ROConstraintSet uncertaintySet;
		for(int i = 0; i < iSizeArray; i++)
		{
			uncertaintySet.add( expr1 >= p_exprArray[i] );
		}

		ROUnVarC varC;
		varC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr1)));
		varC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return varC;	
	}
	else
	{
		ROExpr expr2;
		ROUn un_X;
		expr2 += un_X;

		ROConstraintSet uncertaintySet;
		for(int i = 0; i < iSizeArray; i++)
		{
			uncertaintySet.add( expr2 >= p_exprArray[i] );
		}

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr2)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return unC;
	}
}

template<class T>
ROUnVarC RoNormInfFunctionCall(const T& pArray)
{
	ROExprArray exprArray;

	size_t iSize = pArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(pArray[i]);
	}
	
	return RONormInf(exprArray);
}

ROUnVarC RONormInf(const ROVarArray& p_varArray)
{
	return RoNormInfFunctionCall<ROVarArray>(p_varArray);
}


ROUnVarC RONormInf(const ROUnArray& p_unArray)
{
	return RoNormInfFunctionCall<ROUnArray>(p_unArray);
}

template<class T>
ROUnVarC RONorm1FunctionCall(const T& pArray)
{
	ROUnVarC expr;

	size_t iSize = pArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		expr += ROAbs(pArray[i]);
	}

	return expr;
}

ROUnVarC RONorm1(const ROExprArray& p_exprArray)
{
	return RONorm1FunctionCall<ROExprArray>(p_exprArray);
}

ROUnVarC RONorm1(const ROVarArray& p_varArray)
{
	return RONorm1FunctionCall<ROVarArray>(p_varArray);
}

ROUnVarC RONorm1(const ROUnArray& p_unArray)
{
	return RONorm1FunctionCall<ROUnArray>(p_unArray);
}

// Date: 2013-05-21, Version 0.2
// Adding Norm2 functions for ROVarArray, ROUnArray and ROexprArray
// Modified by: Meilin Zhang 

ROUnVarC RONorm2(const ROExprArray& p_exprArray)
{
	size_t iSizeArray = p_exprArray.getSize();
	if(iSizeArray < 1)
	{
		ROExceptionOutRange exp;
        throw exp;		
	}

	ROExprType exprType = (p_exprArray[0]).getImpl()->getType();
	if(exprType == EnumVar)
	{
		ROExpr expr1;
		ROVar var_X(RONInfinity, ROInfinity, "Norm2");
		expr1 += var_X;

		ROConstraintSet& uncertaintySet = RORotateSOC(p_exprArray, expr1);

		ROUnVarC varC;
		varC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr1)));
		varC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return varC;	
	}
	else
	{
		ROExpr expr2;
		ROUn un_X;
		expr2 += un_X;

		ROConstraintSet& uncertaintySet = RORotateSOC(p_exprArray, expr2);

		ROUnVarC unC;
		unC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr2)));
		unC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

		return unC;
	}
}

template<class T>
ROUnVarC RONorm2FunctionCall(const T& pArray)
{
	ROExprArray exprArray;

	size_t iSize = pArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(pArray[i]);
	}
	
	return RONorm2(exprArray);
}

ROUnVarC RONorm2(const ROVarArray& p_varArray)
{
	return RONorm2FunctionCall<ROVarArray>(p_varArray);
}

ROUnVarC RONorm2(const ROUnArray& p_unArray)
{
	return RONorm2FunctionCall<ROUnArray>(p_unArray);
}

// -------  x^2 + y^2 + z^2 + ... <= u, u >= 0
ROConstraintSet RORotateSOC(const ROExprArray& p_exprArray, const ROExpr& p_expr)
{
	size_t iSizeArray = p_exprArray.getSize();
	if(iSizeArray < 1)
	{
		ROExceptionOutRange exp;
        throw exp;		
	}

	ROExprType exprType = (p_exprArray[0]).getImpl()->getType();
	if(exprType == EnumVar)
	{
		ROVar var_U(0, ROInfinity, "Norm2_U"), var_V(0, ROInfinity, "Norm2_V");

		ROConstraintSet uncertaintySet;
		uncertaintySet.add( var_U == 1 );
		uncertaintySet.add( var_V == p_expr);

		ROExpr expr1;
		for(int i = 0; i < iSizeArray; i++)
		{
			expr1 += (p_exprArray[i]) * (p_exprArray[i]);
		}
		uncertaintySet.set( expr1 <= var_U * var_V);

		return uncertaintySet;
	}
	else
	{
		ROExprArray expr2_array;
		ROUn un_Z;

		for(int i = 0; i < iSizeArray; i++)
		{
			expr2_array.add(p_exprArray[i]);
		}
		expr2_array.add((un_Z - p_expr)/2);

		ROUnSOCConstraint unSOCconst = ROUnSOCConstraint(expr2_array, ((un_Z + p_expr)/2) );

		ROConstraintSet uncertaintySet;
		uncertaintySet.add( unSOCconst );
		uncertaintySet.add( un_Z == 1 );

		return uncertaintySet;
	}
}

ROConstraintSet RORotateSOC(const ROExprArray& p_exprArray, const ROExpr& p_expr1, const ROExpr& p_expr2)
{
	size_t iSizeArray = p_exprArray.getSize();
	if(iSizeArray < 1)
	{
		ROExceptionOutRange exp;
        throw exp;		
	}

	ROExprType exprType = (p_exprArray[0]).getImpl()->getType();
	if(exprType == EnumVar)
	{
		ROVar var_U(0, ROInfinity, "Norm2_U"), var_V(0, ROInfinity, "Norm2_V");

		ROConstraintSet uncertaintySet;
		uncertaintySet.add( var_U == p_expr1 );
		uncertaintySet.add( var_V == p_expr2);

		ROExpr expr1;
		for(int i = 0; i < iSizeArray; i++)
		{
			expr1 += (p_exprArray[i]) * (p_exprArray[i]);
		}
		uncertaintySet.set( expr1 <= var_U * var_V);

		return uncertaintySet;
	}
	else
	{
		ROExprArray expr2_array;

		for(int i = 0; i < iSizeArray; i++)
		{
			expr2_array.add(p_exprArray[i]);
		}
		expr2_array.add((p_expr1 - p_expr2)/2);

		ROUnSOCConstraint unSOCconst = ROUnSOCConstraint(expr2_array, ((p_expr1 + p_expr2)/2) );

		ROConstraintSet uncertaintySet;
		uncertaintySet.add( unSOCconst );

		return uncertaintySet;
	}
}


ROConstraintSet RORotateSOC(const ROVarArray& p_varArray, const ROExpr& p_expr)
{
	ROExprArray exprArray;

	size_t iSize = p_varArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(p_varArray[i]);
	}

	return RORotateSOC(exprArray, p_expr);
}

ROConstraintSet RORotateSOC(const ROVarArray& p_varArray, const ROExpr& p_expr1, const ROExpr& p_expr2)
{
	ROExprArray exprArray;

	size_t iSize = p_varArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(p_varArray[i]);
	}

	return RORotateSOC(exprArray, p_expr1, p_expr2);
}

ROConstraintSet RORotateSOC(const ROUnArray& p_unArray, const ROExpr& p_expr)
{
	ROExprArray exprArray;

	size_t iSize = p_unArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(p_unArray[i]);
	}

	return RORotateSOC(exprArray, p_expr);
}

ROConstraintSet RORotateSOC(const ROUnArray& p_unArray, const ROExpr& p_expr1, const ROExpr& p_expr2)
{
	ROExprArray exprArray;

	size_t iSize = p_unArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(p_unArray[i]);
	}

	return RORotateSOC(exprArray, p_expr1, p_expr2);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ----------------------------------  Binaray operators among ROVar ROIntVar ROBinVar  -------------------------------

ROExpr operator + (const ROVar& lhs, const ROIntVar& rhs)
{
	return (lhs + rhs.getVar());
}

ROExpr operator - (const ROVar& lhs, const ROIntVar& rhs)
{
	return (lhs - rhs.getVar());
}

ROExpr operator * (const ROVar& lhs, const ROIntVar& rhs)
{
	return (lhs * rhs.getVar());
}


ROExpr operator + (const ROIntVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() + rhs);
}

ROExpr operator - (const ROIntVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() - rhs);
}

ROExpr operator * (const ROIntVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() * rhs);
}

ROExpr operator + (const ROVar& lhs, const ROBinVar& rhs)
{
	return (lhs + rhs.getVar());
}

ROExpr operator - (const ROVar& lhs, const ROBinVar& rhs)
{
	return (lhs - rhs.getVar());
}

ROExpr operator * (const ROVar& lhs, const ROBinVar& rhs)
{
	return (lhs * rhs.getVar());
}


ROExpr operator + (const ROBinVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() + rhs);
}

ROExpr operator - (const ROBinVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() - rhs);
}

ROExpr operator * (const ROBinVar& lhs, const ROVar& rhs)
{
	return (lhs.getVar() * rhs);
}


ROExpr operator + (const ROBinVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() + rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() - rhs.getVar());
}

ROExpr operator * (const ROBinVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() * rhs.getVar());
}

ROExpr operator + (const ROIntVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() + rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() - rhs.getVar());
}

ROExpr operator * (const ROIntVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() * rhs.getVar());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to  + - / * with ROUnVarC

ROUnVarC operator + (RONum lhs, const ROUnVarC& rhs)
{	
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::plus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, RONum rhs)
{
	return (rhs + lhs);
}

ROUnVarC operator - (RONum lhs, const ROUnVarC& rhs)
{
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, RONum rhs)
{
	ROExpr expr;
	expr += rhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(lhs, expr);
}

ROUnVarC operator * (RONum lhs, const ROUnVarC& rhs)
{
	ROExpr expr = lhs * (*(rhs.getExpr().get()));

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(rhs.getConstSet());
	
	return uvC;
}

ROUnVarC operator * (const ROUnVarC& lhs, RONum rhs)
{
	return(rhs * lhs);
}

ROUnVarC operator / (const ROUnVarC& lhs, RONum rhs)
{
	ROExpr expr = (*(lhs.getExpr().get())) / rhs;

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(lhs.getConstSet());
	
	return uvC;
}

// -----------------------------------------------------------------------

ROUnVarC operator + (const ROUn& lhs, const ROUnVarC& rhs)
{
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::plus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, const ROUn& rhs)
{
	return (rhs + lhs);
}

ROUnVarC operator - (const ROUn& lhs, const ROUnVarC& rhs)
{
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr += rhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(lhs, expr);
}

ROUnVarC operator * (const ROUn& lhs, const ROUnVarC& rhs)
{
	ROExpr expr = lhs * (*(rhs.getExpr().get()));

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(rhs.getConstSet());
	
	return uvC;
}

ROUnVarC operator * (const ROUnVarC& lhs, const ROUn& rhs)
{
	return (rhs * lhs);
}


// -----------------------------------------------------------------------

ROUnVarC operator + (const ROVar& lhs, const ROUnVarC& rhs)
{
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::plus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, const ROVar& rhs)
{
	return (rhs + lhs);
}

ROUnVarC operator + (const ROIntVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() + rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, const ROIntVar& rhs)
{
    return (rhs.getVar() + lhs);
}

ROUnVarC operator + (const ROBinVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() + rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, const ROBinVar& rhs)
{
    return (rhs.getVar() + lhs);
}

ROUnVarC operator - (const ROVar& lhs, const ROUnVarC& rhs)
{
	ROExpr expr;
	expr += lhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(expr, rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr += rhs;
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(lhs, expr);
}

ROUnVarC operator - (const ROIntVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() -rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROIntVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROUnVarC operator - (const ROBinVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() -rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROBinVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROUnVarC operator * (const ROVar& lhs, const ROUnVarC& rhs)
{
	ROExpr expr = lhs * (*(rhs.getExpr().get()));

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(rhs.getConstSet());
	
	return uvC;
}

ROUnVarC operator * (const ROUnVarC& lhs, const ROVar& rhs)
{
	return (rhs * lhs);
}

ROUnVarC operator * (const ROIntVar& lhs, const ROUnVarC& rhs)
{
    return (rhs * lhs.getVar());
}

ROUnVarC operator * (const ROUnVarC& lhs, const ROIntVar& rhs)
{
    return (rhs.getVar() * lhs);
}

ROUnVarC operator * (const ROBinVar& lhs, const ROUnVarC& rhs)
{
    return (rhs * lhs.getVar());
}

ROUnVarC operator * (const ROUnVarC& lhs, const ROBinVar& rhs)
{
    return (rhs.getVar() * lhs);
}

// -----------------------------------------------------------------------

ROUnVarC operator + (const ROExpr& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCFunctor<std::plus<ROExpr>, ROExpr>(lhs, rhs);
}

ROUnVarC operator + (const ROUnVarC& lhs, const ROExpr& rhs)
{
	return ROUnVarCFunctor<std::plus<ROExpr>, ROExpr>(lhs, rhs);
}

ROUnVarC operator - (const ROExpr& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(lhs, rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROExpr& rhs)
{
	return ROUnVarCFunctor<std::minus<ROExpr>, ROExpr>(lhs, rhs);
}

// -----------------------------------------------------------------------

ROUnVarC operator + (const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCFunctor<std::plus<ROExpr> >(lhs, rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCFunctor<std::minus<ROExpr> >(lhs, rhs);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Binaray
// related to  + - / *

ROExpr operator + (RONum lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (const ROVar& lhs, RONum rhs)
{
	return (operator + (rhs, lhs));
}

ROExpr operator + (RONum lhs, const ROIntVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator + (const ROIntVar& lhs, RONum rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator + (RONum lhs, const ROBinVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator + (const ROBinVar& lhs, RONum rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator - (RONum lhs, const ROIntVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, RONum rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator - (RONum lhs, const ROBinVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, RONum rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator * (RONum lhs, const ROIntVar& rhs)
{
    return (lhs * rhs.getVar());
}

ROExpr operator * (const ROIntVar& lhs, RONum rhs)
{
    return (lhs.getVar() * rhs);
}

ROExpr operator * (RONum lhs, const ROBinVar& rhs)
{
    return (lhs * rhs.getVar());
}

ROExpr operator * (const ROBinVar& lhs, RONum rhs)
{
    return (lhs.getVar() * rhs);
}

ROExpr operator / (const ROIntVar& lhs, RONum rhs)
{
    return (lhs.getVar() / rhs);
}

ROExpr operator / (const ROBinVar& lhs, RONum rhs)
{
    return (lhs.getVar() / rhs);
}


ROExpr operator + (RONum lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (const ROUn& lhs, RONum rhs)
{
	return (operator + (rhs, lhs));
}

ROExpr operator - (RONum lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROVar& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (RONum lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROUn& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator * (RONum lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(rhs);
	expr.operator *=(lhs);
	return expr;
}

ROExpr operator * (const ROVar& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (RONum lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(rhs);
	expr.operator *=(lhs);
	return expr;
}

ROExpr operator * (const ROUn& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (RONum lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(rhs);
	expr.operator *=(lhs);
	return expr;
}

ROExpr operator * (const ROExpr& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator / (const ROVar& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator /=(rhs);
	return expr;
}

ROExpr operator / (const ROUn& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator /=(rhs);
	return expr;
}

ROExpr operator / (const ROExpr& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator /=(rhs);
	return expr;
}

ROExpr operator + (const ROVar& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROVar& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROIntVar& lhs, const ROIntVar& rhs)
{
    return (lhs.getVar() + rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, const ROIntVar& rhs)
{
    return (lhs.getVar() - rhs.getVar());
}

ROExpr operator + (const ROBinVar& lhs, const ROBinVar& rhs)
{
    return (lhs.getVar() + rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, const ROBinVar& rhs)
{
    return (lhs.getVar() - rhs.getVar());
}

ROExpr operator + (const ROUn& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROUn& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROExpr& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (RONum lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROExpr& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (RONum lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROExpr& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (const ROVar& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROExpr& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROVar& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROExpr& lhs, const ROIntVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator + (const ROIntVar& lhs, const ROExpr& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator - (const ROExpr& lhs, const ROIntVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, const ROExpr& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator + (const ROExpr& lhs, const ROBinVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator + (const ROBinVar& lhs, const ROExpr& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator - (const ROExpr& lhs, const ROBinVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, const ROExpr& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator + (const ROExpr& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (const ROUn& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROExpr& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROUn& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROVar& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROUn& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROVar& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator - (const ROUn& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator + (const ROIntVar& lhs, const ROUn& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator + (const ROUn& lhs, const ROIntVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, const ROUn& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator - (const ROUn& lhs, const ROIntVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator + (const ROBinVar& lhs, const ROUn& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator + (const ROUn& lhs, const ROBinVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, const ROUn& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator - (const ROUn& lhs, const ROBinVar& rhs)
{
    return (lhs - rhs.getVar());
}


ROExpr operator + (const ROExpr& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROExpr& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator * (const ROUn& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROVar& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROVar& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}


ROExpr operator * (const ROExpr& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROVar& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROUn& lhs, const ROIntVar& rhs)
{
	return (lhs * rhs.getVar());
}

ROExpr operator * (const ROIntVar& lhs, const ROUn& rhs)
{
	return (lhs.getVar() * rhs);
}

ROExpr operator * (const ROIntVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() * rhs.getVar());
}

ROExpr operator * (const ROExpr& lhs, const ROIntVar& rhs)
{
	return (lhs * rhs.getVar());
}

ROExpr operator * (const ROIntVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() * rhs);
}

ROExpr operator * (const ROUn& lhs, const ROBinVar& rhs)
{
	return (lhs * rhs.getVar());
}

ROExpr operator * (const ROBinVar& lhs, const ROUn& rhs)
{
	return (lhs.getVar() * rhs);
}

ROExpr operator * (const ROBinVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() * rhs.getVar());
}

ROExpr operator * (const ROExpr& lhs, const ROBinVar& rhs)
{
	return (lhs * rhs.getVar());
}

ROExpr operator * (const ROBinVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() * rhs);
}


ROExpr operator * (const ROExpr& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROUn& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROExpr& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs);
	return expr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Functional Operations related to "ROVarDR"
//
//     + - / * 

ROExpr operator + (RONum lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator+=(lhs);
	expr.operator+=(rhs.getExpr());
	return expr;
}

ROExpr operator + (const ROVarDR& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator+=(lhs.getExpr());
	expr.operator+=(rhs);
	return expr;
}

ROExpr operator - (RONum lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs.getExpr());
	return expr;
}

ROExpr operator - (const ROVarDR& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator * (RONum lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs.getExpr());
	return expr;
}

ROExpr operator * (const ROVarDR& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator / (const ROVarDR& lhs, RONum rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator /=(rhs);
	return expr;
}


ROExpr operator + (const ROUn& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator+=(lhs);
	expr.operator+=(rhs.getExpr());
	return expr;
}

ROExpr operator + (const ROVarDR& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator+=(lhs.getExpr());
	expr.operator+=(rhs);
	return expr;
}

ROExpr operator - (const ROUn& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs.getExpr());
	return expr;
}

ROExpr operator - (const ROVarDR& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator * (const ROUn& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs.getExpr());
	return expr;
}

ROExpr operator * (const ROVarDR& lhs, const ROUn& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator *=(rhs);
	return expr;
}


ROExpr operator + (const ROVar& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs.getExpr());
	return expr;
}

ROExpr operator + (const ROVarDR& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator + (const ROIntVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator + (const ROVarDR& lhs, const ROIntVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator + (const ROBinVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() + rhs);
}

ROExpr operator + (const ROVarDR& lhs, const ROBinVar& rhs)
{
    return (lhs + rhs.getVar());
}

ROExpr operator - (const ROIntVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator - (const ROVarDR& lhs, const ROIntVar& rhs)
{
    return (lhs - rhs.getVar());
}

ROExpr operator - (const ROBinVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() - rhs);
}

ROExpr operator - (const ROVarDR& lhs, const ROBinVar& rhs)
{
    return (lhs - rhs.getVar());
}


ROExpr operator - (const ROVar& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs.getExpr());
	return expr;
}

ROExpr operator - (const ROVarDR& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator -=(rhs);
	return expr;
}

ROExpr operator * (const ROVar& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator *=(rhs.getExpr());
	return expr;
}

ROExpr operator * (const ROVarDR& lhs, const ROVar& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator *=(rhs);
	return expr;
}

ROExpr operator * (const ROIntVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() * rhs);
}

ROExpr operator * (const ROVarDR& lhs, const ROIntVar& rhs)
{
    return (lhs * rhs.getVar());
}

ROExpr operator * (const ROBinVar& lhs, const ROVarDR& rhs)
{
    return (lhs.getVar() * rhs);
}

ROExpr operator * (const ROVarDR& lhs, const ROBinVar& rhs)
{
    return (lhs * rhs.getVar());
}


ROExpr operator + (const ROExpr& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator +=(rhs.getExpr());
	return expr;
}

ROExpr operator + (const ROVarDR& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator +=(rhs);
	return expr;
}

ROExpr operator - (const ROExpr& lhs, const ROVarDR& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs);
	expr.operator -=(rhs.getExpr());
	return expr;
}

ROExpr operator - (const ROVarDR& lhs, const ROExpr& rhs)
{
	ROExpr expr;
	expr.operator +=(lhs.getExpr());
	expr.operator -=(rhs);
	return expr;
}


ROUnVarC operator + (const ROUnVarC& lhs, const ROVarDR& rhs)
{
	return (lhs + rhs.getExpr());
}

ROUnVarC operator + (const ROVarDR& lhs, const ROUnVarC& rhs)
{
	return (lhs.getExpr() + rhs);
}

ROUnVarC operator - (const ROUnVarC& lhs, const ROVarDR& rhs)
{
	return (lhs - rhs.getExpr());
}

ROUnVarC operator - (const ROVarDR& lhs, const ROUnVarC& rhs)
{
	return (lhs.getExpr() - rhs);
}

ROExpr operator + (const ROVarDR& lhs, const ROVarDR& rhs)
{
	return (lhs.getExpr() + rhs.getExpr());
}

ROExpr operator - (const ROVarDR& lhs, const ROVarDR& rhs)
{
	return (lhs.getExpr() - rhs.getExpr());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to  == <= >=  constraints with respect to ROUnVarC, ROConstraintSet

// -------------------------------------------" <= " set constraint---------------------------------------------------

ROConstraintSet operator <= (RONum lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<RONum, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, RONum rhs)
{
	return ROUnVarCConst<RONum, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUn& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROUn, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROUn& rhs)
{
	return ROUnVarCConst<ROUn, ROConstTag>(lhs, rhs, EnumLeq);
}


ROConstraintSet operator <= (const ROVar& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROVar, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROIntVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROConstraintSet operator <= (const ROBinVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROVar& rhs)
{
	return ROUnVarCConst<ROVar, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROIntVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROBinVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROConstraintSet operator <= (const ROExpr& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROExpr, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROExpr& rhs)
{
	return ROUnVarCConst<ROExpr, ROConstTag>(lhs, rhs, EnumLeq);
}

ROConstraintSet operator <= (const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROConstTag>(lhs, rhs, EnumLeq);
}

// -------------------------------------------" == " set constraint---------------------------------------------------

ROConstraintSet operator == (RONum lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<RONum, ROConstTag>(lhs, rhs, EnumEq);
}

ROConstraintSet operator == (const ROUnVarC& lhs, RONum rhs)
{
	return ROUnVarCConst<RONum, ROConstTag>(lhs, rhs, EnumEq);
}


ROConstraintSet operator == (const ROUn& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROUn, ROConstTag>(lhs, rhs, EnumEq);
}

ROConstraintSet operator == (const ROUnVarC& lhs, const ROUn& rhs)
{
	return ROUnVarCConst<ROUn, ROConstTag>(lhs, rhs, EnumEq);
}


ROConstraintSet operator == (const ROVar& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROVar, ROConstTag>(lhs, rhs, EnumEq);
}

ROConstraintSet operator == (const ROUnVarC& lhs, const ROVar& rhs)
{
	return ROUnVarCConst<ROVar, ROConstTag>(lhs, rhs, EnumEq);
}

ROConstraintSet operator == (const ROIntVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() == rhs);
}

ROConstraintSet operator == (const ROUnVarC& lhs, const ROIntVar& rhs)
{
	return (lhs == rhs.getVar());
}

ROConstraintSet operator == (const ROBinVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() == rhs);
}

ROConstraintSet operator == (const ROUnVarC& lhs, const ROBinVar& rhs)
{
	return (lhs == rhs.getVar());
}


ROConstraintSet operator == (const ROExpr& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROExpr, ROConstTag>(lhs, rhs, EnumEq);
}

ROConstraintSet operator == (const ROUnVarC& lhs, const ROExpr& rhs)
{
	return ROUnVarCConst<ROExpr, ROConstTag>(lhs, rhs, EnumEq);
}


ROConstraintSet operator == (const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	return ROUnVarCConst<ROConstTag>(lhs, rhs, EnumEq);
}

// -------------------------------------------" >= " set constraint---------------------------------------------------

ROConstraintSet operator >= (RONum lhs, const ROUnVarC& rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, RONum rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROUn& lhs, const ROUnVarC& rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, const ROUn& rhs)
{
	return (rhs <= lhs);
}


ROConstraintSet operator >= (const ROVar& lhs, const ROUnVarC& rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, const ROVar& rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROIntVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, const ROIntVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROConstraintSet operator >= (const ROBinVar& lhs, const ROUnVarC& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, const ROBinVar& rhs)
{
	return (lhs >= rhs.getVar());
}


ROConstraintSet operator >= (const ROExpr& lhs, const ROUnVarC& rhs)
{
	return (rhs <= lhs);
}

ROConstraintSet operator >= (const ROUnVarC& lhs, const ROExpr& rhs)
{
	return (rhs <= lhs);
}


ROConstraintSet operator >= (const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	return (rhs <= lhs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to  == <= >=  constraints set

// -------------------------------------------" <= " set constraint---------------------------------------------------

ROBaseConstraint operator <= (RONum lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROUn& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROUn& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}


ROBaseConstraint operator <= (RONum lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROVar& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROVar& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (RONum lhs, const ROIntVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROBaseConstraint operator <= (const ROIntVar& lhs, RONum rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROIntVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() <= rhs.getVar());
}

ROBaseConstraint operator <= (RONum lhs, const ROBinVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROBaseConstraint operator <= (const ROBinVar& lhs, RONum rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROBinVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() <= rhs.getVar());
}

ROBaseConstraint operator <= (RONum lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROExpr& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}


ROBaseConstraint operator <= (const ROExpr& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}


ROBaseConstraint operator <= (const ROUn& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}


ROBaseConstraint operator <= (const ROExpr& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROVar& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator <= (const ROExpr& lhs, const ROIntVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROBaseConstraint operator <= (const ROIntVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROExpr& lhs, const ROBinVar& rhs)
{
	return (lhs <= rhs.getVar());
}
ROBaseConstraint operator <= (const ROBinVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROExpr& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}


// -------------------------------------------" >= " set constraint---------------------------------------------------

ROBaseConstraint operator >= (RONum lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROUn& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROUn& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (RONum lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROVar& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROVar& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (RONum lhs, const ROIntVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROBaseConstraint operator >= (const ROIntVar& lhs, RONum rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROIntVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() >= rhs.getVar());
}

ROBaseConstraint operator >= (RONum lhs, const ROBinVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROBaseConstraint operator >= (const ROBinVar& lhs, RONum rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROBinVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() >= rhs.getVar());
}

ROBaseConstraint operator >= (RONum lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROExpr& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}


ROBaseConstraint operator >= (const ROExpr& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROUn& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROExpr& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROVar& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}

ROBaseConstraint operator >= (const ROExpr& lhs, const ROIntVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROBaseConstraint operator >= (const ROIntVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROExpr& lhs, const ROBinVar& rhs)
{
	return (lhs >= rhs.getVar());
}
ROBaseConstraint operator >= (const ROBinVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROExpr& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(rhs-lhs)), EnumLeq);
}


// -------------------------------------------" == " set constraint---------------------------------------------------

ROBaseConstraint operator == (RONum lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROUn& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROUn& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator == (RONum lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROVar& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROVar& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumLeq);
}

ROBaseConstraint operator == (RONum lhs, const ROIntVar& rhs)
{
	return (lhs == rhs.getVar());
}

ROBaseConstraint operator == (const ROIntVar& lhs, RONum rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROIntVar& lhs, const ROIntVar& rhs)
{
	return (lhs.getVar() == rhs.getVar());
}

ROBaseConstraint operator == (RONum lhs, const ROBinVar& rhs)
{
	return (lhs == rhs.getVar());
}

ROBaseConstraint operator == (const ROBinVar& lhs, RONum rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROBinVar& lhs, const ROBinVar& rhs)
{
	return (lhs.getVar() == rhs.getVar());
}

ROBaseConstraint operator == (RONum lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROExpr& lhs, RONum rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}


ROBaseConstraint operator == (const ROExpr& lhs, const ROUn& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROUn& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROExpr& lhs, const ROVar& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROVar& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}

ROBaseConstraint operator == (const ROExpr& lhs, const ROIntVar& rhs)
{
	return (lhs == rhs.getVar());
}

ROBaseConstraint operator == (const ROIntVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROExpr& lhs, const ROBinVar& rhs)
{
	return (lhs == rhs.getVar());
}
ROBaseConstraint operator == (const ROBinVar& lhs, const ROExpr& rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROExpr& lhs, const ROExpr& rhs)
{
	return ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs)), EnumEq);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Constraints Operations Related to "ROVarDR"
// 
//   "<=" "<=" "=="

//----------------------------------------------------  " <= "  -------------------------------------------------------

ROBaseConstraint operator <= (RONum lhs, const ROVarDR& rhs)
{
	return (lhs <= rhs.getExpr());
}

ROBaseConstraint operator <= (const ROVarDR& lhs, RONum rhs)
{
	return (lhs.getExpr() <= rhs);
}


ROBaseConstraint operator <= (const ROUn& lhs, const ROVarDR& rhs)
{
	return (lhs <= rhs.getExpr());
}

ROBaseConstraint operator <= (const ROVarDR& lhs, const ROUn& rhs)
{
	return (lhs.getExpr() <= rhs);
}


ROBaseConstraint operator <= (const ROVar& lhs, const ROVarDR& rhs)
{
	return (lhs <= rhs.getExpr());
}

ROBaseConstraint operator <= (const ROVarDR& lhs, const ROVar& rhs)
{
	return (lhs.getExpr() <= rhs);
}

ROBaseConstraint operator <= (const ROIntVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROVarDR& lhs, const ROIntVar& rhs)
{
	return (lhs <= rhs.getVar());
}

ROBaseConstraint operator <= (const ROBinVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() <= rhs);
}

ROBaseConstraint operator <= (const ROVarDR& lhs, const ROBinVar& rhs)
{
	return (lhs <= rhs.getVar());
}


ROBaseConstraint operator <= (const ROExpr& lhs, const ROVarDR& rhs)
{
	return (lhs <= rhs.getExpr());
}

ROBaseConstraint operator <= (const ROVarDR& lhs, const ROExpr& rhs)
{
	return (lhs.getExpr() <= rhs);
}


ROConstraintSet operator <= (const ROUnVarC& lhs, const ROVarDR& rhs)
{
	return (lhs <= rhs.getExpr());
}

ROConstraintSet operator <= (const ROVarDR& lhs, const ROUnVarC& rhs)
{
	return (lhs.getExpr() <= rhs);
}


ROBaseConstraint operator <= (const ROVarDR& lhs, const ROVarDR& rhs)
{
	return (lhs.getExpr() <= rhs.getExpr());
}

//----------------------------------------------------  " == "  -------------------------------------------------------

ROBaseConstraint operator == (RONum lhs, const ROVarDR& rhs)
{
	return (lhs == rhs.getExpr());
}

ROBaseConstraint operator == (const ROVarDR& lhs, RONum rhs)
{
	return (lhs.getExpr() == rhs);
}


ROBaseConstraint operator == (const ROUn& lhs, const ROVarDR& rhs)
{
	return (lhs == rhs.getExpr());
}

ROBaseConstraint operator == (const ROVarDR& lhs, const ROUn& rhs)
{
	return (lhs.getExpr() == rhs);
}


ROBaseConstraint operator == (const ROVar& lhs, const ROVarDR& rhs)
{
	return (lhs == rhs.getExpr());
}

ROBaseConstraint operator == (const ROVarDR& lhs, const ROVar& rhs)
{
	return (lhs.getExpr() == rhs);
}

ROBaseConstraint operator == (const ROIntVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROVarDR& lhs, const ROIntVar& rhs)
{
	return (lhs == rhs.getVar());
}

ROBaseConstraint operator == (const ROBinVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() == rhs);
}

ROBaseConstraint operator == (const ROVarDR& lhs, const ROBinVar& rhs)
{
	return (lhs == rhs.getVar());
}


ROBaseConstraint operator == (const ROExpr& lhs, const ROVarDR& rhs)
{
	return (lhs == rhs.getExpr());
}

ROBaseConstraint operator == (const ROVarDR& lhs, const ROExpr& rhs)
{
	return (lhs.getExpr() == rhs);
}


ROConstraintSet operator == (const ROUnVarC& lhs, const ROVarDR& rhs)
{
	return (lhs == rhs.getExpr());
}

ROConstraintSet operator == (const ROVarDR& lhs, const ROUnVarC& rhs)
{
	return (lhs.getExpr() == rhs);
}


ROBaseConstraint operator == (const ROVarDR& lhs, const ROVarDR& rhs)
{
	return (lhs.getExpr() == rhs.getExpr());
}

//----------------------------------------------------  " <= "  -------------------------------------------------------

ROBaseConstraint operator >= (RONum lhs, const ROVarDR& rhs)
{
	return (lhs >= rhs.getExpr());
}

ROBaseConstraint operator >= (const ROVarDR& lhs, RONum rhs)
{
	return (lhs.getExpr() >= rhs);
}


ROBaseConstraint operator >= (const ROUn& lhs, const ROVarDR& rhs)
{
	return (lhs >= rhs.getExpr());
}

ROBaseConstraint operator >= (const ROVarDR& lhs, const ROUn& rhs)
{
	return (lhs.getExpr() >= rhs);
}


ROBaseConstraint operator >= (const ROVar& lhs, const ROVarDR& rhs)
{
	return (lhs >= rhs.getExpr());
}

ROBaseConstraint operator >= (const ROVarDR& lhs, const ROVar& rhs)
{
	return (lhs.getExpr() >= rhs);
}

ROBaseConstraint operator >= (const ROIntVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROVarDR& lhs, const ROIntVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROBaseConstraint operator >= (const ROBinVar& lhs, const ROVarDR& rhs)
{
	return (lhs.getVar() >= rhs);
}

ROBaseConstraint operator >= (const ROVarDR& lhs, const ROBinVar& rhs)
{
	return (lhs >= rhs.getVar());
}

ROBaseConstraint operator >= (const ROExpr& lhs, const ROVarDR& rhs)
{
	return (lhs >= rhs.getExpr());
}

ROBaseConstraint operator >= (const ROVarDR& lhs, const ROExpr& rhs)
{
	return (lhs.getExpr() >= rhs);
}


ROConstraintSet operator >= (const ROUnVarC& lhs, const ROVarDR& rhs)
{
	return (lhs >= rhs.getExpr());
}

ROConstraintSet operator >= (const ROVarDR& lhs, const ROUnVarC& rhs)
{
	return (lhs.getExpr() >= rhs);
}


ROBaseConstraint operator >= (const ROVarDR& lhs, const ROVarDR& rhs)
{
	return (lhs.getExpr() >= rhs.getExpr());
}

// ----------------------------------------  Unary operators :   + - / *  ---------------------------------------------
ROExpr operator - (const ROVar& p_var)
{
	return (-1)*p_var;
}

ROExpr operator - (const ROIntVar& p_var)
{
    return (-1)*p_var.getVar();
}

ROExpr operator - (const ROBinVar& p_var)
{
    return (-1)*p_var.getVar();
}


ROExpr operator - (const ROUn& p_un)
{
	return (-1)*p_un;
}

ROExpr operator - (const ROExpr& p_expr)
{
	return (-1)*p_expr;
}

ROUnVarC operator - (const ROUnVarC& p_unvarC)
{
	return (-1)*p_unvarC;
}

ROExpr operator - (const ROVarDR& p_varDR)
{
	return (-1)*p_varDR;
}

// -------------------------------------------------      END      ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
