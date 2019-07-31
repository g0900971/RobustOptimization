//
//  ROUnVarImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 5/9/12.
//
//

#include "ROVarsImpl.h"
#include "ROUnsImpl.h"
#include "ROVar.h"
#include "ROUn.h"
#include "ROExpr.h"
#include "ROUnVarImpl.h"
#include "rotempimpl.h"

ROUnVarImpl::ROUnVarImpl()
{
    
}


ROUnVarMap& ROUnVarImpl::getMap()
{
	return m_unVarMap;
}


void ROUnVarImpl::times(RONum p_val)
{
	mapOperatedByNum<ROUnVarMap, std::multiplies<RONum> >(m_unVarMap, p_val);
}

void ROUnVarImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROUnVarMap, std::divides<RONum> >(m_unVarMap, p_val);
}

void ROUnVarImpl::insert(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = 1;

	ROUnVarMapIter iter = m_unVarMap.find(index);
	if(iter == m_unVarMap.end())
	{
		m_unVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}

void ROUnVarImpl::insertNeg(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = -1;

	ROUnVarMapIter iter = m_unVarMap.find(index);
	if(iter == m_unVarMap.end())
	{
		m_unVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}

void ROUnVarImpl::insert(const ROUn& p_un)
{
	ROKeyIndex2 index(0, p_un.getId());
	ROKeyValue val = 1;

	ROUnVarMapIter iter = m_unVarMap.find(index);
	if(iter == m_unVarMap.end())
	{
		m_unVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}

void ROUnVarImpl::insertNeg(const ROUn& p_un)
{
	ROKeyIndex2 index(0, p_un.getId());
	ROKeyValue val = -1;

	ROUnVarMapIter iter = m_unVarMap.find(index);
	if(iter == m_unVarMap.end())
	{
		m_unVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}


void ROUnVarImpl::add(ROVarsImpl& p_vars)
{
	mapMerge<ROUnVarMap, ROVarMap, std::plus<ROUnVarMap::mapped_type> >(m_unVarMap,  p_vars.getMap());
}

void ROUnVarImpl::addNeg(ROVarsImpl& p_vars)
{
	mapMerge<ROUnVarMap, ROVarMap, std::minus<ROUnVarMap::mapped_type> >(m_unVarMap,  p_vars.getMap());
}

void ROUnVarImpl::add(ROUnsImpl& p_uns)
{
	mapMerge<ROUnVarMap, ROUnMap, std::plus<ROUnVarMap::mapped_type> >(m_unVarMap,  p_uns.getMap());
}

void ROUnVarImpl::addNeg(ROUnsImpl& p_uns)
{
	mapMerge<ROUnVarMap, ROUnMap, std::minus<ROUnVarMap::mapped_type> >(m_unVarMap,  p_uns.getMap());
}

void ROUnVarImpl::add(ROUnVarImpl& p_unvar)
{
	mapMerge<ROUnVarMap, std::plus<ROKeyValue> >(m_unVarMap,  p_unvar.getMap());
}

void ROUnVarImpl::addNeg(ROUnVarImpl& p_unvar)
{
	mapMerge<ROUnVarMap, std::minus<ROKeyValue> >(m_unVarMap,  p_unvar.getMap());
}



void ROUnVarImpl::addTimes(const ROVar& p_var, const ROUn& p_un)
{
	m_unVarMap.insert(std::make_pair( std::make_pair(p_var.getId(), p_un.getId()), 1));
}

void ROUnVarImpl::addTimes(const ROUn& p_un, const ROVar& p_var)
{
	m_unVarMap.insert(std::make_pair( std::make_pair(p_var.getId(), p_un.getId()), 1));
}


void ROUnVarImpl::addTimes(ROVarsImpl& p_varsI, const ROUn& p_un)
{
	ROUnIndex id(p_un.getId());
	ROVarMapIter iter = p_varsI.getMap().begin();
	while(iter != p_varsI.getMap().end())
	{
		ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROUnIndex>(iter->first, id);
		m_unVarMap.insert(std::make_pair(index, iter->second));

		iter++;
	}
}

void ROUnVarImpl::addTimes(const ROUn& p_un, ROVarsImpl& p_varsI)
{
	addTimes(p_varsI, p_un);
}



void ROUnVarImpl::addTimes(ROUnsImpl& p_unsI, const ROVar& p_var)
{
	ROVarIndex id(p_var.getId());
	ROUnMapIter iter = p_unsI.getMap().begin();
	while(iter != p_unsI.getMap().end())
	{
		ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROUnIndex>(id, iter->first);
		m_unVarMap.insert(std::make_pair(index, iter->second));

		iter++;
	}
}


void ROUnVarImpl::addTimes(const ROVar& p_var, ROUnsImpl& p_unsI)
{
	addTimes(p_unsI, p_var);
}

void ROUnVarImpl::addTimes(ROVarsImpl& p_lhsI, ROUnsImpl& p_rhsI)
{
	ROVarMapIter iter1 = p_lhsI.getMap().begin();
	ROUnMapIter iter2 = p_rhsI.getMap().begin();
	ROKeyValue val = 0;

	while(iter1 != p_lhsI.getMap().end())
	{
		while(iter2 != p_rhsI.getMap().end())
		{
			ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROUnIndex>(iter1->first, iter2->first);
			val = iter1->second * iter2->second;
			m_unVarMap.insert(std::make_pair(index, val));
			iter2++;
		}
		iter1++;
	}
}

void ROUnVarImpl::addTimes(ROUnsImpl& p_rhsI, ROVarsImpl& p_lhsI)
{
	addTimes(p_lhsI, p_rhsI);
}

