//
//  ROExUnImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROExUnImpl_h
#define RobustOptimizationSolver_ROExUnImpl_h

#include "ROTypedefs.h"

class ROUnsImpl;
class ROUnVarImpl;

class ROExUnImpl
{
public:
    ROExUnImpl();

	ROExUnMap& getMap();

	void times(RONum p_val);
    void divide(RONum p_val);

	void expect(const ROUn& p_un);

	void add(ROExUnImpl& p_unvar);
	void addNeg(ROExUnImpl& p_unvar);

	void expect(ROUnsImpl& p_uns);
    
private:
    ROExUnMap m_exUnMap;
};

#endif
