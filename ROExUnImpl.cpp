//
//  ROExUnImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 10/9/12.
//
//

#include "ROExUnImpl.h"
#include "ROUnsImpl.h"
#include "ROUnVarImpl.h"
#include "rotempimpl.h"
#include "ROUn.h"


ROExUnImpl::ROExUnImpl()
{

}

ROExUnMap& ROExUnImpl::getMap()
{
	return m_exUnMap;
}


void ROExUnImpl::times(RONum p_val)
{
	mapOperatedByNum<ROExUnMap, pairMultipliesNum<ROKeyValue2, RONum> >(m_exUnMap, p_val);
}


void ROExUnImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROExUnMap, pairDividesNum<ROKeyValue2, RONum> >(m_exUnMap, p_val);
}


void ROExUnImpl::expect(const ROUn& p_un)
{
	m_exUnMap.insert(std::make_pair(ROUnIndex(p_un.getId()), std::make_pair(1, 1)));
}

void ROExUnImpl::add(ROExUnImpl& p_exUn)
{
	mapMerge<ROExUnMap, pairPlus<ROKeyValue2> >(m_exUnMap,  p_exUn.getMap());
}

void ROExUnImpl::addNeg(ROExUnImpl& p_exUn)
{
	mapMerge<ROExUnMap, pairMinus<ROKeyValue2> >(m_exUnMap,  p_exUn.getMap());
}

void ROExUnImpl::expect(ROUnsImpl& p_uns)
{
	mapExpect<ROExUnMap, ROUnMap> (m_exUnMap, p_uns.getMap());
}

