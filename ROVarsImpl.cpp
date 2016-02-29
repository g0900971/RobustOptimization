//
//  ROVarsImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//
//

#include "ROVarsImpl.h"
#include "ROVar.h"
#include "ROUn.h"
#include "ROExpr.h"
#include "ROQVarImpl.h"
#include "ROUnVarImpl.h"
#include "rotempimpl.h"

ROVarsImpl::ROVarsImpl()
{
    
}


ROVarMap& ROVarsImpl::getMap()
{
	return m_varsMap;
}

void ROVarsImpl::insert(const ROVar& p_var)
{
	insertElement<ROVarMap, ROVar, std::plus<ROVarMap::mapped_type> >(m_varsMap, p_var);
}

void ROVarsImpl::insertNeg(const ROVar& p_var)
{
	insertElement<ROVarMap, ROVar, std::minus<ROVarMap::mapped_type> >(m_varsMap, p_var);
}




void ROVarsImpl::times(RONum p_val)
{
	mapOperatedByNum<ROVarMap, std::multiplies<RONum> >(m_varsMap, p_val);
}

void ROVarsImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROVarMap, std::divides<RONum> >(m_varsMap, p_val);
}


void ROVarsImpl::add(ROVarsImpl& p_vars)
{
	mapMerge<ROVarMap, std::plus<ROKeyValue> >(m_varsMap, p_vars.getMap());
}

void ROVarsImpl::addNeg(ROVarsImpl& p_vars)
{
	mapMerge<ROVarMap, std::minus<ROKeyValue> >(m_varsMap, p_vars.getMap());
}
