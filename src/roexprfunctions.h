//
//  roexprfunctions.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 27/8/12.
//  Modified by Meilin Zhang on 04/10/12.
//  Modified by Meilin Zhang on 24/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_roexprfunctions_h
#define RobustOptimizationSolver_roexprfunctions_h

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Operators Overload : + - / * == <= >=
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ROTypedefs.h"
#include "ROExpr.h"

class ROVar;
class ROIntVar;
class ROBinVar;
class ROUn;
class ROUnVarC;
class ROExpr;
class ROObjective;
class ROBaseConstraint;
class ROConstraintSet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Objective Function

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_expr  A referrence to an ROExpr instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROExpr& p_expr);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_expr  A referrence to an ROVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROVar& p_expr);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_expr  A referrence to an ROIntVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROIntVar& p_expr);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_expr  A referrence to an ROBinVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROBinVar& p_expr);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_expr  A referrence to an ROExpr instance.
 * @param p_constSet  A referrence to an ROConstraintSet instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROExpr& p_expr, const ROConstraintSet& p_constSet);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_unVarC  A referrence to an ROUnVarC instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROUnVarC& p_unVarC);

/**
 * Global Function.
 * This function defines a minimization objective in a model.
 *
 * @param p_unVarC  A referrence to an ROUnVarC instance.
 * @param p_constSet  A referrence to an ROConstraintSet instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMinimize(const ROUnVarC& p_unVarC, const ROConstraintSet& p_constSet);

// --------------------------------------------------------------------------------------------------------------------

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_expr  A referrence to an ROExpr instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROExpr& p_expr);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_expr  A referrence to an ROVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROVar& p_expr);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_expr  A referrence to an ROIntVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROIntVar& p_expr);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_expr  A referrence to an ROBinVar instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROBinVar& p_expr);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_expr  A referrence to an ROExpr instance.
 * @param p_constSet  A referrence to an ROConstraintSet instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROExpr& p_expr, const ROConstraintSet& p_constSet);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_unVarC  A referrence to an ROUnVarC instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROUnVarC& p_unVarC);

/**
 * Global Function.
 * This function defines a maximization objective in a model.
 *
 * @param p_unVarC  A referrence to an ROUnVarC instance.
 * @param p_constSet  A referrence to an ROConstraintSet instance.
 * @return  An object of ROObjective.
 */
ROObjective ROMaximize(const ROUnVarC& p_unVarC, const ROConstraintSet& p_constSet);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Functional Operations related to "ROUnVarC"
//

// ----------------------------------------  Unary operators :   + - / *  ---------------------------------------------
/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& p_var);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROIntVar& p_var);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROBinVar& p_var);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& p_un);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& p_expr);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& p_unvarC);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& p_varDR);

