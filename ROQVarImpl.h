//
//  ROQVarImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROQVarImpl_h
#define RobustOptimizationSolver_ROQVarImpl_h

#include "ROTypedefs.h"
class ROVarsImpl;
class ROExprImpl;

class ROQVarImpl
{
public:
    ROQVarImpl();
    ROQVarMap& getMap();

    void times(RONum p_val);
    void divide(RONum p_val);

    void insert(const ROVar& p_var);
    void insertNeg(const ROVar& p_var);

	void addTimes(ROVarsImpl& p_varsI, const ROVar& p_var);
	void addTimes(ROVarsImpl& p_lhsI, ROVarsImpl& p_rhsI);
	void addTimes(const ROVar& p_var, ROVarsImpl& p_varsI);

	void add(ROQVarImpl& p_qVarI);
	void addNeg(ROQVarImpl& p_qVarI);

	void add(ROVarsImpl& p_varsI);
	void addNeg(ROVarsImpl& p_varsI);

private:
    ROQVarMap m_qVarMap;
};


#endif
