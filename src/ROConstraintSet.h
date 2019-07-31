//
//  ROConstraintSet.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 06/10/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROConstraintSet_h
#define RobustOptimizationSolver_ROConstraintSet_h

#include "ROTypedefs.h"
#include "ROBaseConstraint.h"
#include "ROUnLinConstraint.h"
#include "ROUnSOCConstraint.h"

/**
 * An instance of this class is a set of constraints in a model.
 *
 * Date: 17-Oct-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROConstraintSet
{
public:
    
	/**
	 * The default constructor which creates an empty object. It must be initialized before use.
     *
	 */
	ROConstraintSet();

	/**
	 * This is the copy constructor.
	 *
	 * @param p_constSet  An referrence of ROConstraintSet.
	 */
	ROConstraintSet(const ROConstraintSet& p_constSet);

	/**
	 * This constructor creates an ROConstraintSet from a single base constraint.
	 * 
	 * @param p_baseConst An referrence of ROBaseConstraint.
	 */
	ROConstraintSet(const ROBaseConstraint& p_baseConst);

	/**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray and ROUnSOCConstraintArray.
	 *
	 * @param p_unConstArray   A shared_pointer to a ROUnLinConstraintArray object.
	 * @param p_unNormConstArray   A shared_pointer to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
					const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray and ROUnSOCConstraintArray.
	 *
	 * @param p_unConstArray   Referrence to a ROUnLinConstraintArray object.
	 * @param p_unNormConstArray   Referrence to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray,
					const ROUnSOCConstraintArray& p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_unConst   A shared_pointer to a ROUnLinConstraint object.
	 * @param p_unNormConstArray   A shared_pointer to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst,
					const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint and ROUnSOCConstraintArray.
	 *
	 * @param p_unConst   Referrence to a ROUnLinConstraint object.
	 * @param p_unNormConstArray   Referrence to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const ROUnLinConstraint& p_unConst,
					const ROUnSOCConstraintArray& p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray and ROUnSOCConstraint.
	 *
	 * @param p_unConstArray   A shared_pointer to a ROUnLinConstraintArray object.
	 * @param p_unNormConst   A shared_pointer to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
					const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray and ROUnSOCConstraint.
	 *
	 * @param p_unConstArray   Referrence to a ROUnLinConstraintArray object.
	 * @param p_unNormConst   Referrence to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray,
					const ROUnSOCConstraint& p_unNormConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint and ROUnSOCConstraint.
	 *
	 * @param p_unConst   A shared_pointer to a ROUnLinConstraint object.
	 * @param p_unNormConst   A shared_pointer to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst,
					const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint and ROUnSOCConstraint.
	 *
	 * @param p_unConst   Referrence to a p_unConst object.
	 * @param p_unNormConst   Referrence to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const ROUnLinConstraint& p_unConst,
					const ROUnSOCConstraint& p_unNormConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray.
	 *
	 * @param p_unConstArray   A shared_pointer to a ROUnLinConstraintArray object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraintArray.
	 *
	 * @param p_unConstArray   Referrence to a ROUnLinConstraintArray object.
	 */
	ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint.
	 *
	 * @param p_unConst   A shared_pointer to a ROUnLinConstraint object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnLinConstraint.
	 *
	 * @param p_unConst   Referrence to a ROUnLinConstraint object.
	 */
	ROConstraintSet(const ROUnLinConstraint& p_unConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnSOCConstraintArray.
	 *
	 * @param p_unNormConstArray   A shared_pointer to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnSOCConstraintArray.
	 *
	 * @param p_unNormConstArray   Referrence to a ROUnSOCConstraintArray object.
	 */
	ROConstraintSet(const ROUnSOCConstraintArray& p_unNormConstArray);

    /**
	 * This constructor creates an ROConstraintSet from ROUnSOCConstraint.
	 *
	 * @param p_unNormConst   A shared_pointer to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst);

    /**
	 * This constructor creates an ROConstraintSet from ROUnSOCConstraint.
	 *
	 * @param p_unNormConst   Referrence to a ROUnSOCConstraint object.
	 */
	ROConstraintSet(const ROUnSOCConstraint& p_unNormConst);

	/**
	 * The assignment operator "=".
	 *
	 * @param p_const  An referrence of ROConstraintSet.
	 * @return  A reference of current invoking object.
	 */
	ROConstraintSet& operator = (const ROConstraintSet& p_const);

	/**
	 * This member function returns a shared pointer of ROBaseConstraint from invoking object.
	 *
	 * @return  A shared pointer to ROBaseConstraint of invoking object.
	 */
	boost::shared_ptr<ROBaseConstraint> getROBaseConst() const;

	/**
	 * This member function returns a shared pointer of ROBaseConstraintArray from invoking object.
	 *
	 * @return  A shared pointer to ROBaseConstraintArray of invoking object.
	 */
	boost::shared_ptr<ROBaseConstraintArray> getBaseConstArray() const;

	/**
	 * This member function returns a shared pointer of ROUnLinConstraintArray from invoking object.
	 *
	 * @return  A shared pointer to ROUnLinConstraintArray of invoking object.
	 */
	boost::shared_ptr<ROUnLinConstraintArray> getUnConstArray() const;

	/**
	 * This member function returns a shared pointer of ROUnSOCConstraintArray from invoking object.
	 *
	 * @return  A shared pointer to ROUnSOCConstraintArray of invoking object.
	 */
	boost::shared_ptr<ROUnSOCConstraintArray> getUnNormArray() const;

	/**
	 * This member function add the primary base constraint.
	 *
	 * @param p_baseConst  A referrence to ROBaseConstraint instance.
	 */
	void set(const ROBaseConstraint& p_baseConst);

	/**
	 * This member function add the elementary base constraint.
	 *
	 * @param p_baseConst  A referrence to ROBaseConstraint instance.
	 */
	void add(const ROBaseConstraint& p_baseConst);

	/**
	 * This member function add the base uncertaint constraint.
	 *
	 * @param p_unConst  A referrence to ROUnLinConstraint instance.
	 */
	void add(const ROUnLinConstraint& p_unConst);

	/**
	 * This member function add the SOC uncertaint constraint.
	 *
	 * @param p_socConst  A referrence to ROUnSOCConstraint instance.
	 */
	void add(const ROUnSOCConstraint& p_socConst);

	/**
	 * This member function add a set of constraints.
	 *
	 * @param p_constSet  A referrence to ROConstraintSet instance.
	 */
	void add(const ROConstraintSet& p_constSet);

private:
	boost::shared_ptr<ROBaseConstraint> m_roBaseConst;

	boost::shared_ptr<ROBaseConstraintArray> m_baseConstArray;

    boost::shared_ptr<ROUnLinConstraintArray> m_unConstArray;

    boost::shared_ptr<ROUnSOCConstraintArray> m_unNormConstArray;
};


#endif