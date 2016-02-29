//
//  ROUnImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//
//

#include "ROUnImpl.h"

ROUnImplManager* ROUnImplManager::m_instance = NULL;

ROUnImpl::ROUnImpl(const int p_id):
    m_id(p_id)
{
    
}


ROUnImplManager& ROUnImplManager::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new ROUnImplManager();
    }
    return *m_instance;
}
/*
void ROUnImplManager::destroy()
{
	delete m_instance;
	m_instance = NULL;
}
*/

void ROUnImplManager::add(const boost::shared_ptr<ROUnImpl> p_impl)
{
    m_unMap.insert(std::make_pair(p_impl->getId(), p_impl));
}

void ROUnImplManager::remove(const int p_id)
{
    UnMapIterator iter = m_unMap.find(p_id);
    if(iter != m_unMap.end())
    {
        m_unMap.erase(iter);
    }
}

bool ROUnImplManager::findId(const int p_id)
{
    UnMapIterator iter = m_unMap.find(p_id);
    if(iter != m_unMap.end())
    {
        return true;
    }
    return false;
}

ROUnIMap& ROUnImplManager::getMap()
{
	return m_unMap;
}

void ROUnImplManager::clear()
{
	m_unMap.clear();
}