// ----------------------------------  Binaray operators among ROVar ROIntVar ROBinVar  -------------------------------

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROIntVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROIntVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROIntVar& lhs, const ROVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROBinVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROBinVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROBinVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROBinVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROBinVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROBinVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (const ROIntVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator - (const ROIntVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROIntVar& lhs, const ROBinVar& rhs);


// ---------------------------------------  Binaray operators :   + - / *  --------------------------------------------

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (const ROUnVarC& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator / (const ROUnVarC& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (const ROUnVarC& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator + (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator + (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator - (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator - (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator * (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROUnVarC operator * (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROUnVarC operator * (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROUnVarC operator * (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROUnVarC operator * (const ROUnVarC& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROExpr& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROExpr& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROUnVarC& rhs);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Functional Operations related to "ROVarDR"
//
//     + - / * 

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVarDR& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVarDR& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator / (const ROVarDR& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVarDR& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVarDR& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVarDR& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator + (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01 
 */
ROExpr operator + (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01 
 */
ROExpr operator + (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01 
 */
ROExpr operator + (const ROVarDR& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator - (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator - (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator - (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator - (const ROVarDR& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVarDR& lhs, const ROVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator * (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator * (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator * (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date : 2013-06-01
 */
ROExpr operator * (const ROVarDR& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVarDR& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROUnVarC& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator + (const ROVarDR& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROUnVarC& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROUnVarC operator - (const ROVarDR& lhs, const ROUnVarC& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVarDR& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVarDR& lhs, const ROVarDR& rhs);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to  + - / *

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator + (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROExpr operator + (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROExpr operator + (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01 
 */
ROExpr operator + (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01  
 */
ROExpr operator - (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01  
 */
ROExpr operator - (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01  
 */
ROExpr operator - (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01  
 */
ROExpr operator - (const ROBinVar& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator * (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (RONum lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator / (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator / (const ROIntVar& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 * Date: 2013-06-01
 */
ROExpr operator / (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator / (const ROUn& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator / (const ROExpr& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01 
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01 
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01 
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROBinVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01 
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROBinVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (RONum lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (RONum lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROBinVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROBinVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROIntVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROIntVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROBinVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROUn& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROBinVar& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Date: 2013-06-01   
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROUn& lhs, const ROBinVar& rhs);



/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator + (const ROExpr& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator - (const ROExpr& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVar& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROIntVar& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROBinVar& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROBinVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01  
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROBinVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROUn& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator.
 */
ROExpr operator * (const ROExpr& lhs, const ROExpr& rhs);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Functional Operations related to "expect" "positive" "negative" "absolute"
//

/**
 * Global Function.
 * Return the summation of an array of numbers.
 */
RONum ROSum(const RONumArray& p_numArray);

/**
 * Global Function.
 * Return the summation of an array of ROExpr objects.
 */
ROExpr ROSum(const ROExprArray& p_exprArray);

/**
 * Global Function.
 * Return the summation of an array of ROVar objects.
 */
ROExpr ROSum(const ROVarArray& p_varArray);

/**
 * Global Function.
 * Return the summation of an array of ROUn objects.
 */
ROExpr ROSum(const ROUnArray& p_unArray);

/**
 * Global Function.
 * Return the expected expression of an ROUn instance.
 */
ROExpr ROExpect(const ROUn& p_un);

/**
 * Global Function.
 * Return the expected expression of an ROExpr instance.
 */
ROExpr ROExpect(const ROExpr& p_expr);

/**
 * Global Function.
 * Return the expected expression of an ROVarDR instance.
 */
ROExpr ROExpect(const ROVarDR& p_varDR);

// --- for objective use ---
/**
 * Global Function.
 * Return the expected ROUnVarC expression of an ROUnVarC instance.
 */
ROUnVarC ROExpect(const ROUnVarC& p_unVarC);
// --- End ---


/**
 * Global Function.
 * Return the positive part of an ROUn instance.
 */
ROUnVarC ROPos(const ROUn& p_un);

/**
 * Global Function.
 * Return the positive part of an ROVar instance.
 */
ROUnVarC ROPos(const ROVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the positive part of an ROIntVar instance.
 */
ROUnVarC ROPos(const ROIntVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the positive part of an ROBinVar instance.
 */
ROUnVarC ROPos(const ROBinVar& p_var);

/**
 * Global Function.
 * Return the positive part of an ROExpr instance.
 */
ROUnVarC ROPos(const ROExpr& p_expr);

/**
 * Global Function.
 * Return the positive part of an ROVarDR instance.
 */
ROUnVarC ROPos(const ROVarDR& p_varDR);

/**
 * Global Function.
 * Return the positive part of an ROUnVarC instance.
 */
ROUnVarC ROPos(const ROUnVarC& p_unC);


/**
 * Global Function.
 * Return the negative part of an ROUn instance.
 */
ROUnVarC RONeg(const ROUn& p_un);

/**
 * Global Function.
 * Return the negative part of an ROVar instance.
 */
ROUnVarC RONeg(const ROVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the negative part of an ROIntVar instance.
 */
ROUnVarC RONeg(const ROIntVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the negative part of an ROBinVar instance.
 */
ROUnVarC RONeg(const ROBinVar& p_var);

/**
 * Global Function.
 * Return the negative part of an ROExpr instance.
 */
ROUnVarC RONeg(const ROExpr& p_expr);

/**
 * Global Function.
 * Return the negative part of an ROVarDR instance.
 */
ROUnVarC RONeg(const ROVarDR& p_varDR);

/**
 * Global Function.
 * Return the negative part of an ROUnVarC instance.
 */
ROUnVarC RONeg(const ROUnVarC& p_unC);


/**
 * Global Function.
 * Return the absolute part of an ROUn instance.
 */
ROUnVarC ROAbs(const ROUn& p_un);

/**
 * Global Function.
 * Return the absolute part of an ROVar instance.
 */
ROUnVarC ROAbs(const ROVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the absolute part of an ROIntVar instance.
 */
ROUnVarC ROAbs(const ROIntVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the absolute part of an ROBinVar instance.
 */
ROUnVarC ROAbs(const ROBinVar& p_var);

/**
 * Global Function.
 * Return the absolute part of an ROExpr instance.
 */
ROUnVarC ROAbs(const ROExpr& p_expr);

/**
 * Global Function.
 * Return the absolute part of an ROVarDR instance.
 */
ROUnVarC ROAbs(const ROVarDR& p_varDR);

/**
 * Global Function.
 * Return the absolute part of an ROUnVarC instance.
 */
ROUnVarC ROAbs(const ROUnVarC& p_unC);


/**
 * Global Function.
 * Return the square expression of an ROUn instance.
 */
ROUnVarC ROSq(const ROUn& p_un);

/**
 * Global Function.
 * Return the square expression of an ROVar instance.
 */
ROUnVarC ROSq(const ROVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the square expression of an ROIntVar instance.
 */
ROUnVarC ROSq(const ROIntVar& p_var);

/**
 * Global Function.
 * Date: 2013-06-01
 * Return the square expression of an ROBinVar instance.
 */
ROUnVarC ROSq(const ROBinVar& p_var);

/**
 * Global Function.
 * Return the square expression of an ROExpr instance.
 */
ROUnVarC ROSq(const ROExpr& p_expr);

/**
 * Global Function.
 * Return the square expression of an ROVarDR instance.
 */
ROUnVarC ROSq(const ROVarDR& p_varDR);

/**
 * Global Function.
 * Return the square expression of an ROUnVarC instance.
 */
ROUnVarC ROSq(const ROUnVarC& p_unC);


/**
 * Global Function Version 0.2
 * Date: 2013-04-30
 * A Polyhedral Approximation for SOCP constraints
 * Return the square expression of an ROUn instance.
 */
ROUnVarC ROSq(const ROUn& p_un, int p_n, double p_beta = 1);

/**
 * Global Function Version 0.2
 * Date: 2013-04-30
 * A Polyhedral Approximation for SOCP constraints
 * Return the square expression of an ROVar instance.
 */
ROUnVarC ROSq(const ROVar& p_var, int p_n, double p_beta = 1);

/**
 * Global Function Version 0.2
 * Date: 2013-06-01
 * A Polyhedral Approximation for SOCP constraints
 * Return the square expression of an ROIntVar instance.
 */
ROUnVarC ROSq(const ROIntVar& p_var, int p_n, double p_beta = 1);

/**
 * Global Function Version 0.2
 * Date: 2013-06-01
 * A Polyhedral Approximation for SOCP constraints
 * Return the square expression of an ROBinVar instance.
 */
ROUnVarC ROSq(const ROBinVar& p_var, int p_n, double p_beta = 1);

/**
 * Global Function Version 0.2
 * Date: 2013-04-30
 * A Polyhedral Approximation for SOCP constraints
 * Return the square expression of an ROExpr instance.
 */
ROUnVarC ROSq(const ROExpr& p_expr, int p_n, double p_beta = 1);


/**
 * Global Function.
 * Return the norm infinity of a ROExprArray instance.
 */
ROUnVarC RONormInf(const ROExprArray& p_exprArray);

/**
 * Global Function.
 * Return the norm infinity of a ROVarArray instance.
 */
ROUnVarC RONormInf(const ROVarArray& p_varArray);

/**
 * Global Function.
 * Return the norm infinity of a ROUnArray instance.
 */
ROUnVarC RONormInf(const ROUnArray& p_unArray);


/**
 * Global Function.
 * Return the norm 1 of a ROExprArray instance.
 */
ROUnVarC RONorm1(const ROExprArray& p_exprArray);

/**
 * Global Function.
 * Return the norm 1 of a ROVarArray instance.
 */
ROUnVarC RONorm1(const ROVarArray& p_varArray);

/**
 * Global Function.
 * Return the norm 1 of a ROUnArray instance.
 */
ROUnVarC RONorm1(const ROUnArray& p_unArray);

/**
 * Global Function.
 * Return the norm 2 of a ROExprArray instance.
 */
ROUnVarC RONorm2(const ROExprArray& p_exprArray);

/**
 * Global Function.
 * Return the norm 2 of a ROVarArray instance.
 */
ROUnVarC RONorm2(const ROVarArray& p_varArray);

/**
 * Global Function.
 * Return the norm 2 of a ROUnArray instance.
 */
ROUnVarC RONorm2(const ROUnArray& p_unArray);

/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*1
 */
ROConstraintSet RORotateSOC(const ROExprArray& p_exprArray, const ROExpr& p_expr);

/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*V
 */
ROConstraintSet RORotateSOC(const ROExprArray& p_exprArray, const ROExpr& p_expr1, const ROExpr& p_expr2);


/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*1
 */
ROConstraintSet RORotateSOC(const ROVarArray& p_varArray, const ROExpr& p_expr);

/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*V
 */
ROConstraintSet RORotateSOC(const ROVarArray& p_varArray, const ROExpr& p_expr1, const ROExpr& p_expr2);


/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*1
 */
ROConstraintSet RORotateSOC(const ROUnArray& p_unArray, const ROExpr& p_expr);

/**
 * Global Function.
 * Return the rotated second order cone constraint in form : ||..||^2 <= U*V
 */
ROConstraintSet RORotateSOC(const ROUnArray& p_unArray, const ROExpr& p_expr1, const ROExpr& p_expr2);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Constraints Operations Related to "ROUnVarC"
// 

// Related to "ROUnVarC" "<=" "<=" "=="

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROExpr& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROUnVarC& rhs);



/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROBinVar& rhs);



/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROExpr& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROUnVarC& rhs);



/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (RONum lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUn& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROIntVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROBinVar& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROExpr& lhs, const ROUnVarC& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROUnVarC& rhs);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Constraints Operations Related to "ROVarDR"
// 
//   "<=" "<=" "=="

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROUnVarC& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROConstraintSet operator <= (const ROVarDR& lhs, const ROUnVarC& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVarDR& lhs, const ROVarDR& rhs);



/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROUnVarC& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROConstraintSet operator == (const ROVarDR& lhs, const ROUnVarC& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVarDR& lhs, const ROVarDR& rhs);



/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROUn& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROUn& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator >= (const ROIntVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator >= (const ROBinVar& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROUnVarC& lhs, const ROVarDR& rhs);

/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROConstraintSet operator >= (const ROVarDR& lhs, const ROUnVarC& rhs);


/**
 * Global Function.
 * Overloaded C++ operator, constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVarDR& lhs, const ROVarDR& rhs);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// "<=" "<=" "=="


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROUn& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROUn& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVar& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROBinVar& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (RONum lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROUn& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROBinVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS <= RHS"
 */
ROBaseConstraint operator <= (const ROExpr& lhs, const ROExpr& rhs);

// " >= " uncertain set constraint

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROUn& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROUn& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVar& lhs, const ROVar& rhs);


/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROBinVar& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (RONum lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROUn& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROBinVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS >= RHS"
 */
ROBaseConstraint operator >= (const ROExpr& lhs, const ROExpr& rhs);



// " == " uncertain set constraint

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROUn& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROUn& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVar& lhs, RONum rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVar& lhs, const ROVar& rhs);


/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROIntVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROIntVar& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROBinVar& lhs, RONum rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROBinVar& lhs, const ROBinVar& rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (RONum lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, RONum rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROUn& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROUn& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROVar& rhs);

/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROIntVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROIntVar& lhs, const ROExpr& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROBinVar& rhs);

/**
 * Global Function.
 * Date: 2013-06-01
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROBinVar& lhs, const ROExpr& rhs);


/**
 * Global Function.
 * Overloaded C++ operator constrains its two arguments which satisfy "LHS == RHS"
 */
ROBaseConstraint operator == (const ROExpr& lhs, const ROExpr& rhs);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
