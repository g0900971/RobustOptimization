//
//  ROUnSOCConstraint.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUnSOCConstraint_h
#define RobustOptimizationSolver_ROUnSOCConstraint_h

#include "ROTypedefs.h"
#include "ROExpr.h"

/**
 * An instance of this class is a norm uncertainty constraint in a ROConstraint.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROUnSOCConstraint
{
public:
	/**
	 * This constructor creates an empty norm uncertainty constraint. It must be initialized before use.
	 */
	ROUnSOCConstraint();

	/**
	 * This copy constructor, which creates from another ROUnSOCConstraint object.
	 */
	ROUnSOCConstraint(const ROUnSOCConstraint&);

	/**
	 * This constructor creates a SOC uncertainty constraint from a pointer to ROExpr and a pointer to ROExpr,
	 * the default equation tag is "<="
	 *
	 * @param p_exprL  A shared_ptr to ROExpr.
	 * @param p_exprR  A shared_ptr to ROExpr.
	 */
	ROUnSOCConstraint(const boost::shared_ptr<ROExpr> p_exprL, boost::shared_ptr<ROExpr> p_exprR);

	/**
	 * This constructor creates a SOC uncertainty constraint from a pointer to ROExpr and a pointer to ROExprArray,
	 * the default equation tag is ">="
	 *
	 * @param p_expr  A shared_ptr to ROExpr.
	 * @param p_exprArray  A shared_ptr to ROExprArray.
	 */
    ROUnSOCConstraint(const boost::shared_ptr<ROExpr> p_expr, boost::shared_ptr<ROExprArray> p_exprArray);

	/**
	 * This constructor creates a norm uncertainty constraint from a pointer to ROExpr and a pointer to ROExprArray,
	 * the default equation tag is "<="
	 *
	 * @param p_exprArray  A shared_ptr to ROExprArray.
	 * @param p_expr  A shared_ptr to ROExpr.
	 */
    ROUnSOCConstraint(boost::shared_ptr<ROExprArray> p_exprArray, const boost::shared_ptr<ROExpr> p_expr);

    /**
     * This constructor creates a norm uncertainty constraint from an object of ROExpr and an object of ROExprArray.
	 * the default equation tag is "<="
	 *
     * @param p_exprArray  An object of ROExprArray.
     * @param p_expr  An object of ROExpr.
     */
	ROUnSOCConstraint(ROExprArray& p_exprArray, const ROExpr& p_expr);

    /**
     * This constructor creates a SOC uncertainty constraint from an object of ROExpr and an object of ROExprArray.
	 * the default equation tag is "<="
	 *
     * @param p_unArray  An object of ROUnArray.
     * @param p_expr  An object of ROExpr.
     */
	ROUnSOCConstraint(ROUnArray& p_unArray, const ROExpr& p_expr);

    /**
     * This constructor creates a norm uncertainty constraint from an object of ROExpr and an object of ROExprArray.
	 * the default equation tag is ">="
	 *
     * @param p_expr  An object of ROExpr.
     * @param p_exprArray  An object of ROExprArray.
     */
	ROUnSOCConstraint(const ROExpr& p_expr, ROExprArray& p_exprArray);

	/**
	 * This constructor creates a SOC uncertainty constraint from two instances of ROExpr.
	 * the default equation tag is "<="
	 *
	 * @param p_exprL  A referrence to ROExpr.
	 * @param p_exprR  A referrence to ROExpr.
	 */
	ROUnSOCConstraint(const ROExpr& p_exprL, const ROExpr& p_exprR);


	/**
	 * This is the assignment operator "=".
	 *
	 * @param  An object of ROUnSOCConstraint.
	 */
	ROUnSOCConstraint& operator = (const ROUnSOCConstraint& p_normConst);


	/**
	 * This member function returns the ROExpr of invoking object.
	 *
	 * @return  A shared_ptr to ROExpr of invoking object.
	 */
	boost::shared_ptr<ROExpr> getExpr() const;

	/**
	 * This member function returns the ROExprArray of invoking object.
	 *
	 * @return  A shared_ptr to ROExprArray of invoking object.
	 */
	boost::shared_ptr<ROExprArray> getExprArray() const;

private:
	boost::shared_ptr<ROExpr> m_expr;
    boost::shared_ptr<ROExprArray> m_exprArray;

};

typedef ROArray<ROUnSOCConstraint> ROUnSOCConstraintArray;

#endif
