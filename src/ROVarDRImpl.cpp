//
//  ROVarDRImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 24/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include "ROVarDRImpl.h"
#include "ROVar.h"
#include "roexprfunctions.h"

ROVarDRImpl::ROVarDRImpl()
{
	m_sp_var_Z = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "DR_"));
}

ROExpr ROVarDRImpl::getExpr()
{
	ROExpr expr;

	expr += *(m_sp_var_Z.get());

	ReVarDRIter iter;
	for(iter = m_varDRMapReverse.begin(); iter != m_varDRMapReverse.end(); iter++)
	{
		expr += (*(iter->first.get())) * (*(iter->second.get()));
	}

	ReVarDRUnIter un_iter;
	for(un_iter = m_varDRUnMapReverse.begin(); un_iter != m_varDRUnMapReverse.end(); un_iter++)
	{
		expr += (*(un_iter->first.get())) * (*(un_iter->second.get()));
	}

	return expr;
}

ROVar& ROVarDRImpl::getVar(ROExpr& p_expr) const
{
	boost::shared_ptr<ROExpr> sp_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));

	return (*(m_varDRMapReverse.find(sp_expr)->second.get()));
}

ROVar& ROVarDRImpl::getVar(ROUn& p_un) const
{
	boost::shared_ptr<ROUn> sp_un = boost::shared_ptr<ROUn>(new ROUn(p_un));

	return (*(m_varDRUnMapReverse.find(sp_un)->second.get()));
}

ROVar& ROVarDRImpl::getVar() const
{
	return (*(m_sp_var_Z.get()));
}

ReVarDRMap& ROVarDRImpl::getReVarDRMap()
{
	return m_varDRMapReverse;
}

ReVarDRUnMap& ROVarDRImpl::getReVarDRUnMap()
{
	return m_varDRUnMapReverse;
}

void ROVarDRImpl::add(ROExpr& p_expr)
{
	boost::shared_ptr<ROVar> sp_var_X = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "DR_"));
	boost::shared_ptr<ROExpr> sp_expr = boost::shared_ptr<ROExpr>(new ROExpr(p_expr));

	//m_varDRMap.insert(std::make_pair(sp_var_X, sp_expr));
	if(m_varDRMapReverse.find(sp_expr) == m_varDRMapReverse.end())
	{
		m_varDRMapReverse.insert(std::make_pair(sp_expr, sp_var_X));
	}
}

void ROVarDRImpl::add(ROUn& p_un)
{
	boost::shared_ptr<ROVar> sp_var_X = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "DR_"));
	boost::shared_ptr<ROUn> sp_un = boost::shared_ptr<ROUn>(new ROUn(p_un));

	//m_varDRUnMap.insert(std::make_pair(sp_var_X, sp_un));
	if(m_varDRUnMapReverse.find(sp_un) == m_varDRUnMapReverse.end())
	{
		m_varDRUnMapReverse.insert(std::make_pair(sp_un, sp_var_X));
	}
}

void ROVarDRImpl::add(boost::shared_ptr<ROVarDRImpl> sp_DRImpl)
{
	ReVarDRMap& exprMap = sp_DRImpl->getReVarDRMap();
	ReVarDRUnMap& unMap = sp_DRImpl->getReVarDRUnMap();

	ReVarDRIter iterE;
	for(iterE = exprMap.begin(); iterE != exprMap.end(); iterE++)
	{
		this->add(*(iterE->first.get()));
	}

	ReVarDRUnIter iterUn;
	for(iterUn = unMap.begin(); iterUn != unMap.end(); iterUn++)
	{
		this->add(*(iterUn->first.get()));
	}
}