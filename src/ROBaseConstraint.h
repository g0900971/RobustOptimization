//
//  ROBaseConstraint.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROBaseConstraint_h
#define RobustOptimizationSolver_ROBaseConstraint_h

#include "ROTypedefs.h"
#include "ROArrayTemplate.h"

class ROExpr;
class ROUnLinConstraint;


/**
 * An instance of this class is a base constraint in a model. A base constraint consists of its equation tag and an expression (LHS).
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROBaseConstraint
{
public:
	/**
	 * This is the copy constructor.
	 *
	 * @param p_bConst  An object of ROBaseConstraint.
	 */
	ROBaseConstraint(const ROBaseConstraint& p_bConst);

	/**
	 * This is the copy constructor.
	 *
	 * @param p_unConst  An object of ROUnLinConstraint.
	 */
	ROBaseConstraint(const ROUnLinConstraint& p_unConst);

	/**
	 * This constructor creates an ROBaseConstraint from given LHS (left hand side) expression and equation tag ("<=" or "==").
	 *
	 * @param  A pointer to ROExpr (LHS expression).
	 * @param  The equation tag, either "<=" or "==".
	 */
	ROBaseConstraint(const boost::shared_ptr<ROExpr> p_expr, const ROConstTag p_tag = EnumLeq);

	/**
	 * The default constructor of ROBaseConstraint.
	 */
	ROBaseConstraint(const ROConstTag p_tag = EnumLeq);

	/**
	 * The assignment operator "=".
	 *
	 * @param  An object of ROBaseConstraint.
	 * @return  A reference of current invoking object.
	 */
	ROBaseConstraint& operator = (const ROBaseConstraint& p_expr);

	/**
	 * The assignment operator "=".
	 *
	 * @param  An object of ROUnLinConstraint.
	 * @return  A reference of current invoking object.
	 */
	ROBaseConstraint& operator = (const ROUnLinConstraint& p_expr);

	/**
	 * This member function returns a pointer of ROExpr (LHS expression) of invoking object.
	 *
	 * @return  A pointer to ROExpr of invoking object.
	 */
	boost::shared_ptr<ROExpr> getExpr() const;

	/**
	 * This member function returns the equation tag ("<=" or "==") of invoking object.
	 *
	 * @return  The equation tag ("<=" or "==") of invoking object.
	 */
    ROConstTag getTag() const;

private:
    boost::shared_ptr<ROExpr> m_expr;
    ROConstTag m_tag;
};

typedef ROArray<ROBaseConstraint> ROBaseConstraintArray;

#endif
