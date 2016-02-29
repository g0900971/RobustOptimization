//
//  ROUnsImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUnsImpl_h
#define RobustOptimizationSolver_ROUnsImpl_h

#include "ROTypedefs.h"

class ROUnsImpl
{
public:
    ROUnsImpl();
    ROUnMap& getMap();

	void insert(const ROUn& p_un);
	void insertNeg(const ROUn& p_un);

	void times(RONum p_val);
	void divide(RONum p_val);

	void add(ROUnsImpl& p_uns);
	void addNeg(ROUnsImpl& p_uns);

private:
    ROUnMap m_unsMap;
};

#endif
