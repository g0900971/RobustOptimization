//
//  ROVarDR.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 7/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include "ROVarDR.h"
#include "ROVarDRImpl.h"


ROVarDR::ROVarDR()
{
	m_sp_DRImp = boost::shared_ptr<ROVarDRImpl>(new ROVarDRImpl());
}

boost::shared_ptr<ROVarDRImpl> ROVarDR::getImpl() const
{
	return m_sp_DRImp;
}

ROExpr ROVarDR::getExpr() const
{
	return m_sp_DRImp->getExpr();
}

ROVar& ROVarDR::getVar(ROExpr& p_expr) const
{
	return m_sp_DRImp->getVar(p_expr);
}

ROVar& ROVarDR::getVar(ROUn& p_un) const
{
	return m_sp_DRImp->getVar(p_un);
}

ROVar& ROVarDR::getVar() const
{
	return m_sp_DRImp->getVar();
}


void ROVarDR::addDR(ROExpr& p_expr)
{
	m_sp_DRImp->add(p_expr);
}

void ROVarDR::addDR(ROUn& p_un)
{
	m_sp_DRImp->add(p_un);
}


// Date: 2013-05-21 Version 0.2
// Rename as ROVarDR::clone()
// Modified by Meilin Zhang
void ROVarDR::clone(ROVarDR& p_varDR)
{
	m_sp_DRImp->add(p_varDR.getImpl());
}