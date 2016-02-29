//
//  ROExpr.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 29/8/12.
//
//

#include "ROExpr.h"
#include "ROVar.h"
#include "ROVarDR.h"
#include "ROUn.h"
#include "ROExprImpl.h"
#include "ROIntVar.h"
#include "ROBinVar.h"

ROExpr::ROExpr()
{
    m_exprImpl = boost::shared_ptr<ROExprImpl> (new ROExprImpl());
}

ROExpr::ROExpr(const ROVar& p_var)
{
	ROExpr expr;
	expr += p_var;
	
	m_exprImpl = expr.getImpl();
}

ROExpr::ROExpr(const ROIntVar& p_var)
{
	ROExpr expr;
	expr += p_var.getVar();
	
	m_exprImpl = expr.getImpl();
}

ROExpr::ROExpr(const ROBinVar& p_var)
{
	ROExpr expr;
	expr += p_var.getVar();
	
	m_exprImpl = expr.getImpl();
}

ROExpr::ROExpr(const ROUn& p_un)
{
	ROExpr expr;
	expr += p_un;
	
	m_exprImpl = expr.getImpl();
}

ROExpr::ROExpr(RONum val)
{
	m_exprImpl = boost::shared_ptr<ROExprImpl> (new ROExprImpl());
	*(m_exprImpl.get()) += val;
}

ROExpr::ROExpr(const ROExpr& p_expr)
{
	m_exprImpl = p_expr.getImpl();
}

ROExpr& ROExpr::operator = (RONum p_num)
{
	*(m_exprImpl.get()) += p_num;
	return *this;
}

ROExpr& ROExpr::operator = (const ROVar& p_var)
{
	*(m_exprImpl.get()) += p_var;
	return *this;
}

ROExpr& ROExpr::operator = (const ROUn& p_un)
{
	*(m_exprImpl.get()) += p_un;
	return *this;
}

ROExpr& ROExpr::operator = (const ROExpr& p_expr)
{
	if(this == &p_expr)
	{
		return *this;
	}
	m_exprImpl = p_expr.getImpl();
	return *this;
}

boost::shared_ptr<ROExprImpl> ROExpr::getImpl() const
{
    return m_exprImpl;
}

ROExpr& ROExpr::operator += (RONum p_val)
{
    *m_exprImpl.get() += p_val;
    return *this;
    
}
ROExpr& ROExpr::operator -= (RONum p_val)
{
    *m_exprImpl.get() -= p_val;
    return *this;
}

ROExpr& ROExpr::operator *= (RONum p_val)
{
    *m_exprImpl.get() *= p_val;
    return *this;
}

ROExpr& ROExpr::operator /= (RONum p_val)
{
    *m_exprImpl.get() /= p_val;
    return *this;
}

ROExpr& ROExpr::operator += (const ROVar& p_var)
{
    *m_exprImpl.get() += p_var;
    return *this;
}


ROExpr& ROExpr::operator -= (const ROVar& p_var)
{
    *m_exprImpl.get() -= p_var;
    return *this;
}


ROExpr& ROExpr::operator += (const ROUn& p_un)
{
    *m_exprImpl.get() += p_un;
    return *this;
}


ROExpr& ROExpr::operator -= (const ROUn& p_un)
{
    *m_exprImpl.get() -= p_un;
    return *this;
}

ROExpr& ROExpr::operator += (const ROExpr& p_expr)
{
	*m_exprImpl.get() += *(p_expr.getImpl().get());
    return *this;
}

ROExpr& ROExpr::operator += (const ROVarDR& p_varDR)
{
	return this->operator+=(p_varDR.getExpr());
}

ROExpr& ROExpr::operator -= (const ROExpr& p_expr)
{
    *m_exprImpl.get() -= *(p_expr.getImpl().get());
    return *this;
}

ROExpr& ROExpr::operator -= (const ROVarDR& p_varDR)
{
	return this->operator-=(p_varDR.getExpr());
}

ROExpr& ROExpr::operator *= (const ROVar& p_var)
{
	*m_exprImpl.get() *= p_var;
    return *this;
}

ROExpr& ROExpr::operator *=(const ROUn& p_un)
{
	*m_exprImpl.get() *= p_un;
    return *this;
}

ROExpr& ROExpr::operator *=(const ROExpr& p_expr)
{
	*m_exprImpl.get() *= *(p_expr.getImpl().get());
    return *this;
}

ROExpr& ROExpr::expect(const ROUn& p_un)
{
	m_exprImpl->expect(p_un);
	return *this;
}

ROExpr& ROExpr::expect(const ROExpr& p_expr)
{
	m_exprImpl->expect(*(p_expr.getImpl().get()));
	return *this;
}


ROExpr::~ROExpr()
{
    
}
