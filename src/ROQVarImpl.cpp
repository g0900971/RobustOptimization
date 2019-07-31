//
//  ROVarsImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 10/9/12.
//
//

#include "ROQVarImpl.h"
#include "ROVarsImpl.h"
#include "ROExprImpl.h"
#include "ROVar.h"
#include "ROUn.h"
#include "ROExpr.h"
#include "rotempimpl.h"

ROQVarImpl::ROQVarImpl()
{
    
}


ROQVarMap& ROQVarImpl::getMap()
{
	return m_qVarMap;
}

void ROQVarImpl::times(RONum p_val)
{
	mapOperatedByNum<ROQVarMap, std::multiplies<RONum> >(m_qVarMap, p_val);
}


void ROQVarImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROQVarMap, std::divides<RONum> >(m_qVarMap, p_val);
}

void ROQVarImpl::insert(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = 1;

	ROQVarMapIter iter = m_qVarMap.find(index);
	if(iter == m_qVarMap.end())
	{
		m_qVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}

void ROQVarImpl::insertNeg(const ROVar& p_var)
{
	ROKeyIndex2 index(p_var.getId(),0);
	ROKeyValue val = -1;

	ROQVarMapIter iter = m_qVarMap.find(index);
	if(iter == m_qVarMap.end())
	{
		m_qVarMap.insert(std::make_pair(index,val));
	}
	else
	{
		iter->second += val;
	}
}

void ROQVarImpl::addTimes(ROVarsImpl& p_varsI, const ROVar& p_var)
{
	ROVarIndex id(p_var.getId());
	ROVarMapIter iter = p_varsI.getMap().begin();
	while(iter != p_varsI.getMap().end())
	{
		if(iter->first >= id)
		{
			ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROVarIndex>(iter->first, id);

			// Debug Use
			double t_data = iter->second;

			m_qVarMap.insert(std::make_pair(index, iter->second));
		}
		else
		{
			ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROVarIndex>(id, iter->first);

			// Debug Use
			double t_data = iter->second;

			m_qVarMap.insert(std::make_pair(index, iter->second));
		}
		iter++;
	}
}



void ROQVarImpl::addTimes(ROVarsImpl& p_lhsI, ROVarsImpl& p_rhsI)
{
	ROVarMapIter iter1 = p_lhsI.getMap().begin();
	ROVarMapIter iter2 = p_rhsI.getMap().begin();
	ROKeyValue val = 0;

	while(iter1 != p_lhsI.getMap().end())
	{
		while(iter2 != p_rhsI.getMap().end())
		{
			if(iter1->first >= iter2->first)
			{
				ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROVarIndex>(iter1->first, iter2->first);
				val = iter1->second * iter2->second;
				if(m_qVarMap.find(index) == m_qVarMap.end())
				{
					m_qVarMap.insert(std::make_pair(index, val));
				}
				else
				{
					m_qVarMap.find(index)->second +=val;
				}
			}
			else
			{
				ROKeyIndex2 index = updateIndex<ROKeyIndex2, ROVarIndex, ROVarIndex>(iter2->first, iter1->first);
				val = iter1->second * iter2->second;
				if(m_qVarMap.find(index) == m_qVarMap.end())
				{
					m_qVarMap.insert(std::make_pair(index, val));
				}
				else
				{
					m_qVarMap.find(index)->second +=val;
				}
			}
			iter2++;
		}

		iter1++;
	}
}

void ROQVarImpl::addTimes(const ROVar& p_var, ROVarsImpl& p_varsI)
{
	addTimes(p_varsI, p_var);
}



void ROQVarImpl::add(ROQVarImpl& p_qVarI)
{
	mapMerge<ROQVarMap, std::plus<ROKeyValue> >(m_qVarMap, p_qVarI.getMap());
}

void ROQVarImpl::addNeg(ROQVarImpl& p_qVarI)
{
	mapMerge<ROQVarMap, std::minus<ROKeyValue> >(m_qVarMap, p_qVarI.getMap());
}

void ROQVarImpl::add(ROVarsImpl& p_varsI)
{
	mapMerge<ROQVarMap, ROVarMap, std::plus<ROKeyValue> >(m_qVarMap, p_varsI.getMap());
}

void ROQVarImpl::addNeg(ROVarsImpl& p_varsI)
{
	mapMerge<ROQVarMap, ROVarMap, std::minus<ROKeyValue> >(m_qVarMap, p_varsI.getMap());
}