//
//  ROBaseConstraint.cpp
//  RobustOptimizationSolver
//
//	Created by Meilin Zhang on 11/9/12
//
//

#include "ROBaseConstraint.h"
#include "ROUnLinConstraint.h"
#include "ROExpr.h"

ROBaseConstraint::ROBaseConstraint(const ROBaseConstraint& p_const):
	m_expr(p_const.getExpr()),
	m_tag(p_const.getTag())
{
}

ROBaseConstraint::ROBaseConstraint(const ROUnLinConstraint& p_const):
	m_expr(p_const.getExpr()),
	m_tag(p_const.getTag())
{
}


ROBaseConstraint::ROBaseConstraint(const boost::shared_ptr<ROExpr> p_expr, const ROConstTag p_tag):
	m_expr(p_expr),
	m_tag(p_tag)
{

}

ROBaseConstraint::ROBaseConstraint(const ROConstTag p_tag):
	m_tag(p_tag)
{

}

ROBaseConstraint& ROBaseConstraint::operator = (const ROBaseConstraint& p_const)
{
	if(this == &p_const)
	{
		return *this;
	}
	m_expr = p_const.getExpr();
	m_tag = p_const.getTag();
	return *this;
}

ROBaseConstraint& ROBaseConstraint::operator = (const ROUnLinConstraint& p_const)
{
	m_expr = p_const.getExpr();
	m_tag = p_const.getTag();
	return *this;
}


boost::shared_ptr<ROExpr> ROBaseConstraint::getExpr() const
{
	return m_expr;
}

ROConstTag ROBaseConstraint::getTag() const
{
	return m_tag;
}