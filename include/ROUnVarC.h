//
//  ROUnVarC.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 06/10/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUnVarC_h
#define RobustOptimizationSolver_ROUnVarC_h

#include "ROTypedefs.h"

class ROConstraintSet;

/**
 * An instance of this class is a composite expression.
 *
 * Date: 1-Nov-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROUnVarC
{
public:

	/**
	 * This constructor creates an empty expression of ROUnVarC.
	 */
	ROUnVarC();

	/**
	 * The copy constructor of ROUnVarC.
	 */
	ROUnVarC(const ROUnVarC& p_unC);

    /**
     * This is the assignment "=" operator.
     *
     * @param p_unC  A referrence to a ROUnVarC object.
     * @return  A reference to current invoking instance.
     */
	ROUnVarC& operator = (const ROUnVarC& p_unC);

    /**
     * This is the assignment "=" operator.
     *
     * @param p_expr  A referrence to a ROExpr object.
     * @return  A reference to current invoking instance.
     */
	ROUnVarC& operator = (const ROExpr& p_expr);

	/**
	 * This is the overloaded operator "+=" between ROUnVarC and RONum.
	 *
	 * @param p_val  An Object of RONum.
	 * @return  A reference of current invoking instance.
	 */
	ROUnVarC& operator += (RONum p_val);

    /**
     * This is the overloaded operator "-=" between ROUnVarC and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator -= (RONum p_val);

    /**
     * This is the overloaded operator "*=" between ROUnVarC and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator *= (RONum p_val);

    /**
     * This is the overloaded operator "/=" between ROUnVarC and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator /= (RONum p_val);


    /**
     * This is the overloaded operator "+=" between ROUnVarC and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator += (const ROVar& p_var);

    /**
     * This is the overloaded operator "-=" between ROUnVarC and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator -= (const ROVar& p_var);


    /**
     * This is the overloaded operator "+=" between ROUnVarC and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator += (const ROUn& p_un);

    /**
     * This is the overloaded operator "-=" between ROUnVarC and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator -= (const ROUn& p_un);


    /**
     * This is the overloaded operator "+=" between ROUnVarC and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator += (const ROExpr& p_expr);

    /**
     * This is the overloaded operator "+=" between ROUnVarC and ROUnVarC.
     *
     * @param p_varC  An object of ROUnVarC.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator += (const ROUnVarC& p_varC);

    /**
     * This is the overloaded operator "-=" between ROUnVarC and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator -= (const ROExpr& p_expr);

    /**
     * This is the overloaded operator "-=" between ROUnVarC and ROUnVarC.
     *
     * @param p_unC  An object of ROUnVarC.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator -= (const ROUnVarC& p_unC);


    /**
     * This is the overloaded operator "*=" between ROUnVarC and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator *=(const ROVar& p_var);

    /**
     * This is the overloaded operator "*=" between ROUnVarC and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator *=(const ROUn& p_un);

    /**
     * This is the overloaded operator "*=" between ROUnVarC and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROUnVarC& operator *=(const ROExpr& p_expr);

	/**
	 * This member function takes the expected form of given ROUn.
	 *
	 * @param p_un  An object of ROUn.
	 * @return  A reference of current invoking instance.
	 */
	ROUnVarC& expect(const ROUn& p_un);

	/**
	 * This member function takes the expected form of given ROExpr.
	 *
	 * @param p_expr  An object of ROExpr.
	 * @return  A reference of current invoking instance.
	 */
	ROUnVarC& expect(const ROExpr& p_expr);
	// -----------


	/**
	 * This member function sets the primary ROExpr of invoking object.
	 *
	 * @param p_expr  An object of ROExpr.
	 */
	void setExpr(boost::shared_ptr<ROExpr> p_expr);

	/**
	 * This member function sets the constraints set.
	 *
	 * @param p_constSet  An object of ROConstraintSet.
	 */
	void setConstSet(boost::shared_ptr<ROConstraintSet> p_constSet);


	/**
	 * This member function returns the primary ROExpr of invoking object.
	 *
	 * @return  A shared pointer to ROExpr.
	 */
	boost::shared_ptr<ROExpr> getExpr() const;


	/**
	 * This member function returns the constraint set of invoking object.
	 *
	 * @return  A shared pointer to ROConstraintSet.
	 */
	boost::shared_ptr<ROConstraintSet> getConstSet() const;

private:
	boost::shared_ptr<ROExpr> m_expr;
	boost::shared_ptr<ROConstraintSet> m_constSet;

};

#endif