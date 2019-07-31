//
//  ROUnsImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//
//

#include "ROUnsImpl.h"
#include "ROUn.h"
#include "rotempimpl.h"

ROUnsImpl::ROUnsImpl():
	m_unsMap(0)
{
    
}

ROUnMap& ROUnsImpl::getMap()
{
	return m_unsMap;
}

void ROUnsImpl::insert(const ROUn& p_un)
{
	insertElement<ROUnMap, ROUn, std::plus<ROUnMap::mapped_type> >(m_unsMap, p_un);
}

void ROUnsImpl::insertNeg(const ROUn& p_un)
{
	insertElement<ROUnMap, ROUn, std::minus<ROUnMap::mapped_type> >(m_unsMap, p_un);
}

void ROUnsImpl::times(RONum p_val)
{
	mapOperatedByNum<ROUnMap, std::multiplies<RONum> >(m_unsMap, p_val);
}

void ROUnsImpl::divide(RONum p_val)
{
	mapOperatedByNum<ROUnMap, std::divides<RONum> >(m_unsMap, p_val);
}

void ROUnsImpl::add(ROUnsImpl& p_uns)
{
	mapMerge<ROUnMap, std::plus<ROKeyValue> >(m_unsMap, p_uns.getMap());
}

void ROUnsImpl::addNeg(ROUnsImpl& p_uns)
{
	mapMerge<ROUnMap, std::minus<ROKeyValue> >(m_unsMap, p_uns.getMap());
}


