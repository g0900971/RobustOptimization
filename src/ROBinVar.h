//
//  ROBinVar.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 31/05/13.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROBinVar_h
#define RobustOptimizationSolver_ROBinVar_h

#include "ROVar.h"


/**
 * An instance of this class is an binary variable without uncertainty.
 *
 * Date: 31-May-2013
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROBinVar
{
public:
	/**
	 * This constructor creates an ROBinVar instance from given name.
	 *
	 * @param p_name  name of invoking object.
	 */
    ROBinVar(const std::string& p_name = "");

	/**
	 * The copy constructor.
	 */
	ROBinVar(const ROBinVar&);
    
    /**
     * Get the variable
     */
    const ROVar& getVar() const;
    
private:
    ROVar m_var;
    
};

#endif