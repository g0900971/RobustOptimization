//
//  ROBinVar.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 1/6/13.
//
//

#include "ROBinVar.h"

ROBinVar::ROBinVar(const std::string& p_name)
{
    m_var = ROVar(0,1,p_name,EnumROBool);
}


ROBinVar::ROBinVar(const ROBinVar& binVar)
{
    m_var = binVar.getVar();
}

const ROVar& ROBinVar::getVar() const
{
    return m_var;
}

