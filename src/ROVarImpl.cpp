//
//  ROVarImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//  Added by Tianjue Lin on 28/8/12
//
//

#include "ROVarImpl.h"
#include "roexceptions.h"


ROVarImpl::ROVarImpl(const int p_id, const double p_lb, const double p_ub, 
					 const std::string& p_name, const ROVarType p_type):
    m_id(p_id),
    m_lb(p_lb),
    m_ub(p_ub),
	m_type(p_type),
    m_name(p_name)
{
    
}

ROVarImplManager* ROVarImplManager::m_instance = NULL;

ROVarImplManager& ROVarImplManager::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new ROVarImplManager();
    }
    
    return *m_instance;
}

void ROVarImplManager::add(const boost::shared_ptr<ROVarImpl> p_impl)
{
    m_varMap.insert(std::make_pair(p_impl->getId(), p_impl));
}


bool ROVarImplManager::findId(const int p_id)
{
    VarMapIterator iter = m_varMap.find(p_id);
    if(iter != m_varMap.end())
    {
        return true;
    }
    return false;
}

ROVarIMap& ROVarImplManager::getMap()
{
	return m_varMap;
}

void ROVarImplManager::remove(const int id)
{
	VarMapIterator iter = m_varMap.find(id);
	if(iter != m_varMap.end())
	{
		m_varMap.erase(iter);
	}
}

void ROVarImplManager::clear()
{
	m_varMap.clear();
}

/*
 void ROVarImplManager::destroy()
 {
	 if(m_instance != NULL)
	 {
		 delete m_instance;
		 m_instance = NULL;
	 }
 }
 */