//
//  rotempimpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 5/9/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//


#ifndef RobustOptimizationSolver_rotempimpl_h
#define RobustOptimizationSolver_rotempimpl_h

#include <functional>
#include <math.h>
#include "ROTypedefs.h"

#include "ROUnVarC.h"
#include "ROExpr.h"
#include "ROConstraintSet.h"
#include "roexprfunctions.h"

#define ROC_PI 3.14159265

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Template Part ------- Positive(), Negative(), Absolute(), Square(), Norm1(), Norm2(), NormInf()
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename VarType>
ROUnVarC ROAbsolute(const ROExpr& p_expr)
{
	ROExpr expr;
	VarType var_X;
	expr += var_X;

	ROConstraintSet constSet;
	constSet.add(var_X >= p_expr);
	constSet.add(var_X >= (-1) * p_expr);

	ROUnVarC unvarC;
	unvarC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
	unvarC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(constSet)));

	return unvarC;
}

// Only applies to uncertaint variables  ----- Need modification future
template<typename VarType>
ROUnVarC ROSquare(const ROExpr& p_expr)
{
	ROExpr expr;
	VarType var_X;
	expr += var_X;

	ROConstraintSet uncertaintySet;
	ROExprArray expr_array = ROExprArray(2);
	expr_array[0] += p_expr;
	expr_array[1] += (var_X - 1)/2;
	ROExpr expr_1 = (var_X + 1)/2;
	ROUnSOCConstraint unSOCConst(expr_1, expr_array);
	uncertaintySet.add(unSOCConst);


	ROUnVarC unvarC;
	unvarC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
	unvarC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

	return unvarC;
}


// Version 0.2
// A Polyhedral Approximation for SOCP
// Date: 2013-04-30
template<typename VarType>
ROUnVarC ROPolyApprox(const ROExpr& p_expr, int p_n, double p_beta)
{
	ROExpr expr;
	VarType var_u;
	expr += var_u;

	typedef ROArray<VarType> ROVarTypeArray;
	ROVarTypeArray arrayX((p_n+1)), arrayY((p_n+1));

	ROConstraintSet uncertaintySet;

	// Adding those constructed polyhedral approximation constraints

	uncertaintySet.add( arrayX[0] >= p_expr );
	uncertaintySet.add( arrayX[0] >= -p_expr );

	uncertaintySet.add( arrayY[0] >= (p_beta*var_u - 1/p_beta)/2 );
	uncertaintySet.add( arrayY[0] >= -(p_beta*var_u - 1/p_beta)/2 );

	for(int i = 1; i <= p_n; i++)
	{
		uncertaintySet.add( arrayX[i] == cos(ROC_PI / pow(2.0, i+1)) * arrayX[i-1] + sin(ROC_PI / pow(2.0, i+1)) * arrayY[i-1] );
		uncertaintySet.add( arrayY[i] >= sin(ROC_PI / pow(2.0, i+1)) * arrayX[i-1] - cos(ROC_PI / pow(2.0, i+1)) * arrayY[i-1] );
		uncertaintySet.add( arrayY[i] >= - sin(ROC_PI / pow(2.0, i+1)) * arrayX[i-1] + cos(ROC_PI / pow(2.0, i+1)) * arrayY[i-1] );
	}

	uncertaintySet.add(arrayX[p_n] <= (p_beta*var_u + 1/p_beta)/2 );
	uncertaintySet.add(arrayY[p_n] <= tan(ROC_PI / pow(2.0, p_n+1)) * arrayX[p_n] );

	ROUnVarC unvarC;
	unvarC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
	unvarC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(uncertaintySet)));

	return unvarC;

}



template<typename VarType, typename ProcessBinaryFunctor>
ROUnVarC ROPosNeg(const ROExpr& p_expr)
{
	ROExpr expr;
	VarType var_X;
	expr += var_X;

	ROConstraintSet constSet;

	ProcessBinaryFunctor functor;

	constSet.add(var_X >= functor(0,1) * p_expr);
	constSet.add(var_X >= 0);

	ROUnVarC unvarC;
	unvarC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr(expr)));
	unvarC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(constSet)));

	return unvarC;
}

// --------------------------------------------------------------------------------------------------------------------

template<typename ProcessBinaryFunctor, typename ExprType>
ROUnVarC ROUnVarCFunctor(const ROUnVarC& lhs, const ExprType& p_expr)
{
	ProcessBinaryFunctor functor;
	ROExpr expr = functor( *(lhs.getExpr().get()), p_expr);

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(lhs.getConstSet());
	
	return uvC;
}

