//
//  ROUn.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//
//

#include "ROUn.h"
#include "ROUnImpl.h"

int ROUn::UniqueId = 1;

ROUn::ROUn()
{
    m_id = generateUniqueId();
    ROUnImplManager::instance().add(boost::shared_ptr<ROUnImpl> (new ROUnImpl(m_id)));        
}

ROUn::ROUn(const ROUn& p_un)
{
	m_id = p_un.getId();
}

int ROUn::getNo()
{
	return UniqueId;
}

int ROUn::getId() const
{
    return m_id;
}

int ROUn::generateUniqueId()
{
    UniqueId++;
	return (UniqueId - 1);
}

void ROUn::resetUniqueId()
{
	UniqueId = 1;
}

ROUn::~ROUn()
{
//    ROUnImplManager::instance().remove(m_id);
}