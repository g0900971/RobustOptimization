//
//  ROConstraintSet.cpp
//  RobustOptimizationSolver
//
//	Created by Meilin Zhang on 04/10/12
//
//

#include "ROConstraintSet.h"

#include "ROExpr.h"
#include "ROExprImpl.h"
#include "ROConstraint.h"

ROConstraintSet::ROConstraintSet()
{

}

ROConstraintSet::ROConstraintSet(const ROConstraintSet& p_constSet):
	m_roBaseConst(p_constSet.getROBaseConst()),
	m_baseConstArray(p_constSet.getBaseConstArray()),
	m_unConstArray(p_constSet.getUnConstArray()),
	m_unNormConstArray(p_constSet.getUnNormArray())
{

}

ROConstraintSet::ROConstraintSet(const ROBaseConstraint& p_baseConst)
{
	m_roBaseConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_baseConst));
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
                 const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_unConstArray(p_unConstArray),
	m_unNormConstArray(p_unNormConstArray)
{

}


ROConstraintSet::ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray,
                 const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst,
                 const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_unNormConstArray(p_unNormConstArray)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));
}

ROConstraintSet::ROConstraintSet(const ROUnLinConstraint& p_unConst,
                 const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
                 const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst):
	m_unConstArray(p_unConstArray)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}

ROConstraintSet::ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray,
                 const ROUnSOCConstraint& p_unNormConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst,
                 const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}


ROConstraintSet::ROConstraintSet(const ROUnLinConstraint& p_unConst,
                 const ROUnSOCConstraint& p_unNormConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray):
	m_unConstArray(p_unConstArray)
{

}



ROConstraintSet::ROConstraintSet(const ROUnLinConstraintArray& p_unConstArray)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnLinConstraint> p_unConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));
}


ROConstraintSet::ROConstraintSet(const ROUnLinConstraint& p_unConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_unNormConstArray(p_unNormConstArray)
{

}


ROConstraintSet::ROConstraintSet(const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraintSet::ROConstraintSet(const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}


ROConstraintSet::ROConstraintSet(const ROUnSOCConstraint& p_unNormConst)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);
}



ROConstraintSet& ROConstraintSet::operator = (const ROConstraintSet& p_constSet)
{
	if(this == &p_constSet)
	{
		return *this;
	}

	m_roBaseConst = p_constSet.getROBaseConst();
	m_baseConstArray = p_constSet.getBaseConstArray();
	m_unConstArray = p_constSet.getUnConstArray();
	m_unNormConstArray = p_constSet.getUnNormArray();
	return *this;
}

boost::shared_ptr<ROBaseConstraint> ROConstraintSet::getROBaseConst() const
{
	return m_roBaseConst;
}

boost::shared_ptr<ROBaseConstraintArray> ROConstraintSet::getBaseConstArray() const
{
	return m_baseConstArray;
}


boost::shared_ptr<ROUnLinConstraintArray> ROConstraintSet::getUnConstArray() const
{
	return m_unConstArray;
}

boost::shared_ptr<ROUnSOCConstraintArray> ROConstraintSet::getUnNormArray() const
{
	return m_unNormConstArray;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Primary Constraint
void ROConstraintSet::set(const ROBaseConstraint& p_baseConst)
{
	ROExprType type = p_baseConst.getExpr()->getImpl()->getType();
	if(type == EnumVar || type == EnumQVar || type == EnumUnVar)
	{
		m_roBaseConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_baseConst));
	}
	else
	{
		this->add(p_baseConst);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pay attention to underlying constraint type

void ROConstraintSet::add(const ROBaseConstraint& p_baseConst)
{
	ROExprType type = p_baseConst.getExpr()->getImpl()->getType();
	if (type == EnumVar || type == EnumQVar || type == EnumUnVar || type == EnumExUnVar)
	{
		if(m_baseConstArray.get() == NULL)
		{
			m_baseConstArray = boost::shared_ptr<ROBaseConstraintArray>(new ROBaseConstraintArray());
		}
		m_baseConstArray->add(p_baseConst);
	}
	else if(type == EnumUn || type == EnumExUn)
	{
		if(m_unConstArray.get() == NULL)
		{
			m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
		}
		m_unConstArray->add(p_baseConst);
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}


void ROConstraintSet::add(const ROUnLinConstraint& p_unConst)
{
	if(m_unConstArray.get() == NULL)
	{
		m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	}
	m_unConstArray->add(p_unConst);
}


void ROConstraintSet::add(const ROUnSOCConstraint& p_unNormConst)
{
	if(m_unNormConstArray.get() == NULL)
	{
		m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	}
	m_unNormConstArray->add(p_unNormConst);
}


void ROConstraintSet::add(const ROConstraintSet& p_uncertaintySet)
{
	boost::shared_ptr<ROUnLinConstraintArray> unLinConstArray = p_uncertaintySet.getUnConstArray();
	boost::shared_ptr<ROUnSOCConstraintArray> unSOCConstArray = p_uncertaintySet.getUnNormArray();

	//boost::shared_ptr<ROConstraint> roConst = p_uncertaintySet.getROConst();
	boost::shared_ptr<ROBaseConstraint> roBaseConst = p_uncertaintySet.getROBaseConst();
	boost::shared_ptr<ROBaseConstraintArray> baseConstArray = p_uncertaintySet.getBaseConstArray();

	// Add linear constraints
	if(m_unConstArray.get() == NULL)
	{
		m_unConstArray = unLinConstArray;
	}
	else if(unLinConstArray.get() != NULL)
	{
		size_t iSize_unLin = unLinConstArray->getSize();
		for(int i = 0; i < iSize_unLin; i++)
		{
			m_unConstArray->add((*(unLinConstArray.get()))[i]);
		}
	}

	// Add SOC constraints
	if(m_unNormConstArray.get() == NULL)
	{
		m_unNormConstArray = unSOCConstArray;
	}
	else if(unSOCConstArray.get() != NULL)
	{
		size_t iSize_unLin = unSOCConstArray->getSize();
		for(int i = 0; i < iSize_unLin; i++)
		{
			m_unNormConstArray->add((*(unSOCConstArray.get()))[i]);
		}
	}

	// Add ROConstraint
	if(m_roBaseConst.get() == NULL)
	{
		m_roBaseConst = roBaseConst;
	}

	// Add Base constraints
	if(m_baseConstArray.get() == NULL)
	{
		m_baseConstArray = baseConstArray;
	}
	else if(baseConstArray.get() != NULL)
	{
		size_t iSize_unLin = baseConstArray->getSize();
		for(int i = 0; i < iSize_unLin; i++)
		{
			m_baseConstArray->add((*(baseConstArray.get()))[i]);
		}
	}

}