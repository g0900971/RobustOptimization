//
//  ROConstraint.cpp
//  RobustOptimizationSolver
//
//	Created by Meilin Zhang on 11/9/12
//
//

#include "ROConstraint.h"
#include "ROConstraintSet.h"


ROConstraint::ROConstraint()
{

}

ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, 
						   const ROConstraintSet& p_uncertaintySet):
	m_unConstArray(p_uncertaintySet.getUnConstArray()),
	m_unNormConstArray(p_uncertaintySet.getUnNormArray())
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));
}

ROConstraint::ROConstraint(const ROConstraintSet& p_varConstSet, 
						   const ROConstraintSet& p_uncertaintySet):
	m_varConst(p_varConstSet.getROBaseConst()),
	m_unConstArray(p_uncertaintySet.getUnConstArray()),
	m_unNormConstArray(p_uncertaintySet.getUnNormArray())
{
	m_baseConstSet = p_varConstSet.getBaseConstArray();

	boost::shared_ptr<ROUnLinConstraintArray> unConstArray = p_varConstSet.getUnConstArray();
	if(unConstArray.get() != NULL)
	{
		size_t iSize_unA = unConstArray->getSize();
		for(int i = 0; i < iSize_unA; i++)
		{
			m_unConstArray->add((*(unConstArray.get()))[i]);
		}
	}

	boost::shared_ptr<ROUnSOCConstraintArray> unNormConstArray = p_varConstSet.getUnNormArray();
	if(unNormConstArray.get() != NULL)
	{
		size_t iSize_unNormA = unNormConstArray->getSize();
		for(int i = 0; i < iSize_unNormA; i++)
		{
			m_unNormConstArray->add((*(unNormConstArray.get()))[i]);
		}
	}
	
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
						   const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_varConst(p_varConst),
	m_unConstArray(p_unConstArray),
	m_unNormConstArray(p_unNormConstArray)
{

}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, 
						   const ROUnLinConstraintArray& p_unConstArray,
						   const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnLinConstraint> p_unConst,
						   const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_varConst(p_varConst),
	m_unNormConstArray(p_unNormConstArray)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, 
						   const ROUnLinConstraint& p_unConst,
						   const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));

	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray,
						   const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst):
	m_varConst(p_varConst),
	m_unConstArray(p_unConstArray)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, 
						   const ROUnLinConstraintArray& p_unConstArray,
						   const ROUnSOCConstraint& p_unNormConst)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);

}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst,
						   const boost::shared_ptr<ROUnLinConstraint> p_unConst,
						   const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst):
	m_varConst(p_varConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst,
						   const ROUnLinConstraint& p_unConst,
						   const ROUnSOCConstraint& p_unNormConst)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));

	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnLinConstraintArray> p_unConstArray):
	m_varConst(p_varConst),
	m_unConstArray(p_unConstArray)
{

}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, 
						   const ROUnLinConstraintArray& p_unConstArray)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray(p_unConstArray));
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnLinConstraint> p_unConst):
	m_varConst(p_varConst)
{
	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(*(p_unConst.get()));
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, const ROUnLinConstraint& p_unConst)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));

	m_unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	m_unConstArray->add(p_unConst);
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnSOCConstraintArray> p_unNormConstArray):
	m_varConst(p_varConst),
	m_unNormConstArray(p_unNormConstArray)
{
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, const ROUnSOCConstraintArray& p_unNormConstArray)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray(p_unNormConstArray));
}


ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_varConst, 
						   const boost::shared_ptr<ROUnSOCConstraint> p_unNormConst):
	m_varConst(p_varConst)
{
	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(*(p_unNormConst.get()));
}


ROConstraint::ROConstraint(const ROBaseConstraint& p_varConst, const ROUnSOCConstraint& p_unNormConst)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_varConst));

	m_unNormConstArray = boost::shared_ptr<ROUnSOCConstraintArray>(new ROUnSOCConstraintArray());
	m_unNormConstArray->add(p_unNormConst);
}



ROConstraint::ROConstraint(const boost::shared_ptr<ROBaseConstraint> p_const):
	m_varConst(p_const)
{

}


ROConstraint::ROConstraint(const ROBaseConstraint& p_const)
{
	m_varConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(p_const));
}



ROConstraint::ROConstraint(const ROConstraint& p_const):
	m_varConst( p_const.getVarConst() ),
	m_unConstArray( p_const.getUnConstArray() ),
	m_unNormConstArray( p_const.getUnNormArray() ),
	m_baseConstSet(p_const.getBaseConstArray() )
{

}

ROConstraint& ROConstraint::operator = (const ROConstraint& p_const)
{
	if(this == &p_const)
	{
		return *this;
	}
	m_varConst = p_const.getVarConst();
	m_unConstArray = p_const.getUnConstArray();
	m_unNormConstArray = p_const.getUnNormArray();
	return *this;
}

boost::shared_ptr<ROBaseConstraint> ROConstraint::getVarConst() const
{
	return m_varConst;
}

boost::shared_ptr<ROUnLinConstraintArray> ROConstraint::getUnConstArray() const
{
	return m_unConstArray;
}

boost::shared_ptr<ROUnSOCConstraintArray> ROConstraint::getUnNormArray() const
{
	return m_unNormConstArray;
}

boost::shared_ptr<ROBaseConstraintArray> ROConstraint::getBaseConstArray() const
{
	return m_baseConstSet;
}