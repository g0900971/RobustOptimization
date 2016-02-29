//
//  ROUnSOCConstraint.cpp
//  RobustOptimizationSolver
//
//	Created by Meilin Zhang on 11/9/12
//
//

#include "ROUnSOCConstraint.h"
#include "ROExpr.h"
#include "ROUn.h"

ROUnSOCConstraint::ROUnSOCConstraint()
{

}

ROUnSOCConstraint::ROUnSOCConstraint(const ROUnSOCConstraint& p_normConst):
	m_expr(p_normConst.getExpr()),
	m_exprArray(p_normConst.getExprArray())
{

}

ROUnSOCConstraint::ROUnSOCConstraint(const boost::shared_ptr<ROExpr> p_exprL, boost::shared_ptr<ROExpr> p_exprR):
	m_expr(p_exprR)
{
	m_exprArray = boost::shared_ptr<ROExprArray>(new ROExprArray());
	m_exprArray->add(*(p_exprL.get()));
}


ROUnSOCConstraint::ROUnSOCConstraint(const boost::shared_ptr<ROExpr> p_expr, const boost::shared_ptr<ROExprArray> p_exprArray):
	m_expr(p_expr),
	m_exprArray(p_exprArray)
{

}

ROUnSOCConstraint::ROUnSOCConstraint(boost::shared_ptr<ROExprArray> p_exprArray, const boost::shared_ptr<ROExpr> p_expr)
	 :m_expr(p_expr),
	 m_exprArray(p_exprArray)
{

}


ROUnSOCConstraint::ROUnSOCConstraint(ROExprArray& p_exprArray, const ROExpr& p_expr)
{
	m_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));
	m_exprArray = boost::shared_ptr<ROExprArray>(new ROExprArray(p_exprArray));
}

ROUnSOCConstraint::ROUnSOCConstraint(ROUnArray& p_unArray, const ROExpr& p_expr)
{
	ROExprArray exprArray;
	size_t iSize = p_unArray.getSize();
	for(int i = 0; i < iSize; i++)
	{
		exprArray.add(p_unArray[i]);
	}

	m_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));
	m_exprArray = boost::shared_ptr<ROExprArray>(new ROExprArray(exprArray));
}


ROUnSOCConstraint::ROUnSOCConstraint(const ROExpr& p_expr, ROExprArray& p_exprArray)
{
	m_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));
	m_exprArray = boost::shared_ptr<ROExprArray>(new ROExprArray(p_exprArray));
}

ROUnSOCConstraint::ROUnSOCConstraint(const ROExpr& p_exprL, const ROExpr& p_exprR)
{
	m_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_exprR));

	m_exprArray = boost::shared_ptr<ROExprArray>(new ROExprArray());
	m_exprArray->add(p_exprL);
}

ROUnSOCConstraint& ROUnSOCConstraint::operator = (const ROUnSOCConstraint& p_normConst)
{
	if(this == &p_normConst)
	{
		return *this;
	}
	m_expr = p_normConst.getExpr();
	m_exprArray = p_normConst.getExprArray();
	return *this;
}

boost::shared_ptr<ROExpr> ROUnSOCConstraint::getExpr() const
{
	return m_expr;
}

boost::shared_ptr<ROExprArray> ROUnSOCConstraint::getExprArray() const
{
	return m_exprArray;
}