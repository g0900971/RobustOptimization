//
//  ROExprImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 11/9/12.
//
//

#include "ROExUnVarImpl.h"
#include "ROVar.h"
#include "ROVarsImpl.h"
#include "ROExUnImpl.h"
#include "ROUnVarImpl.h"
#include "rotempimpl.h"

ROExUnVarImpl::ROExUnVarImpl()
{

}

ROExUnVarMap& ROExUnVarImpl::getMap()
{
	return m_exUnVarMap;
}

void ROExUnVarImpl::times(RONum p_val)
{
	mapOperatedByNum<ROExUnVarMap, pairMultipliesNum<ROKeyValue2, RONum> >(m_exUnVarMap, p_val);
}


void ROExUnVarImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROExUnVarMap, pairDividesNum<ROKeyValue2, RONum> >(m_exUnVarMap, p_val);	
}

void ROExUnVarImpl::insert(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = 1;

	ROExUnVarMapIter iter = m_exUnVarMap.find(index);
	if(iter == m_exUnVarMap.end())
	{
		m_exUnVarMap.insert(std::make_pair(index,std::make_pair(val,0)));
	}
	else
	{
		iter->second.first += val;
	}	
}

void ROExUnVarImpl::insertNeg(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = -1;

	ROExUnVarMapIter iter = m_exUnVarMap.find(index);
	if(iter == m_exUnVarMap.end())
	{
		m_exUnVarMap.insert(std::make_pair(index,std::make_pair(val,0)));
	}
	else
	{
		iter->second.first += val;
	}
}


void ROExUnVarImpl::add(ROVarsImpl& p_vars)
{
	mapMerge<ROExUnVarMap, ROVarMap, pairPlusNum<ROKeyValue2, ROKeyValue> >(m_exUnVarMap,  p_vars.getMap());
}

void ROExUnVarImpl::addNeg(ROVarsImpl& p_vars)
{
	mapMerge<ROExUnVarMap, ROVarMap, pairMinusNum<ROKeyValue2, ROKeyValue> >(m_exUnVarMap,  p_vars.getMap());
}


void ROExUnVarImpl::add(ROExUnImpl& p_exUn)
{
	mapMerge<ROExUnVarMap, ROExUnMap, pairPlus<ROExUnVarMap::mapped_type> >(m_exUnVarMap,  p_exUn.getMap());
}

void ROExUnVarImpl::addNeg(ROExUnImpl& p_exUn)
{
	mapMerge<ROExUnVarMap, ROExUnMap, pairMinus<ROExUnVarMap::mapped_type> >(m_exUnVarMap,  p_exUn.getMap());
}


void ROExUnVarImpl::add(ROExUnVarImpl& p_exUnVar)
{
	mapMerge<ROExUnVarMap, pairPlus<ROKeyValue2> >(m_exUnVarMap,  p_exUnVar.getMap());
}

void ROExUnVarImpl::addNeg(ROExUnVarImpl& p_exUnVar)
{
	mapMerge<ROExUnVarMap, pairMinus<ROKeyValue2> >(m_exUnVarMap,  p_exUnVar.getMap());
}

void ROExUnVarImpl::expect(ROUnVarImpl& p_unVar)
{
	mapExpect<ROExUnVarMap, ROUnVarMap> (m_exUnVarMap, p_unVar.getMap());
}