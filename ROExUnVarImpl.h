//
//  ROExUnVarImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROExUnVarImpl_h
#define RobustOptimizationSolver_ROExUnVarImpl_h

#include "ROTypedefs.h"

class ROVarsImpl;
class ROExUnImpl;
class ROUnVarImpl;

class ROExUnVarImpl
{
public:
    ROExUnVarImpl();
	
	ROExUnVarMap& getMap();

    void times(RONum p_val);
    void divide(RONum p_val);

    void insert(const ROVar& p_var);
	void insertNeg(const ROVar& p_var);

	void add(ROVarsImpl& p_vars);
	void addNeg(ROVarsImpl& p_vars);

	void add(ROExUnImpl& p_exUn);
	void addNeg(ROExUnImpl& p_exUn);

	void add(ROExUnVarImpl& p_exUnVar);
	void addNeg(ROExUnVarImpl& p_exUnVar);

	void expect(ROUnVarImpl& p_unVar);
    
private:
    ROExUnVarMap m_exUnVarMap;
};


#endif
