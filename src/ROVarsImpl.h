//
//  ROVarMap.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 25/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROVarMap_h
#define RobustOptimizationSolver_ROVarMap_h

#include "ROTypedefs.h"

class ROUnVarImpl;

class ROVarsImpl
{
public:
    ROVarsImpl();
    ROVarMap& getMap();

	void insert(const ROVar& p_var);
	void insertNeg(const ROVar& p_var);

	void times(RONum p_val);
	void divide(RONum p_val);

	void add(ROVarsImpl& p_vars);
	void addNeg(ROVarsImpl& p_vars);
    
private:
    ROVarMap m_varsMap;
};

#endif
