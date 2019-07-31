//
//  ROVar.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 27/8/12.
//  Modifed by Tianjue Lin on 28/8/12
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROVar_h
#define RobustOptimizationSolver_ROVar_h

#include "ROTypedefs.h"

class ROVarImpl;
class ROVarsImpl;
class ROIntVar;
class ROBinVar;

/**
 * An instance of this class is an variable without uncertainty.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROVar
{
public:
	/**
	 * This constructor creates an ROVar instance from given lower bound, upper bound, and name.
	 *
	 * @param p_lb  lower bound of invoking object.
	 * @param p_ub  upper bound of invoking object.
	 * @param p_name  name of invoking object.
	 * @param p_type  type of variable, e.g. int, bool, double
	 */
    ROVar(const double p_lb = RONInfinity, const double p_ub = ROInfinity, 
		  const std::string& p_name = "", const ROVarType p_type = EnumROVar);

	/**
	 * The copy constructor.
	 */
	ROVar(const ROVar&);
    
    /**
	 * The copy constructor.
     * Date: 2013-06-01
	 */
	ROVar(const ROIntVar&);
    
    /**
	 * The copy constructor.
     * Date: 2013-06-01
	 */
	ROVar(const ROBinVar&);

    /**
     * Return the number of variables created.
     */
	static int getNo();

	/**
	 * This member function returns the unique ID of invoking variable.
	 *
	 * @return  Unique ID of invoking object.
	 */
    int getId() const;

    /**
     * The destructor of ROVar.
     *
     */
    ~ROVar();
    
private:
	friend class ROModel;

    int m_id;
    static int generateUniqueId();
	static void resetUniqueId();
    static int UniqueId;
};

#endif
