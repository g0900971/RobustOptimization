//
//  ROObjective.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 13/9/12.
//  Modified by Meilin Zhang on 24/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include "ROVar.h"
#include "ROExpr.h"
#include "ROUnVarC.h"
#include "ROObjective.h"
#include "ROExprImpl.h"
#include "ROConstraintSet.h"
#include "roexprfunctions.h"

ROObjective::ROObjective(const boost::shared_ptr<ROExpr> p_expr, const ROObjectiveTag p_tag):
	m_expr(p_expr),
	m_obj_tag(p_tag)
{

}

// TBA
ROObjective::ROObjective(const boost::shared_ptr<ROExpr> p_expr, const ROConstraintSet& p_constSet, const ROObjectiveTag p_tag):
	m_obj_tag(p_tag)
{
	m_constSet = boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(p_constSet));

	if(p_expr->getImpl()->getType() == EnumVar || p_expr->getImpl()->getType() == EnumQVar)
	{
		m_expr = p_expr;
	}
	else
	{
		ROVar var_X;
		ROExpr temExpr;
		temExpr += var_X;
		m_expr = boost::shared_ptr<ROExpr>(new ROExpr(temExpr));

		if(p_tag == EnumMin)
		{
			m_constSet->add(var_X >= *(p_expr.get()));
		}
		else
		{
			m_constSet->add(var_X <= *(p_expr.get()));
		}
	}
}

ROObjective::ROObjective(const ROObjective& p_obj):
	m_expr(p_obj.getExpr()),
	m_constSet(p_obj.getConstSet()),
	m_obj_tag(p_obj.getTag())
{
	
}

// --------- Incorporate the ROUnVarC -------------
ROObjective::ROObjective(const ROUnVarC& p_unVarC, const ROConstraintSet& p_constSet, const ROObjectiveTag p_tag):
	m_obj_tag(p_tag)
{
	m_constSet = boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(p_constSet));
	m_constSet->add(*(p_unVarC.getConstSet().get()));
	ROExpr expr = *(p_unVarC.getExpr().get());

	if(expr.getImpl()->getType() == EnumVar || expr.getImpl()->getType() == EnumQVar)
	{
		m_expr = p_unVarC.getExpr();
	}
	else
	{
		ROVar var_X;
		ROExpr temExpr;
		temExpr += var_X;
		m_expr = boost::shared_ptr<ROExpr>(new ROExpr(temExpr));

		if(p_tag == EnumMin)
		{
			m_constSet->add(var_X >= expr);
		}
		else
		{
			m_constSet->add(var_X <= expr);
		}
	}
}

ROObjective::ROObjective(const ROUnVarC& p_unVarC, const ROObjectiveTag p_tag):
	m_expr(p_unVarC.getExpr()),
	m_constSet(p_unVarC.getConstSet()),
	m_obj_tag(p_tag)
{

}

// ------------------------------------------------

ROObjective& ROObjective::operator = (const ROObjective& p_obj)
{
	if(this == &p_obj)
	{
		return *this;
	}
	m_expr = p_obj.getExpr();
	return *this;
}

boost::shared_ptr<ROExpr> ROObjective::getExpr() const
{
	return m_expr;
}

boost::shared_ptr<ROConstraintSet> ROObjective::getConstSet() const
{
	return m_constSet;
}

ROObjectiveTag ROObjective::getTag() const
{
	return m_obj_tag;
}