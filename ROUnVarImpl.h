//
//  ROUnVarImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUnVarImpl_h
#define RobustOptimizationSolver_ROUnVarImpl_h

#include "ROTypedefs.h"

class ROVarsImpl;
class ROUnsImpl;

class ROUnVarImpl
{
public:
    ROUnVarImpl();
	ROUnVarMap& getMap();

	void times(RONum p_val);
    void divide(RONum p_val);

	void insert(const ROVar& p_var);
	void insertNeg(const ROVar& p_var);

	void insert(const ROUn& p_un);
	void insertNeg(const ROUn& p_un);

	void add(ROVarsImpl& p_vars);
	void addNeg(ROVarsImpl& p_vars);

	void add(ROUnsImpl& p_uns);
	void addNeg(ROUnsImpl& p_uns);

	void add(ROUnVarImpl& p_unvar);
	void addNeg(ROUnVarImpl& p_unvar);

	void addTimes(const ROVar& p_var, const ROUn& p_un);
	void addTimes(const ROUn& p_un, const ROVar& p_var);

	void addTimes(ROVarsImpl& p_varsI, const ROUn& p_un);
	void addTimes(const ROUn& p_un, ROVarsImpl& p_varsI);

	void addTimes(const ROVar& p_var, ROUnsImpl& p_unsI);
	void addTimes(ROUnsImpl& p_unsI, const ROVar& p_var);

	void addTimes(ROVarsImpl& p_lhsI, ROUnsImpl& p_rhsI);
	void addTimes(ROUnsImpl& p_rhsI, ROVarsImpl& p_lhsI);
	
    
private:
    ROUnVarMap m_unVarMap;
};

#endif
