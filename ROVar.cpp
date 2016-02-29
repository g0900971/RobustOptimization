//
//  ROVar.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//  Added by Tianjue Lin on 28/8/12
//
//

#include "ROVar.h"
#include "ROVarImpl.h"
#include "ROIntVar.h"
#include "ROBinVar.h"

int ROVar::UniqueId = 1;

ROVar::ROVar(const double p_lb, const double p_ub,
			 const std::string& p_name, const ROVarType p_type)
{
    m_id = generateUniqueId();
    ROVarImplManager::instance().add(boost::shared_ptr<ROVarImpl>(new ROVarImpl(m_id, p_lb, p_ub, p_name, p_type)));
}

ROVar::ROVar(const ROVar& p_var)
{
	m_id = p_var.getId();
}

ROVar::ROVar(const ROIntVar& p_var)
{
	m_id = p_var.getVar().getId();
}

ROVar::ROVar(const ROBinVar& p_var)
{
	m_id = p_var.getVar().getId();
}

int ROVar::getNo()
{
	return UniqueId;
}

int ROVar::getId() const
{
    return m_id;
}

int ROVar::generateUniqueId()
{
	UniqueId++;
    return (UniqueId - 1);
}

void ROVar::resetUniqueId()
{
	UniqueId = 1;
}

ROVar::~ROVar()
{
}