template<typename ProcessBinaryFunctor, typename ExprType>
ROUnVarC ROUnVarCFunctor(const ExprType& p_expr, const ROUnVarC& rhs)
{
	ProcessBinaryFunctor functor;
	ROExpr expr = functor( p_expr, *(rhs.getExpr().get()) );

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));
	uvC.setConstSet(rhs.getConstSet());
	
	return uvC;
}

template<typename ProcessBinaryFunctor>
ROUnVarC ROUnVarCFunctor(const ROUnVarC& lhs, const ROUnVarC& rhs)
{
	ProcessBinaryFunctor functor;
	ROExpr expr = functor( *(lhs.getExpr().get()), *(rhs.getExpr().get()));

	ROUnVarC uvC;
	uvC.setExpr(boost::shared_ptr<ROExpr>(new ROExpr( expr )));

	ROConstraintSet constSet = *(lhs.getConstSet().get());
	constSet.add(*(rhs.getConstSet().get()));
	uvC.setConstSet(boost::shared_ptr<ROConstraintSet>(new ROConstraintSet(constSet)));
	
	return uvC;
}

// --------------------------------------------------------------------------------------------------------------------

template<typename ExprType, typename OperatorType>
ROConstraintSet ROUnVarCConst(const ExprType& lhs, const ROUnVarC& rhs, OperatorType constType)
{
	ROExpr& rhs_expr = *(rhs.getExpr().get());

	ROBaseConstraint roBaseConst = ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs-rhs_expr)), constType);

	ROConstraintSet roConstSet;
	roConstSet.set(roBaseConst);
	roConstSet.add(*(rhs.getConstSet().get()));

	return roConstSet;
}

template<typename ExprType, typename OperatorType>
ROConstraintSet ROUnVarCConst(const ROUnVarC& lhs, const ExprType& rhs, OperatorType constType)
{
	ROExpr& lhs_expr = *(lhs.getExpr().get());

	ROBaseConstraint roBaseConst = ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs_expr - rhs)), constType);

	ROConstraintSet roConstSet;
	roConstSet.set(roBaseConst);
	roConstSet.add(*(lhs.getConstSet().get()));

	return roConstSet;
}

template<typename OperatorType>
ROConstraintSet ROUnVarCConst(const ROUnVarC& lhs, const ROUnVarC& rhs, OperatorType constType)
{
	ROExpr& lhs_expr = *(lhs.getExpr().get());
	ROExpr& rhs_expr = *(rhs.getExpr().get());

	ROBaseConstraint roBaseConst = ROBaseConstraint(boost::shared_ptr<ROExpr>(new ROExpr(lhs_expr - rhs_expr)), constType);

	ROConstraintSet roConstSet;
	roConstSet.set(roBaseConst);
	roConstSet.add(*(lhs.getConstSet().get()));
	roConstSet.add(*(rhs.getConstSet().get()));

	return roConstSet;
}

// --------------------------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Template Part ------- Map Operations
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename ValueType>
ValueType updateValue();


template<typename MapType, typename ProcessBinaryFunctor>
void mapMerge(MapType& thisMap, MapType& pMap)
{
	typedef typename MapType::key_type MapIndexType;
	typedef typename MapType::mapped_type MapValueType;

	typename MapType::iterator iter = pMap.begin();
	ProcessBinaryFunctor functor;
	while(iter != pMap.end())
	{
		MapIndexType index = iter->first;

		typename MapType::iterator thisIter = thisMap.find(index);
		if(thisIter != thisMap.end())
		{
			thisIter->second = functor(thisIter->second, iter->second);
		}
		else
		{
      MapValueType value = updateValue<MapValueType>();

			thisMap.insert(std::make_pair(index, functor(value, iter->second)));
		}
		iter++;
	}
}

template<typename HighLevelIndexType, typename LowLevelIndexType>
HighLevelIndexType updateIndex(const LowLevelIndexType&);

template<typename HighLevelIndexType, typename LowLevelIndexType1, typename LowLevelIndexType2>
HighLevelIndexType updateIndex(const LowLevelIndexType1&, const LowLevelIndexType2&);


template<typename HighLevelValueType, typename LowLevelValueType>
HighLevelValueType updateValue(const LowLevelValueType&);

