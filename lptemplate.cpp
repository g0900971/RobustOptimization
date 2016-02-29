//
//  lptemplate.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 19/9/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_lptemplate_cpp
#define RobustOptimizationSolver_lptemplate_cpp

#include "lptemplate.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to expr  + - / *

template<>
Expr<CPLEX> operator + (LPNum p_val, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) + p_val)));
	return expr;
}


template<>
Expr<CPLEX> operator + (const Var<CPLEX>& p_var, LPNum p_val)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) + p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator - (LPNum p_val, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(p_val - *(p_var.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Var<CPLEX>& p_var, LPNum p_val)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) - p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator * (LPNum p_val, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) * p_val)));
	return expr;
}

template<>
Expr<CPLEX> operator * (const Var<CPLEX>& p_var, LPNum p_val)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) * p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator * (LPNum p_val, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) * p_val)));
	return expr;
}

template<>
Expr<CPLEX> operator * (const Expr<CPLEX>& p_expr, LPNum p_val)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) * p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator / (const Var<CPLEX>& p_var, LPNum p_val)
{
	Expr<CPLEX> expr(p_var.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) / p_val)));
	return expr;
}

template<>
Expr<CPLEX> operator / (const Expr<CPLEX>& p_expr, LPNum p_val)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) / p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator + (const Var<CPLEX>& p_varL, const Var<CPLEX>& p_varR)
{
	Expr<CPLEX> expr(p_varL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_varL.getVar().get()) + *(p_varR.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Var<CPLEX>& p_varL, const Var<CPLEX>& p_varR)
{
	Expr<CPLEX> expr(p_varL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_varL.getVar().get()) - *(p_varR.getVar().get()))));
	return expr;
}
//

template<>
Expr<CPLEX> operator + (LPNum p_val, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) + p_val)));
	return expr;
}

template<>
Expr<CPLEX> operator + (const Expr<CPLEX>& p_expr, LPNum p_val)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) + p_val)));
	return expr;
}

template<>
Expr<CPLEX> operator - (LPNum p_val, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(p_val - *(p_expr.getExpr().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Expr<CPLEX>& p_expr, LPNum p_val)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) - p_val)));
	return expr;
}
//

template<>
Expr<CPLEX> operator + (const Var<CPLEX>& p_var, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) + *(p_var.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator + (const Expr<CPLEX>& p_expr, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) + *(p_var.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Var<CPLEX>& p_var, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_var.getVar().get()) - *(p_expr.getExpr().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Expr<CPLEX>& p_expr, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) - *(p_var.getVar().get()))));
	return expr;
}
//

template<>
Expr<CPLEX> operator + (const Expr<CPLEX>& p_exprL, const Expr<CPLEX>& p_exprR)
{
	Expr<CPLEX> expr(p_exprL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_exprL.getExpr().get()) + *(p_exprR.getExpr().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator - (const Expr<CPLEX>& p_exprL, const Expr<CPLEX>& p_exprR)
{
	Expr<CPLEX> expr(p_exprL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_exprL.getExpr().get()) - *(p_exprR.getExpr().get()))));
	return expr;
}
//

template<>
Expr<CPLEX> operator * (const Var<CPLEX>& p_varL, const Var<CPLEX>& p_varR)
{
	Expr<CPLEX> expr(p_varL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_varL.getVar().get()) * *(p_varR.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator * (const Expr<CPLEX>& p_expr, const Var<CPLEX>& p_var)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) * *(p_var.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator * (const Var<CPLEX>& p_var, const Expr<CPLEX>& p_expr)
{
	Expr<CPLEX> expr(p_expr.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_expr.getExpr().get()) * *(p_var.getVar().get()))));
	return expr;
}

template<>
Expr<CPLEX> operator * (const Expr<CPLEX>& p_exprL, const Expr<CPLEX>& p_exprR)
{
	Expr<CPLEX> expr(p_exprL.getEnv());
	expr.setExpr(boost::shared_ptr<IloExpr>(new IloExpr(*(p_exprL.getExpr().get()) * *(p_exprR.getExpr().get()))));
	return expr;
}
//


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Objective Function
template<>
Objective<CPLEX> Minimize(const Expr<CPLEX>& p_expr)
{
	IloEnv& env = p_expr.getEnv();
	Objective<CPLEX> obj(env);
	obj.setObjective(boost::shared_ptr<IloObjective>(new IloObjective(IloMinimize(env, *(p_expr.getExpr().get())))));

	return obj;
}

