//
//  ROUnLinConstraint.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUnLinConstraint_h
#define RobustOptimizationSolver_ROUnLinConstraint_h

#include "ROTypedefs.h"
#include "ROArrayTemplate.h"

class ROExpr;
class ROBaseConstraint;


/**
 * An instance of this class is an uncertain linear constraint in a model. A base constraint consists of its equation tag and an expression (LHS).
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROUnLinConstraint
{
public:

	/**
	 * This is the copy constructor.
	 *
	 * @param p_unConst  An object of ROUnLinConstraint.
	 */
	ROUnLinConstraint(const ROUnLinConstraint& p_unConst);

	/**
	 * This is the copy constructor.
	 *
	 * @param p_baseConst  An object of ROBaseConstraint.
	 */
	ROUnLinConstraint(const ROBaseConstraint& p_baseConst);

	/**
	 * This constructor creates an ROUnLinConstraint from given LHS (left hand side) expression and equation tag ("<=" or "==").
	 *
	 * @param p_expr  A pointer to ROExpr (LHS expression).
	 * @param p_tag  The equation tag, either "<=" or "==".
	 */
	ROUnLinConstraint(const boost::shared_ptr<ROExpr> p_expr, const ROConstTag p_tag = EnumLeq);

	/**
	 * The default constructor of ROUnLinConstraint.
	 */
	ROUnLinConstraint(const ROConstTag p_tag = EnumLeq);


	/**
	 * The assignment operator "=".
	 *
	 * @param p_expr  An object of ROUnLinConstraint.
	 * @return  A reference of current invoking object.
	 */
	ROUnLinConstraint& operator = (const ROUnLinConstraint& p_expr);

	 /**
	 * The assignment operator "=".
	 *
	 * @param p_expr  An object of ROUnLinConstraint.
	 * @return  A reference of current invoking object.
	 */
	ROUnLinConstraint& operator = (const ROBaseConstraint& p_expr);

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

typedef ROArray<ROUnLinConstraint> ROUnLinConstraintArray;

#endif
