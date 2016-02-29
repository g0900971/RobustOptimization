//
//  ROExpr.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Modified by Meilin Zhang on 29/8/12
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROExpr_h
#define RobustOptimizationSolver_ROExpr_h

#include "ROTypedefs.h"
#include "ROArrayTemplate.h"
class ROExprImpl;
class ROUnVarC;
class ROVarDR;
class ROIntVar;
class ROBinVar;

/**
 * An instance of this class represents an expression in a model.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExpr
{
public:

	/**
	 * This constructor creates an empty expression.
	 */
    ROExpr();

    /**
     * The copy constructor of ROExpr.
     *
     * @param p_expr  A referrence to an ROExpr object.
     */
	ROExpr(const ROExpr& p_expr);

    /**
     * The copy constructor of ROExpr.
     *
     * @param p_var  A referrence to an ROVar object.
     */
	ROExpr(const ROVar& p_var);
    
    /**
     * The copy constructor of ROExpr.
     *
     * @param p_var  A referrence to an ROIntVar object.
     */
	ROExpr(const ROIntVar& p_var);
    
    /**
     * The copy constructor of ROExpr.
     *
     * @param p_var  A referrence to an ROBinVar object.
     */
	ROExpr(const ROBinVar& p_var);

    /**
     * The copy constructor of ROExpr.
     *
     * @param p_un  A referrence to an ROUn object.
     */
	ROExpr(const ROUn& p_un);

    /**
     * The copy constructor of ROExpr.
     *
     * @param val  A RONum number.
     */
    ROExpr(RONum val);

	/**
	 * This member function returns the implementation object of the invoking instance.
	 *
	 * @return  A pointer to the underlying implementation object.
	 */
    boost::shared_ptr<ROExprImpl> getImpl() const;

    /**
     * This is the assignment "=" operator.
     *
     * @param p_num  A number.
     * @return  A reference to current invoking instance.
     */
	ROExpr& operator = (RONum p_num);

    /**
     * This is the assignment "=" operator.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference to current invoking instance.
     */
	ROExpr& operator = (const ROVar& p_var);

	 /**
     * This is the assignment "=" operator.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference to current invoking instance.
     */
	ROExpr& operator = (const ROUn& p_un);

    /**
     * This is the assignment "=" operator.
     *
     * @param p_expr  An object of ROExpr which would be copied by invoking instance.
     * @return  A reference to current invoking instance.
     */
	ROExpr& operator = (const ROExpr& p_expr);


    /**
     * This is the assignment "=" operator.
	 * Caution : might lose underlying constraints attached with ROVarDR.
     *
     * @param p_varDR  An object of ROVarDR which would be copied by invoking instance.
     * @return  A reference to current invoking instance.
     */
	ROExpr& operator = (const ROVarDR& p_varDR);
    

	/**
	 * This is the overloaded operator "+=" between ROExpr and RONum.
	 *
	 * @param p_val  An Object of RONum.
	 * @return  A reference of current invoking instance.
	 */
    ROExpr& operator += (RONum p_val);

    /**
     * This is the overloaded operator "-=" between ROExpr and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
    ROExpr& operator -= (RONum p_val);

    /**
     * This is the overloaded operator "*=" between ROExpr and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
    ROExpr& operator *= (RONum p_val);

    /**
     * This is the overloaded operator "/=" between ROExpr and RONum.
     *
     * @param p_val  An object of RONum.
     * @return  A reference of current invoking instance.
     */
    ROExpr& operator /= (RONum p_val);
    

    /**
     * This is the overloaded operator "+=" between ROExpr and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
    ROExpr& operator += (const ROVar& p_var);

    /**
     * This is the overloaded operator "-=" between ROExpr and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator -= (const ROVar& p_var);


    /**
     * This is the overloaded operator "+=" between ROExpr and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator += (const ROUn& p_un);

    /**
     * This is the overloaded operator "-=" between ROExpr and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator -= (const ROUn& p_un);


    /**
     * This is the overloaded operator "+=" between ROExpr and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator += (const ROExpr& p_expr);

    /**
     * This is the overloaded operator "+=" between ROExpr and ROVarDR.
     *
     * @param p_varDR  A referrence of ROVarDR instance.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator += (const ROVarDR& p_varDR);

    /**
     * This is the overloaded operator "-=" between ROExpr and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator -= (const ROExpr& p_expr);

    /**
     * This is the overloaded operator "-=" between ROExpr and ROVarDR.
     *
     * @param p_varDR  A referrence of ROVarDR instance.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator -= (const ROVarDR& p_varDR);

    /**
     * This is the overloaded operator "*=" between ROExpr and ROVar.
     *
     * @param p_var  An object of ROVar.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator *=(const ROVar& p_var);

    /**
     * This is the overloaded operator "*=" between ROExpr and ROUn.
     *
     * @param p_un  An object of ROUn.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator *=(const ROUn& p_un);

    /**
     * This is the overloaded operator "*=" between ROExpr and ROExpr.
     *
     * @param p_expr  An object of ROExpr.
     * @return  A reference of current invoking instance.
     */
	ROExpr& operator *=(const ROExpr& p_expr);

	/**
	 * This member function takes the expected form of given ROUn.
	 *
	 * @param p_un  An object of ROUn.
	 * @return  A reference of current invoking instance.
	 */
	ROExpr& expect(const ROUn& p_un);

	/**
	 * This member function takes the expected form of given ROExpr.
	 *
	 * @param p_expr  An object of ROExpr.
	 * @return  A reference of current invoking instance.
	 */
	ROExpr& expect(const ROExpr& p_expr);

	/**
	 * Destructor of ROExpr.
	 *
	 */
	~ROExpr();

private:
    boost::shared_ptr<ROExprImpl>  m_exprImpl;
};

typedef ROArray<ROExpr> ROExprArray;

#endif
