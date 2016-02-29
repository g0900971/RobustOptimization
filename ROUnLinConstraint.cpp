//
//  ROUnLinConstraint.cpp
//  RobustOptimizationSolver
//
//	Created by Meilin Zhang on 04/10/12
//
//

#include "ROUnLinConstraint.h"
#include "ROBaseConstraint.h"
#include "ROExpr.h"

ROUnLinConstraint::ROUnLinConstraint(const ROUnLinConstraint& constraint):
	m_expr(constraint.getExpr()),
	m_tag(constraint.getTag())
{
}

ROUnLinConstraint::ROUnLinConstraint(const ROBaseConstraint& constraint):
	m_expr(constraint.getExpr()),
	m_tag(constraint.getTag())
{

}


ROUnLinConstraint::ROUnLinConstraint(const boost::shared_ptr<ROExpr> p_expr, const ROConstTag p_tag):
	m_expr(p_expr),
	m_tag(p_tag)
{

}

ROUnLinConstraint::ROUnLinConstraint(const ROConstTag p_tag):
	m_tag(p_tag)
{

}

ROUnLinConstraint& ROUnLinConstraint::operator = (const ROUnLinConstraint& p_const)
{
	if(this == &p_const)
	{
		return *this;
	}
	m_expr = p_const.getExpr();
	m_tag = p_const.getTag();
	return *this;
}

ROUnLinConstraint& ROUnLinConstraint::operator = (const ROBaseConstraint& p_const)
{
	m_expr = p_const.getExpr();
	m_tag = p_const.getTag();
	return *this;
}


boost::shared_ptr<ROExpr> ROUnLinConstraint::getExpr() const
{
	return m_expr;
}

ROConstTag ROUnLinConstraint::getTag() const
{
	return m_tag;
}