template<typename ThisMapType, typename ParamMapType, typename ProcessBinaryFunctor>
void mapMerge(ThisMapType& thisMap, ParamMapType& pMap)
{
	typename ParamMapType::iterator iter = pMap.begin();
	while(iter != pMap.end())
	{
		typedef typename ThisMapType::key_type ThisMapIndexType;
		typedef typename ParamMapType::key_type ParamMapIndexType;

		typedef typename ThisMapType::mapped_type ThisMapValueType;
		typedef typename ParamMapType::mapped_type ParamMapValueType;


		ThisMapIndexType index = updateIndex<ThisMapIndexType, ParamMapIndexType>(iter->first);
		
		ProcessBinaryFunctor functor;
		if(thisMap.find(index) != thisMap.end())
		{
			thisMap.find(index)->second = functor(thisMap.find(index)->second, iter->second);
		}
		else
		{
			ThisMapValueType value_temp = updateValue<ThisMapValueType>();

			ThisMapValueType value_temp2 = functor(value_temp, iter->second);

			//ThisMapValueType value = updateValue<ThisMapValueType, ParamMapValueType>(value_temp2);
			thisMap.insert(std::make_pair(index, value_temp2));
		}
		iter++;		
	}
}


template<typename MAP_TYPE, typename Functor>
void mapOperatedByNum(MAP_TYPE& map, RONum p_val)
{
	typename MAP_TYPE::iterator iter = map.begin();
	Functor functor;
	while(iter != map.end())
	{
		iter->second = functor(iter->second, p_val);
		iter++;
	}
}


template<class MAP_TYPE, class ELEMENT_TYPE, class FUNCTOR_TYPE>
void insertElement(MAP_TYPE& m_varsMap, const ELEMENT_TYPE& p_var)
{
	typedef typename MAP_TYPE::key_type INDEX_TYPE;
	typedef typename MAP_TYPE::mapped_type MAP_VALUE_TYPE;

	INDEX_TYPE index(p_var.getId());
	MAP_VALUE_TYPE val(1);

	FUNCTOR_TYPE functor;

	typename MAP_TYPE::iterator iter = m_varsMap.find(index);
	if(iter == m_varsMap.end())
	{
		m_varsMap.insert(std::make_pair(index, functor(0, val)));
	}
	else
	{
		iter->second = functor(iter->second, val);
	}
}

template<typename ThisMapType, typename ParamMapType>
void mapExpect(ThisMapType& thisMap, ParamMapType& paramMap)
{
	typename ParamMapType::iterator iter = paramMap.begin();

	while(iter != paramMap.end())
	{
		thisMap.insert(std::make_pair(iter->first, std::make_pair(iter->second,1)));
		iter++;
	}
}


			// TEMPLATE STRUCT plus
template<class PAIR_TYPE, class NUM_TYPE>
struct pairMultipliesNum
		: public std::binary_function<PAIR_TYPE, PAIR_TYPE, NUM_TYPE>
{	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const NUM_TYPE& _Right) const
	{	// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first * _Right, _Left.second);
		return tempType;
	}
};

		// TEMPLATE STRUCT plus
template<class PAIR_TYPE, class NUM_TYPE>
struct pairDividesNum
		: public std::binary_function<PAIR_TYPE, NUM_TYPE, PAIR_TYPE>
{	
	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const NUM_TYPE& _Right) const
	{	
		if(_Right == 0)
		{
			ROExceptionDivideZero exp;
			throw exp;
		}

		// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first / _Right, _Left.second);
		return tempType;
	}
};

template<class PAIR_TYPE>
struct pairPlus
		: public std::binary_function<PAIR_TYPE, PAIR_TYPE, PAIR_TYPE>
{	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const PAIR_TYPE& _Right) const
	{	// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first + _Right.first, _Right.second);
		return tempType;
	}
};


template<class PAIR_TYPE, class NUM_TYPE>
struct pairPlusNum
		: public std::binary_function<PAIR_TYPE, NUM_TYPE, PAIR_TYPE>
{	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const NUM_TYPE& _Num) const
	{	// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first + _Num, _Left.second);
		return tempType;
	}
};

template<class PAIR_TYPE, class NUM_TYPE>
struct pairMinusNum
		: public std::binary_function<PAIR_TYPE, NUM_TYPE, PAIR_TYPE>
{	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const NUM_TYPE& _Num) const
	{	// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first - _Num, _Left.second);
		return tempType;
	}
};


template<class PAIR_TYPE>
struct pairMinus
		: public std::binary_function<PAIR_TYPE, PAIR_TYPE, PAIR_TYPE>
{	// functor for operator+
	PAIR_TYPE operator()(const PAIR_TYPE& _Left, const PAIR_TYPE& _Right) const
	{	// apply operator+ to operands
		PAIR_TYPE tempType(_Left.first - _Right.first, _Right.second);
		return tempType;
	}
};



#endif
