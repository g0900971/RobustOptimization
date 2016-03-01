//
//  ROModel.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 27/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROModel_h
#define RobustOptimizationSolver_ROModel_h

#include "ROTypedefs.h"
#include "ROConstraintSet.h"

//////////////////////////
// Test Usage
#ifdef _USE_CPLEX_
class CPLEX;
typedef CPLEX TYPE;
#endif

/////////////////////////
class ROConstraint;
class ROBaseConstraint;
class ROObjective;
class ROExprImpl;
class ROConstraintSet;

template<class T>
class Factory;

template<class T>
class Model;

template<class T>
class Objective;

template<class T>
class Constraint;

template<class T>
class Var;

class LPVarArray;

//typedef std::vector<boost::shared_ptr<Var<CPLEX> > > LPVarArray;

template<class T>
class Expr;

/*
typedef boost::unordered_map< ROUnIndex, boost::shared_ptr<ROExpr> > ROUVSubMap;
typedef boost::unordered_map< ROUnIndex, boost::shared_ptr<ROExpr> >::iterator ROUVSubMapIter;
*/

typedef boost::unordered_map< ROUnIndex, boost::shared_ptr<ROExpr>, StrongTypeHash<ROUnIndex> > ROUVSubMap;
typedef boost::unordered_map< ROUnIndex, boost::shared_ptr<ROExpr>, StrongTypeHash<ROUnIndex> >::iterator ROUVSubMapIter;


/**
 * An instance of this class represents a model. A model consists of constraints, constrained variables, objectives, and possibly other
 * modeling objects, that represents a robust optimization problem.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROModel
{
public:
	/**
	 * The default constructor which creates an empty model. It must be initialized before use.
	 */
    ROModel();

    /**
     * This member function returns a pointer to the underlying LP solver implementation object.
     *
     * @return A pointer of LP<TYPE> model.
     */
	boost::shared_ptr<Model<TYPE> > getModel() const;

	/**
	 * This member function returns a pointer to the add-in ROObjective.
	 *
	 * @return A pointer to the ROObjective of invoking model instance.
	 */
    boost::shared_ptr<ROObjective> getObjective() const;

    /**
     * This member function adds "ROBaseConstraint" object (a base constraint) to the invoking model.
     *
     * @param p_const  A "ROBaseConstraint" without uncertainty set attached.
     */
	void add(const ROBaseConstraint & p_const);

	/**
	 * This member function adds "ROBaseConstraintArray" object (array of base constraints) to the invoking model.
	 *
	 * @param p_constArray  An array of "ROBaseConstraint" without uncertainty set attached.
	 */
	void add(ROBaseConstraintArray & p_constArray);

	/**
	 * This member function adds "ROConstraintArray" object (array of ro-constraints) to the invoking model.
	 *
	 * @param p_constArray  An array of "ROConstraint" and possibly set of uncertain constraints.
	 */
	void add(ROConstraintArray & p_constArray);

	/**
	 * This member function adds "ROConstraint" object to the invoking model.
	 *
	 * @param p_const  A "ROConstraint" with possibly set of uncertaint constraints.
	 */
	void add(const ROConstraint & p_const);

	/**
	 * This member function adds "ROConstraintSet" object to the invoking model.
	 *
	 * @param p_constSet  A  set of  constraints.
	 */
	void add(const ROConstraintSet & p_constSet);

	/**
	 * This member function adds "ROObjective" object to the invoking model.
	 *
	 * @param p_obj  A "ROObjective" which specifies the objective function.
	 */
    void add(const ROObjective & p_obj);

    /**
     * This member function solves the current model.
     */
	void solve();

	/**
	 * This member function returns the objective value of invoking model if it finds a solution.
	 *
	 * @return Objective value.
	 */
	RONum getObjValue();

	/**
	 * This member function returns the status of the model after call solve().
	 *
	 * @see solve().
	 * @return status after model solving.
	 */
	std::string getStatus();

	/**
	 * This member function returns the solution of a specified variable.
	 *
	 * @param A specified ROVar.
	 * @return The solved solution of specified variable.
	 */
	RONum getVarValue(const ROVar& p_var);

	/**
	 * This member function would print the LP formulation of invoking model in default path.
	 */
	void exportModel();

	/**
	 * This member function would print the LP formulation of invoking model in specified directory.
	 *
	 * @param std::string directory path.
	 */
	void exportModel(std::string& p_dirPath);

	~ROModel();
    
private:
	boost::shared_ptr<Factory<TYPE> > m_lpFactory;

	boost::shared_ptr<Model<TYPE> > m_lpModel;

	boost::shared_ptr<LPVarArray> m_p_vec_lpVar;

	boost::shared_ptr<ROObjective> m_obj;  
	std::list< boost::shared_ptr<ROConstraint> > m_listConst;

	std::list< boost::shared_ptr<ROBaseConstraint> > m_baseConst;
	void transform(const ROConstraint & p_const);
	void transformEq(const ROConstraint & p_const);
	void transformLeq(const ROConstraint & p_const);
	void transformExpect(const ROConstraint & p_const);

	void decompose(const ROConstraint & p_const, boost::shared_ptr<ROExpr> p_vExpr, ROUVSubMap & p_uvSubMap);
	void decomposeExpect(const ROConstraint & p_const, boost::shared_ptr<ROExpr> p_expr0, boost::shared_ptr<ROExpr> p_expr1,
		boost::shared_ptr<ROUnLinConstraintArray> unConstArray, boost::shared_ptr<ROUnLinConstraintArray> unExConstArray);

	void lpSolve();
};


#endif