template<>
Objective<CPLEX> Maximize(const Expr<CPLEX>& p_expr)
{
	IloEnv& env = p_expr.getEnv();
	Objective<CPLEX> obj(env);
	obj.setObjective(boost::shared_ptr<IloObjective>(new IloObjective(IloMaximize(env, *(p_expr.getExpr().get())))));

	return obj;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Constraints Operations
// 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// "<=" "<=" "=="

template<>
Constraint<CPLEX> operator <= (LPNum lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(lhs <= *(rhs.getVar().get()))));
//	constraint.getConstraint()= boost::shared_ptr<IloConstraint>(new IloConstraint(lhs <= *(rhs.getVar().get())));

	return constraint;
}

template<>
Constraint<CPLEX> operator <= (const Var<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;

	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) <= rhs)));

	return constraint;
}


template<>
Constraint<CPLEX> operator <= (LPNum lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint((lhs <= *(rhs.getExpr().get())))));

	return constraint;
}


template<>
Constraint<CPLEX> operator <= (const Expr<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) <= rhs)));

	return constraint;
}


template<>
Constraint<CPLEX> operator <= (const Expr<CPLEX>& lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) <= *(rhs.getVar().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator <= (const Var<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) <= *(rhs.getExpr().get()))));

	return constraint;
}



template<>
Constraint<CPLEX> operator <= (const Expr<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) <= *(rhs.getExpr().get()))));

	return constraint;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// " >= " 
template<>
Constraint<CPLEX> operator >= (LPNum lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(lhs >= *(rhs.getVar().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator >= (const Var<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) >= rhs)));

	return constraint;
}



template<>
Constraint<CPLEX> operator >= (LPNum lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(lhs >= *(rhs.getExpr().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator >= (const Expr<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) >= rhs)));

	return constraint;
}



template<>
Constraint<CPLEX> operator >= (const Expr<CPLEX>& lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) >= *(rhs.getVar().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator >= (const Var<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) >= *(rhs.getExpr().get()))));

	return constraint;
}



template<>
Constraint<CPLEX> operator >= (const Expr<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) >= *(rhs.getExpr().get()))));

	return constraint;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// " == "

template<>
Constraint<CPLEX> operator == (LPNum lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(lhs == *(rhs.getVar().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator == (const Var<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) == rhs)));

	return constraint;
}


template<>
Constraint<CPLEX> operator == (LPNum lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(lhs == *(rhs.getExpr().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator == (const Expr<CPLEX>& lhs, LPNum rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) == rhs)));

	return constraint;
}


template<>
Constraint<CPLEX> operator == (const Expr<CPLEX>& lhs, const Var<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) == *(rhs.getVar().get()))));

	return constraint;
}


template<>
Constraint<CPLEX> operator == (const Var<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getVar().get()) == *(rhs.getExpr().get()))));

	return constraint;
}



template<>
Constraint<CPLEX> operator == (const Expr<CPLEX>& lhs, const Expr<CPLEX>& rhs)
{
	Constraint<CPLEX> constraint;
	constraint.setConstraint(boost::shared_ptr<IloConstraint>(new IloConstraint(*(lhs.getExpr().get()) == *(rhs.getExpr().get()))));

	return constraint;
}

template<>
CPLEX::VarType LPUtils<CPLEX, CPLEX_VAR_TYPE>::ROVarType2LPType(const ROVarType type)
{

	switch(type)
	{
		case EnumROVar:
			return CPLEX_VAR_TYPE::Float;
			
		case EnumROInt:
			return CPLEX_VAR_TYPE::Int;

		case EnumROBool:
			return CPLEX_VAR_TYPE::Bool;

		default:
			return CPLEX_VAR_TYPE::Float;
	}
}

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
