//
//  rotempimpl.cpp
//  RobustOptimizationSolver
//
//  Created by Tianjue Lin on 6/9/12.
//	Modified by Meilin Zhang on 11/9/12
//
//


#include "ROTypedefs.h"
#include "rotempimpl.h"

template<>
ROKeyIndex2 updateIndex<ROKeyIndex2, ROVarIndex>(const ROVarIndex& keyIndex)
{
	ROKeyIndex2 index2(keyIndex, 0);
	return index2;
}

template<>
ROKeyIndex2 updateIndex<ROKeyIndex2, ROUnIndex>(const ROUnIndex& keyIndex)
{
	ROKeyIndex2 index2(0, keyIndex);
	return index2;
}

template<>
ROKeyIndex2 updateIndex<ROKeyIndex2, ROVarIndex, ROUnIndex>(const ROVarIndex& keyIndex1, const ROUnIndex& keyIndex2)
{
	ROKeyIndex2 index2(keyIndex1, keyIndex2);
	return index2;
}

template<>
ROKeyIndex2 updateIndex<ROKeyIndex2, ROVarIndex, ROVarIndex>(const ROVarIndex& keyIndex1, const ROVarIndex& keyIndex2)
{
	ROKeyIndex2 index2(keyIndex1, keyIndex2);
	return index2;
}

template<>
ROKeyValue updateValue<ROKeyValue>()
{
	ROKeyValue value(0);
	return value;
}

template<>
ROKeyValue2 updateValue<ROKeyValue2>()
{
	ROKeyValue2 value2(std::make_pair(0,0));
	return value2;
}

template<>
ROKeyValue2 updateValue<ROKeyValue2, ROKeyValue>(const ROKeyValue& keyValue)
{
	ROKeyValue2 value2(keyValue, 0);
	return value2;
}

template<>
ROKeyValue2 updateValue<ROKeyValue2, ROKeyValue2>(const ROKeyValue2& keyValue)
{
	return keyValue;
}

template<>
ROKeyValue updateValue<ROKeyValue, ROKeyValue>(const ROKeyValue& keyValue)
{
	return keyValue;
}