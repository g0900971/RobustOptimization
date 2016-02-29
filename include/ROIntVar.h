//
//  ROIntVar.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 31/05/13.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROIntVar_h
#define RobustOptimizationSolver_ROIntVar_h

#include "ROVar.h"

/**
 * An instance of this class is an integer variable without uncertainty.
 *
 * Date: 31-May-2013
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROIntVar
{
public:
	/**
	 * This constructor creates an ROIntVar instance from given lower bound, upper bound, and name.
	 *
	 * @param p_lb  lower bound of invoking object.
	 * @param p_ub  upper bound of invoking object.
	 * @param p_name  name of invoking object.
	 */
    ROIntVar(const double p_lb = RONInfinity, const double p_ub = ROInfinity, const std::string& p_name = "");

	/**
	 * The copy constructor.
	 */
	ROIntVar(const ROIntVar&);
    
    /**
     * Get the variable
     */
    const ROVar& getVar() const;
    
private:
    ROVar m_var;

};

#endif