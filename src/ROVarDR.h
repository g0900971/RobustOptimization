//
//  ROVarDR.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 05/10/12.
//  Modified by Meilin Zhang on 23/10/12.
//  Modified by Meilin Zhang on 24/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROVarDR_h
#define RobustOptimizationSolver_ROVarDR_h

#include "ROTypedefs.h"

class ROVarDRImpl;

/**
 * An instance of this class is a decision rule variable.
 *
 * Date: 1-Nov-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROVarDR
{
public:

	/**
	 * This constructor creates a decision rule variable without uncertainty.
	 */
	ROVarDR();


	/**
	 * This member function returns the implementation object of the invoking instance.
	 *
	 * @return  A pointer to the underlying implementation object.
	 */
	boost::shared_ptr<ROVarDRImpl> getImpl() const;

	/**
	 * This member function returns the ROExpr of invoking object.
	 *
	 * @return  A shared pointer to ROExpr.
	 */
	ROExpr getExpr() const;


	/**
	 * This member function returns the referrence to the variable related to given uncertainty ROExpr.
	 *
	 * @param p_expr  A referrence to uncertain ROExpr
	 * @return  A referrence to ROVar.
	 */
	ROVar& getVar(ROExpr& p_expr) const;

	/**
	 * This member function returns the referrence to the variable related to given uncertainty ROUn.
	 *
	 * @param p_un  A referrence to uncertain ROUn
	 * @return  A referrence to ROVar.
	 */
	ROVar& getVar(ROUn& p_un) const;

	/**
	 * This member function returns the referrence to the variable not related to uncertainty.
	 *
	 * @return  A referrence to ROVar.
	 */
	ROVar& getVar() const;


	/**
	 * This member function adds an uncertain "ROExpr" to the invoking object's decision rule.
	 *
	 * @param p_expr  A referrence to ROExpr.
	 */
	void addDR(ROExpr& p_expr);

	/**
	 * This member function adds an uncertain "ROUn" to the invoking object's decision rule.
	 *
	 * @param p_un  A referrence to ROUn.
	 */
	void addDR(ROUn& p_un);


	/**
	 * This member function copy the decision rule from another ROVarDR variable.
	 *
	 * @param p_varDR  A referrence to ROVarDR.
	 */
	void clone(ROVarDR& p_varDR);

private:
	boost::shared_ptr<ROVarDRImpl> m_sp_DRImp;
};



#endif
