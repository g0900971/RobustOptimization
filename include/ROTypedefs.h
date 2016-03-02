//
//  ROTypedefs.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROTypedefs_h
#define RobustOptimizationSolver_ROTypedefs_h

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
// #include <boost/strong_typedef.hpp>
#include <boost/serialization/strong_typedef.hpp>

#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <math.h>
#include "roexceptions.h"


BOOST_STRONG_TYPEDEF(int, ROVarIndex);
BOOST_STRONG_TYPEDEF(int, ROUnIndex);

template<class STRONG_TYPE>
struct StrongTypeHash : std::unary_function<STRONG_TYPE, std::size_t>
{
	std::size_t operator() (STRONG_TYPE const& x) const {
		return boost::hash<int>()(x.t);
	}
};

typedef double ROKeyValue;

typedef int ROInt;
typedef double RONum;

typedef std::pair<int, int> ROKeyIndex2;
typedef std::pair<double, int> ROKeyValue2;

/*
typedef boost::unordered_map< ROVarIndex, ROKeyValue > ROVarMap;
typedef boost::unordered_map< ROUnIndex, ROKeyValue > ROUnMap;

typedef boost::unordered_map< ROKeyIndex2, ROKeyValue > ROQVarMap;
typedef boost::unordered_map< ROUnIndex, ROKeyValue2 > ROExUnMap;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue > ROUnVarMap;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue2 > ROExUnVarMap;

typedef boost::unordered_map< ROVarIndex, ROKeyValue >::iterator ROVarMapIter;
typedef boost::unordered_map< ROUnIndex, ROKeyValue >::iterator ROUnMapIter;

typedef boost::unordered_map< ROKeyIndex2, ROKeyValue >::iterator ROQVarMapIter;
typedef boost::unordered_map< ROUnIndex, ROKeyValue2 >::iterator ROExUnMapIter;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue >::iterator ROUnVarMapIter;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue2 >::iterator ROExUnVarMapIter;

*/
typedef boost::unordered_map< ROVarIndex, ROKeyValue, StrongTypeHash<ROVarIndex> > ROVarMap;
typedef boost::unordered_map< ROUnIndex, ROKeyValue, StrongTypeHash<ROUnIndex> > ROUnMap;

typedef boost::unordered_map< ROKeyIndex2, ROKeyValue > ROQVarMap;
typedef boost::unordered_map< ROUnIndex, ROKeyValue2, StrongTypeHash<ROUnIndex> > ROExUnMap;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue > ROUnVarMap;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue2 > ROExUnVarMap;

typedef boost::unordered_map< ROVarIndex, ROKeyValue, StrongTypeHash<ROVarIndex> >::iterator ROVarMapIter;
typedef boost::unordered_map< ROUnIndex, ROKeyValue, StrongTypeHash<ROUnIndex> >::iterator ROUnMapIter;

typedef boost::unordered_map< ROKeyIndex2, ROKeyValue >::iterator ROQVarMapIter;
typedef boost::unordered_map< ROUnIndex, ROKeyValue2, StrongTypeHash<ROUnIndex> >::iterator ROExUnMapIter;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue >::iterator ROUnVarMapIter;
typedef boost::unordered_map< ROKeyIndex2, ROKeyValue2 >::iterator ROExUnVarMapIter;

enum ROConstTag {EnumEq, EnumLeq};
enum ROObjectiveTag {EnumMax, EnumMin};

enum ROVarType {EnumROVar, EnumROInt, EnumROBool};

const double RO_HUGE_VAL = HUGE_VAL;
const double RO_HUGE_NVAL = -HUGE_VAL;

#define ROInfinity RO_HUGE_VAL
#define RONInfinity RO_HUGE_NVAL

class ROVar;
class ROVarDR;
class ROUn;
class ROUnVarC;
class ROObjective;
class ROExpr;

class ROBaseConstraint;
class ROUnLinConstraint;
class ROUnSOCConstraint;

class ROConstraint;
class ROConstraintSet;
class LPNumVar;

#endif
