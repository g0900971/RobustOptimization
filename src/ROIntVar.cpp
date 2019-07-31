//
//  ROIntVar.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 1/6/13.
//
//

#include "ROIntVar.h"

ROIntVar::ROIntVar(const double p_lb, const double p_ub, const std::string& p_name)
{
    m_var = ROVar(p_lb, p_ub, p_name, EnumROInt);
}

ROIntVar::ROIntVar(const ROIntVar& var)
{
    m_var = var.getVar();
}

const ROVar& ROIntVar::getVar() const
{
    return m_var;
}


