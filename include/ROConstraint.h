//
//  ROConstraint.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROConstraint_h
#define RobustOptimizationSolver_ROConstraint_h

#include "ROTypedefs.h"
#include "ROBaseConstraint.h"
#include "ROUnLinConstraint.h"
#include "ROUnSOCConstraint.h"

/**
 * An instance of this class is a constraint in a model. A constraint could be either a ROBaseConstraint or a 
 *		ROConstraint with uncertainty set.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROConstraint
{
public:

	/**
	 * The default constructor which creates an empty object. It must be initialized before use.
	 */
	ROConstraint();

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROConstraintSet.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_uncertaintySet  A object of ROConstraintSet which specifies the set of uncertainty constraints.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, const ROConstraintSet& p_uncertaintySet);

	/**
	 * This constructor creates an ROConstraint from ROConstraintSet and ROConstraintSet.
	 *
	 * @param p_varConstSet  A object of ROConstraintSet which specifies a set of base constraints.
	 * @param p_uncertaintySet  A object of ROConstraintSet which specifies the set of uncertainty constraints.
	 */
	ROConstraint(const ROConstraintSet& p_varConstSet, const ROConstraintSet& p_uncertaintySet);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraintArray and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A shared_ptr of ROUnLinConstraintArray which specifies the base set of uncertainty constraints.
	 * @param p_unNormConstArray  A shared_ptr of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
                 const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraintArray and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A object of ROUnLinConstraintArray which specifies the base set of uncertainty constraints.
	 * @param p_unNormConstArray  A object of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraintArray& p_unConstArray,
                 const ROUnSOCConstraintArray& p_unNormConstArray);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A shared_ptr of ROUnLinConstraint which specifies an base uncertainty constraint.
	 * @param p_unNormConstArray  A shared_ptr of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraint> p_unConst,
                 const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A object of ROUnLinConstraint which specifies an base uncertainty constraint.
	 * @param p_unNormConstArray  A object of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraint& p_unConst,
                 const ROUnSOCConstraintArray& p_unNormConstArray);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraintArray and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A shared_ptr of ROUnLinConstraintArray which specifies the base set of uncertainty constraints.
	 * @param p_unNormConst  A shared_ptr of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
                 const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraintArray and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A object of ROUnLinConstraintArray which specifies the base set of uncertainty constraints.
	 * @param p_unNormConst  A object of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraintArray& p_unConstArray,
                 const ROUnSOCConstraint& p_unNormConst);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraint and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A shared_ptr of ROUnLinConstraint which specifies an base uncertainty constraint.
	 * @param p_unNormConst  A shared_ptr of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraint> p_unConst,
                 const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, ROUnLinConstraint and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A object of ROUnLinConstraint which specifies an base uncertainty constraint.
	 * @param p_unNormConst  A object of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraint& p_unConst,
                 const ROUnSOCConstraint& p_unNormConst);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnLinConstraintArray.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A shared_ptr of ROUnLinConstraintArray which specifies the set of base uncertainty constraints.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnLinConstraintArray.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConstArray  A object of ROUnLinConstraintArray which specifies the set of base uncertainty constraints.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraintArray& p_unConstArray);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnLinConstraint.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A shared_ptr of ROUnLinConstraint which specifies an base uncertainty constraint.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnLinConstraint> p_unConst);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnLinConstraint.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unConst  A object of ROUnLinConstraint which specifies an base uncertainty constraint.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnLinConstraint& p_unConst);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unNormConstArray  A shared_ptr of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unNormConstArray  A object of ROUnSOCConstraintArray which specifies the norm set of uncertainty constraints.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnSOCConstraintArray& p_unNormConstArray);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unNormConst  A shared_ptr of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
				 const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint and ROUnSOCConstraint.
	 *
	 * @param p_varConst  A object of ROBaseConstraint which specifies the primary variable constraint.
	 * @param p_unNormConst  A object of ROUnSOCConstraint which specifies a norm uncertainty constraint.
	 */
	ROConstraint(const ROBaseConstraint& p_varConst, 
				 const ROUnSOCConstraint& p_unNormConst);


	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, no uncertainty attached.
	 *
	 * @param p_const  A shared_ptr of ROBaseConstraint which specifies the primary variable constraint.
	 */
	ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_const);

	/**
	 * This constructor creates an ROConstraint from ROBaseConstraint, no uncertainty attached.
	 *
	 * @param p_const  A object of ROBaseConstraint which specifies the primary variable constraint.
	 */
	ROConstraint(const ROBaseConstraint& p_const);


	/**
	 * The copy constructor.
	 *
	 * @param  An object of ROConstraint.
	 */
	ROConstraint(const ROConstraint& p_const);

	/**
	 * The assignment operator "="
	 *
	 * @param p_const  An object of ROConstraint.
	 * @return  A reference of current invokign object.
	 */
	ROConstraint& operator = (const ROConstraint& p_const);


	/**
	 * This member function returns the primary variable constraint.
	 *
	 * @return  A shared_ptr of the primary variable constraint, ROBaseConstraint.
	 */
	boost::shared_ptr<ROBaseConstraint> getVarConst() const; 

	/**
	 * This member function returns the set of base uncertainty constraints.
	 *
	 * @return  A shared_ptr of ROUnLinConstraintArray.
	 */
	boost::shared_ptr<ROUnLinConstraintArray> getUnConstArray() const;

	/**
	 * This member function returns the set of norm uncertainty constraints.
	 *
	 * @return  A shared_ptr of ROUnSOCConstraintArray.
	 */
	boost::shared_ptr<ROUnSOCConstraintArray> getUnNormArray() const;

	/**
	 * This member function returns the set of base constraints.
	 *
	 * @return  A shared_ptr of ROBaseConstraintArray.
	 */
	boost::shared_ptr<ROBaseConstraintArray> getBaseConstArray() const;

private:
    boost::shared_ptr<ROBaseConstraint> m_varConst;

    boost::shared_ptr<ROUnLinConstraintArray> m_unConstArray;

    boost::shared_ptr<ROUnSOCConstraintArray> m_unNormConstArray;

	boost::shared_ptr<ROBaseConstraintArray> m_baseConstSet;

};


#endif
