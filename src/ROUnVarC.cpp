//
//  Created by Meilin Zhang on 04/10/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include "ROUnVarC.h"
#include "ROExpr.h"
#include "ROConstraintSet.h"


ROUnVarC::ROUnVarC()
{
	m_expr = boost::shared_ptr<ROExpr>(new ROExpr());
	m_constSet = boost::shared_ptr<ROConstraintSet>(new ROConstraintSet());
}


ROUnVarC::ROUnVarC(const ROUnVarC& p_unC):
	m_expr(p_unC.getExpr()),
	m_constSet(p_unC.getConstSet())
{

}


ROUnVarC& ROUnVarC::operator = (const ROUnVarC& p_unC)
{
	if(this == &p_unC)
	{
		return *this;
	}
	m_expr = p_unC.getExpr();
	m_constSet = p_unC.getConstSet();
	return *this;
}


// Newly Added
ROUnVarC& ROUnVarC::operator = (const ROExpr& p_expr)
{
	m_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));
	m_constSet = boost::shared_ptr<ROConstraintSet>(new ROConstraintSet());

	return *this;
}

ROUnVarC& ROUnVarC::operator += (RONum p_val)
{
	*m_expr.get() += p_val;
	return *this;
}

ROUnVarC& ROUnVarC::operator -= (RONum p_val)
{
	*m_expr.get() -= p_val;
	return *this;
}

ROUnVarC& ROUnVarC::operator *= (RONum p_val)
{
	*m_expr.get() *= p_val;
	return *this;
}

ROUnVarC& ROUnVarC::operator /= (RONum p_val)
{
	*m_expr.get() /= p_val;
	return *this;
}

ROUnVarC& ROUnVarC::operator += (const ROVar& p_var)
{
	*m_expr.get() += p_var;
	return *this;
}

ROUnVarC& ROUnVarC::operator -= (const ROVar& p_var)
{
	*m_expr.get() -= p_var;
	return *this;
}


ROUnVarC& ROUnVarC::operator += (const ROUn& p_un)
{
	*m_expr.get() += p_un;
	return *this;
}

ROUnVarC& ROUnVarC::operator -= (const ROUn& p_un)
{
	*m_expr.get() -= p_un;
	return *this;
}

ROUnVarC& ROUnVarC::operator += (const ROExpr& p_expr)
{
	*m_expr.get() += p_expr;
	return *this;
}

ROUnVarC& ROUnVarC::operator += (const ROUnVarC& p_varC)
{
	*m_expr.get() += *(p_varC.getExpr().get());
	m_constSet->add(*(p_varC.getConstSet().get()));
	return *this;
}

ROUnVarC& ROUnVarC::operator -= (const ROExpr& p_expr)
{
	*m_expr.get() -= p_expr;
	return *this;
}

ROUnVarC& ROUnVarC::operator -= (const ROUnVarC& p_unC)
{
	*m_expr.get() -= *(p_unC.getExpr().get());
	m_constSet->add(*(p_unC.getConstSet().get()));
	return *this;
}

ROUnVarC& ROUnVarC::operator *= (const ROVar& p_var)
{
	*m_expr.get() *= p_var;
	return *this;
}

ROUnVarC& ROUnVarC::operator *= (const ROUn& p_un)
{
	*m_expr.get() *= p_un;
	return *this;
}

ROUnVarC& ROUnVarC::operator *= (const ROExpr& p_expr)
{
	*m_expr.get() *= p_expr;
	return *this;
}

ROUnVarC& ROUnVarC::expect(const ROUn& p_un)
{
	m_expr->expect(p_un);
	return *this;
}

ROUnVarC& ROUnVarC::expect(const ROExpr& p_expr)
{
	m_expr->expect(p_expr);
	return *this;
}

void ROUnVarC::setExpr(boost::shared_ptr<ROExpr> p_expr)	
{
	m_expr = p_expr;
}


void ROUnVarC::setConstSet(boost::shared_ptr<ROConstraintSet> p_constSet)
{
	m_constSet = p_constSet;
}


boost::shared_ptr<ROExpr> ROUnVarC::getExpr() const
{
	return m_expr;
}


boost::shared_ptr<ROConstraintSet> ROUnVarC::getConstSet() const
{
	return m_constSet;
}