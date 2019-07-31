//
//  ROObjective.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Modified by Meilin Zhang on 23/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROObjective_h
#define RobustOptimizationSolver_ROObjective_h

#include "ROTypedefs.h"

/**
 * An instance of this class is an objective in a model. An objective consists of its obj tag and an expression.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROObjective
{
public:

	/**
	 * This constructor creates an ROObjective object from given ROExpr and ROObjectiveTag.
	 *
	 * @param p_expr  An shared pointer of ROExpr object.
	 * @param p_tag  The ROObjective tag. (Minimize or Maximize).
	 */
    ROObjective(const boost::shared_ptr<ROExpr> p_expr, const ROObjectiveTag p_tag = EnumMin);

	// --- II from composite constraint set ---

	/**
	 * This constructor creates an ROObjective object from given ROExpr, uncertainty set and ROObjectiveTag.
	 *
	 * @param p_expr  An shared pointer of ROExpr object.
	 * @param p_constSet A referrence to the uncertainty set.
	 * @param p_tag  The ROObjective tag. (Minimize or Maximize).
	 */
	ROObjective(const boost::shared_ptr<ROExpr> p_expr, const ROConstraintSet& p_constSet, const ROObjectiveTag p_tag = EnumMin);

	/**
	 * This constructor creates an ROObjective object from given ROUnVarC, uncertainty set and ROObjectiveTag.
	 *
	 * @param p_unVarC  An shared pointer of ROUnVarC object.
	 * @param p_constSet A referrence to the uncertainty set.
	 * @param p_tag  The ROObjective tag. (Minimize or Maximize).
	 */
	ROObjective(const ROUnVarC& p_unVarC, const ROConstraintSet&, const ROObjectiveTag p_tag = EnumMin);

	/**
	 * This constructor creates an ROObjective object from given ROUnVarC and ROObjectiveTag.
	 *
	 * @param p_unVarC  An shared pointer of ROUnVarC object.
	 * @param p_tag  The ROObjective tag. (Minimize or Maximize).
	 */
	ROObjective(const ROUnVarC& p_unVarC, const ROObjectiveTag p_tag = EnumMin);

	// --- End ---

    /**
     * This is the copy constructor of ROObjective.
     *
     * @param p_obj  An object of ROObjective.
     */
	ROObjective(const ROObjective& p_obj);

	/**
	 * This is the assignment operator "=".
	 *
	 * @param  An object of ROObjective.
	 * @return  The reference of current invoking object.
	 */
	ROObjective& operator = (const ROObjective& p_obj);

	/**
	 * This member function returns a share pointer to the ROExpr within this invoking objective.
	 *
	 * @return  A shared_ptr of ROExpr (member of invoking ROObjective instance).
	 */
	boost::shared_ptr<ROExpr> getExpr() const;

	/**
	 * This member function returns a share pointer to the uncertainty set within this invoking objective.
	 *
	 * @return  A shared_ptr of ROConstraintSet.
	 */
	boost::shared_ptr<ROConstraintSet> getConstSet() const;

	/**
	 * This member function returns the objective tag of invoking objective. (Minimize or Maximize)
	 *
	 * @return  The ROObjective tag of invoking objective instance.
	 */
	ROObjectiveTag getTag() const;

private:
    boost::shared_ptr<ROExpr> m_expr;
	boost::shared_ptr<ROConstraintSet> m_constSet;
    ROObjectiveTag m_obj_tag;
    
};

#endif
