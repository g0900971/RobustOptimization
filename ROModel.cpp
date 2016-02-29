//
//  ROModel.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 2/9/12.
//  Modified by Meilin Zhang on 19/06/2013
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <ctime>

#include "ROModel.h"
#include "ROConstraint.h"
#include "ROBaseConstraint.h"
#include "ROUnLinConstraint.h"
#include "ROUnSOCConstraint.h"
#include "ROObjective.h"
#include "ROExpr.h"
#include "ROExprImpl.h"
#include "ROUnVarImpl.h"
#include "ROVarsImpl.h"
#include "ROUnsImpl.h"
#include "roexprfunctions.h"
#include "ROVar.h"
#include "ROUn.h"
#include "ROExUnVarImpl.h"
#include "ROUnImpl.h"
#include "ROVarImpl.h"
#include "ROQVarImpl.h"
#include "ROExUnImpl.h"
#include "lptemplate.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to public functions

class ROVarVector
{
public:
	ROVarVector()
	{
		//m_v_var = boost::shared_ptr<SpROVarVectorType >(new std::vector<boost::shared_ptr<ROVar> >());
	}
	ROVarVector(size_t p_size)
	{
		m_v_var = boost::shared_ptr<SpROVarVectorType >(new std::vector<boost::shared_ptr<ROVar> >());
	}

	boost::shared_ptr<ROVar> operator[](size_t i)
	{
		return (*(m_v_var.get()))[i];
	}

	void push_back(const boost::shared_ptr<ROVar> sp_var)
	{
		m_v_var.get()->push_back(sp_var);
	}

	ROVarVector& operator = (const ROVarVector& p)
	{
		if(this != &p)
		{
			m_v_var = p.m_v_var;
		}
		return *this;
	}

	size_t getSize()
	{
		return m_v_var->size();
	}

private:
	boost::shared_ptr<std::vector<boost::shared_ptr<ROVar> > > m_v_var;
	typedef std::vector<boost::shared_ptr<ROVar> > SpROVarVectorType;
};

class ROVarVector2D
{
public:
	ROVarVector2D()
	{
		//m_var2D.reserve(p_size);
	}

	ROVarVector& operator [](size_t j)
	{
		return m_var2D[j];
	}
	
	void push_back(const ROVarVector& p_var_vector)
	{
		m_var2D.push_back(p_var_vector);
	}

	size_t getSize()
	{
		return m_var2D.size();
	}

private:
	std::vector<ROVarVector> m_var2D;
};


ROModel::ROModel()
{
	m_lpFactory = boost::shared_ptr<Factory<TYPE> >(new Factory<TYPE>());
	m_lpModel = boost::shared_ptr<Model<TYPE> >(m_lpFactory->createModel());
	m_p_vec_lpVar = boost::shared_ptr<LPVarArray>(new LPVarArray());
}

boost::shared_ptr<Model<TYPE> > ROModel::getModel() const
{
	return m_lpModel;
}

boost::shared_ptr<ROObjective> ROModel::getObjective() const
{
	return m_obj;
}

void ROModel::add(const ROBaseConstraint & p_const)
{
	boost::shared_ptr<ROConstraint> m_roconst = boost::shared_ptr<ROConstraint>(new ROConstraint(p_const));
	m_listConst.push_back(m_roconst);
}

void ROModel::add(ROBaseConstraintArray & p_constArray)
{
	size_t size = p_constArray.getSize();

	for(int i = 0; i < size; i++)
	{
		this->add(p_constArray[i]);
	}
}

// ----- Need Refactoring in future,  I dont like this! ---------------
void ROModel::add(const ROConstraint & p_const)
{
	boost::shared_ptr<ROConstraint> sp_roConst = boost::shared_ptr<ROConstraint>(new ROConstraint(p_const));
	m_listConst.push_back(sp_roConst);

	boost::shared_ptr<ROBaseConstraintArray> sp_baseConstArray = p_const.getBaseConstArray();
	boost::shared_ptr<ROUnLinConstraintArray> sp_iUnConstA = p_const.getUnConstArray();
	boost::shared_ptr<ROUnSOCConstraintArray> sp_iSOCConstA = p_const.getUnNormArray();

	if(sp_baseConstArray.get() != NULL)
	{
		size_t iSize = sp_baseConstArray->getSize();
		for(size_t i = 0; i < iSize; i++)
		{
			ROBaseConstraint& ref_iBaseConst = (*(sp_baseConstArray.get()))[i];
			ROExpr& ref_iExpr = *(ref_iBaseConst.getExpr().get());
			boost::shared_ptr<ROExprImpl> sp_iExprI = ref_iExpr.getImpl();

			if(sp_iExprI->getType() == EnumVar || sp_iExprI->getType() == EnumQVar)
			{
				this->add(ref_iBaseConst);
			}
			else
			{
				boost::shared_ptr<ROBaseConstraint> sp_iBaseConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(ref_iBaseConst));

				boost::shared_ptr<ROConstraint> sp_iROConst = boost::shared_ptr<ROConstraint>(new ROConstraint(sp_iBaseConst, sp_iUnConstA, sp_iSOCConstA));

				m_listConst.push_back(sp_iROConst);
			}
		}

		
	}
}
// ------------------ End ----------------------------------------------

void ROModel::add(ROConstraintArray & p_constArray)
{
	size_t size = p_constArray.getSize();

	for(int i = 0; i < size; i++)
	{
		this->add(p_constArray[i]);
	}
}

//
// ----- Need Refactoring in future,  I dont like this! ---------------

void ROModel::add(const ROConstraintSet & p_constSet)
{
	ROBaseConstraint* ptr_roBaseconst = p_constSet.getROBaseConst().get();

	boost::shared_ptr<ROBaseConstraintArray> sp_baseConstArray = p_constSet.getBaseConstArray();
	boost::shared_ptr<ROUnLinConstraintArray> sp_iUnConstA = p_constSet.getUnConstArray();
	boost::shared_ptr<ROUnSOCConstraintArray> sp_iSOCConstA = p_constSet.getUnNormArray();

	if(ptr_roBaseconst != NULL)
	{
		ROExpr& ref_Expr = *(ptr_roBaseconst->getExpr().get());
		boost::shared_ptr<ROExprImpl> sp_ExprI = ref_Expr.getImpl();
		if(sp_ExprI->getType() == EnumVar || sp_ExprI->getType() == EnumQVar)
		{
			this->add(*ptr_roBaseconst);
		}
		else
		{
			boost::shared_ptr<ROBaseConstraint> sp_BaseConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(*ptr_roBaseconst));

			boost::shared_ptr<ROConstraint> sp_ROConst = boost::shared_ptr<ROConstraint>(new ROConstraint(sp_BaseConst, sp_iUnConstA, sp_iSOCConstA));

			m_listConst.push_back(sp_ROConst);
		}
	}

	if(sp_baseConstArray.get() != NULL)
	{
		size_t iSize = sp_baseConstArray->getSize();
		for(int i = 0; i < iSize; i++)
		{
			ROBaseConstraint& ref_iBaseConst = (*(sp_baseConstArray.get()))[i];
			ROExpr& ref_iExpr = *(ref_iBaseConst.getExpr().get());
			boost::shared_ptr<ROExprImpl> sp_iExprI = ref_iExpr.getImpl();

			if(sp_iExprI->getType() == EnumVar || sp_iExprI->getType() == EnumQVar)
			{
				this->add(ref_iBaseConst);
			}
			else
			{
				boost::shared_ptr<ROBaseConstraint> sp_iBaseConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(ref_iBaseConst));

				boost::shared_ptr<ROConstraint> sp_iROConst = boost::shared_ptr<ROConstraint>(new ROConstraint(sp_iBaseConst, sp_iUnConstA, sp_iSOCConstA));

				m_listConst.push_back(sp_iROConst);
			}
		}

		
	}
}
// ------------------ End ----------------------------------------------


void ROModel::add(const ROObjective & p_obj)
{
	m_obj = boost::shared_ptr<ROObjective>(new ROObjective(p_obj));

	boost::shared_ptr<ROConstraintSet> constSet = p_obj.getConstSet();
	if(constSet.get() != NULL)
	{
		this->add(*(constSet.get()));
	}
}

void ROModel::solve()
{
	// Check the expiration date
  /*
	time_t now = time(0);
	tm* ptr_tm = localtime(&now);

	if(( ptr_tm->tm_year + 1900) >= 2014)
	{
		std::cerr << "Expiration date pass!" << std::endl;
		return;
	}
  */


	std::list< boost::shared_ptr<ROConstraint> >::iterator iter;

	for(iter = m_listConst.begin(); iter != m_listConst.end(); iter++)
	{
		transform(*((*iter).get()));
	}

	lpSolve();

}

RONum ROModel::getObjValue()
{
	return m_lpModel->getObjValue();
}

std::string ROModel::getStatus()
{
	return m_lpModel->getStatus();
}


RONum ROModel::getVarValue(const ROVar& p_var)
{
	LPVarArray& m_vec_lpVar = *m_p_vec_lpVar.get();
	int id = p_var.getId();
	boost::shared_ptr<Var<TYPE> > lpVar = m_vec_lpVar[id-1];
	double value = m_lpModel->getVarValue(*(lpVar.get()));
	return value;
}

void ROModel::exportModel()
{
	m_lpModel->exportModel();
}

void ROModel::exportModel(std::string& p_dirPath)
{
	m_lpModel->exportModel(p_dirPath);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to private functions

void ROModel::transform(const ROConstraint & p_const)
{
	if(p_const.getVarConst().get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::transform::ROConstraint");
		throw exp;
	}

	ROExprType varType = p_const.getVarConst()->getExpr()->getImpl()->getType();

	if(varType == EnumNull || varType == EnumVar || varType == EnumQVar)
	{
		m_baseConst.push_back(p_const.getVarConst());
	}
	else if(p_const.getVarConst()->getTag() == EnumEq && varType != EnumExUnVar)
	{
		transformEq(p_const);
	}
	else if(p_const.getVarConst()->getTag() == EnumLeq)
	{
		if(varType == EnumExUnVar)
		{
			transformExpect(p_const);
		}
		else
		{
			transformLeq(p_const);
		}
	}
	else
	{
		ROExceptionTypeIncompatible exp;
        throw exp;
	}
}


void ROModel::transformEq(const ROConstraint & p_const)
{
	// PART I : UnVarMap and UnMaps decompose
	ROUVSubMap uvSubMap;
	boost::shared_ptr<ROExpr> sp_expr0 = boost::shared_ptr<ROExpr>(new ROExpr());
	*(sp_expr0.get()) += p_const.getVarConst()->getExpr()->getImpl()->getNum();
	sp_expr0->getImpl()->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));

	decompose(p_const, sp_expr0, uvSubMap);

	// PART II
	m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(*(sp_expr0.get()) == 0)));

	ROUVSubMapIter iter = uvSubMap.begin();
	while(iter != uvSubMap.end())
	{
		m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(*(iter->second.get()) == 0)));
		iter++;
	}

}

void ROModel::transformLeq(const ROConstraint & p_const)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART 0 : Deal with those unexpected "ExUn" uncertain constraints 

	// Abstraction --- p_const
	boost::shared_ptr<ROUnLinConstraintArray> sp_unConstA = p_const.getUnConstArray();

	boost::shared_ptr<ROUnSOCConstraintArray> sp_unNorm_const_array = p_const.getUnNormArray();
	// ---------- end --------

	boost::shared_ptr<ROUnLinConstraintArray> sp_un_const_array = 
												boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	if(sp_unConstA.get() != NULL)
	{
		size_t iSizeUnConstA = sp_unConstA->getSize();
		for(int i = 0; i < iSizeUnConstA; i++)
		{
			ROUnLinConstraint& ref_iUnConst = (*(sp_unConstA.get()))[i];
			ROExprType varType = ref_iUnConst.getExpr()->getImpl()->getType();

			if(varType != EnumExUn)
			{
				sp_un_const_array->add(ref_iUnConst);
			}

		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART I : UnVarMap and UnMaps decompose
	ROUVSubMap uvSubMap;
	boost::shared_ptr<ROExpr> sp_expr0 = boost::shared_ptr<ROExpr>(new ROExpr());
	*(sp_expr0.get()) += p_const.getVarConst()->getExpr()->getImpl()->getNum();
	sp_expr0->getImpl()->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));

	decompose(p_const, sp_expr0, uvSubMap);
	// ---------- end --------



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Abstractiong --- sp_expr0
	boost::shared_ptr<ROExprImpl> sp_expr0_impl = sp_expr0->getImpl();
	if(sp_expr0_impl.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::transformLeq::sp_expr0_impl");
		throw exp;
	}
	boost::shared_ptr<ROExprMapImpl> sp_expr0_map_impl = sp_expr0_impl->getMapImpl();
	if(sp_expr0_map_impl.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::transformLeq::sp_expr0_map_impl");
		throw exp;
	}
	ROExprMapUnion& expr0_impl_mapUnion = sp_expr0_map_impl->getUnion();
	ROVarsImpl* expr0_impl_varsI = expr0_impl_mapUnion.m_varsI;
	if(expr0_impl_varsI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::transformLeq::expr0_impl_varsI");
		throw exp;
	}
	ROVarMap& expr0_impl_varMap = expr0_impl_varsI->getMap();
	// ---------- end --------

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART II -- obj constraint
	size_t size_unA = 0;
	if(sp_un_const_array.get() != NULL)
	{
		size_unA = sp_un_const_array->getSize();
	}
	ROVarVector v_sp_varNew(size_unA);
	

	// Base Uncertain Constraints 
	for(unsigned int i = 0; i < size_unA; i++)
	{
		ROUnLinConstraint& ref_i_bConst = (*(sp_un_const_array.get()))[i];

		// Abstraction --- ref_i_bConst ---
		boost::shared_ptr<ROExpr> sp_i_expr = ref_i_bConst.getExpr();
		if(sp_i_expr.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_i_expr");
			throw exp;
		}

		boost::shared_ptr<ROExprImpl> sp_i_exprI = sp_i_expr->getImpl();
		if(sp_i_exprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_i_exprI");
			throw exp;
		}

		// ------------- end ------------

		if( ref_i_bConst.getTag() == EnumEq )
		{
			boost::shared_ptr<ROVar> sp_var = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "Un"));
			v_sp_varNew.push_back(sp_var);

			double val = 0 - sp_i_exprI->getNum();
			expr0_impl_varMap.insert(std::make_pair(ROVarIndex(sp_var->getId()), val));
		}
		else
		{
			boost::shared_ptr<ROVar> sp_var = boost::shared_ptr<ROVar>(new ROVar(0, ROInfinity, "Un"));
			v_sp_varNew.push_back(sp_var);

			double val = 0 - sp_i_exprI->getNum();
			expr0_impl_varMap.insert(std::make_pair(ROVarIndex(sp_var->getId()), val));
		}
	}

	// Norm Uncertain Constraints 
	size_t size_unNA = 0;
	if(sp_unNorm_const_array.get() != NULL)
	{
		size_unNA = sp_unNorm_const_array->getSize();
	}
	
	ROVarVector2D v_sp_varNew2D;
	
	for(unsigned int i = 0; i < size_unNA; i++)
	{
		ROUnSOCConstraint& ref_i_nConst = (*(sp_unNorm_const_array.get()))[i];

		// Abstraction --- ref_i_nConst ---
		boost::shared_ptr<ROExprArray> sp_i_expr_array = ref_i_nConst.getExprArray();
		if(sp_i_expr_array.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_i_expr_array_norm");
			throw exp;
		}

		boost::shared_ptr<ROExpr> sp_i_expr = ref_i_nConst.getExpr();
		if(sp_i_expr.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_i_expr_norm");
			throw exp;
		}

		boost::shared_ptr<ROExprImpl> sp_i_exprI = sp_i_expr->getImpl();
		if(sp_i_exprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_i_exprI_norm");
			throw exp;
		}
		// ------------- end ------------

		size_t iSize = sp_i_expr_array->getSize();
		v_sp_varNew2D.push_back(ROVarVector(iSize+1));

		for(int j = 0; j < iSize; j++ )
		{
			ROExpr& ref_expr_i_j = (*(sp_i_expr_array.get()))[j];

			// Abstraction --- ref_expr_i_j ---
			boost::shared_ptr<ROExprImpl> sp_exprI_i_j = ref_expr_i_j.getImpl();
			if(sp_exprI_i_j.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Objective::sp_exprI_i_j_norm");
				throw exp;
			}
			// ------------- end ------------

			double val = sp_exprI_i_j->getNum();

			v_sp_varNew2D[i].push_back(boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "UnNV")));
			ROVarIndex index = ROVarIndex((v_sp_varNew2D[i][j])->getId());

			expr0_impl_varMap.insert(std::make_pair(index, val));
		}

		double val = sp_i_exprI->getNum();

		v_sp_varNew2D[i].push_back(boost::shared_ptr<ROVar>(new ROVar(0, ROInfinity, "UnN")));
		ROVarIndex index = ROVarIndex(v_sp_varNew2D[i][iSize]->getId());

		if(val != 0)
		{
			expr0_impl_varMap.insert(std::make_pair(index, val));
		}

	}

	m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(*(sp_expr0.get())<= 0)));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART III --- sub constraint

	/*
	 * Modified on 05-Apr-3013, for fixing the bug of memory leak in ROVarImplManager
	 */
	for(int i = 0; i < ROUn::getNo(); i++)
	{
		boost::shared_ptr<ROExpr> sp_i_expr = boost::shared_ptr<ROExpr>(new ROExpr());
		boost::shared_ptr<ROExprImpl> sp_i_exprI = sp_i_expr->getImpl();
		if(sp_i_exprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_exprI");
			throw exp;
		}

		sp_i_exprI->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));

		// Abstraction --- sp_i_expr ---
		boost::shared_ptr<ROExprMapImpl> sp_i_mapI = sp_i_exprI->getMapImpl();
		if(sp_i_mapI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_mapI");
			throw exp;
		}

		ROExprMapUnion& ref_i_map_union = sp_i_mapI->getUnion();
		ROVarsImpl* ptr_i_varsI = ref_i_map_union.m_varsI;
		if(ptr_i_varsI == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::ptr_i_varsI");
			throw exp;
		}

		ROVarMap& ref_i_varMap = ptr_i_varsI->getMap();
		// ------------ end ----------

		// Base Uncertain Constraints 
		for(unsigned int j = 0; j < size_unA; j++)
		{
			// Abstraction --- un_const_array[j]
			ROUnLinConstraint& ref_i_j_bConst = (*(sp_un_const_array.get()))[j];
			
			boost::shared_ptr<ROExpr> sp_i_j_expr = ref_i_j_bConst.getExpr();
			if(sp_i_j_expr.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_expr_base");
				throw exp;
			}

			boost::shared_ptr<ROExprImpl> sp_i_j_exprI = sp_i_j_expr->getImpl();
			if(sp_i_j_exprI.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_exprI_base");
				throw exp;
			}

			boost::shared_ptr<ROExprMapImpl> sp_i_j_mapI = sp_i_j_exprI->getMapImpl();
			if(sp_i_j_mapI.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_mapI_base");
				throw exp;
			}

			ROExprMapUnion& ref_i_j_map_union = sp_i_j_mapI->getUnion();
			ROUnsImpl* ptr_i_j_unsI = ref_i_j_map_union.m_unsI;
			if(ptr_i_j_unsI == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::ptr_i_j_unsI_base");
				throw exp;
			}

			ROUnMap& ref_i_j_unMap = ptr_i_j_unsI->getMap();
			// ------------ end ----------


			ROVarIndex index = ROVarIndex(v_sp_varNew[j]->getId());

			ROUnMapIter iter_ij_B = ref_i_j_unMap.find(ROUnIndex(i));
			if(iter_ij_B != ref_i_j_unMap.end())
			{
				double val = iter_ij_B->second;
				ref_i_varMap.insert(std::make_pair(index, val));
			}
		}

		// Norm Uncertain Constraints 
		for(unsigned int j = 0; j < size_unNA; j++)
		{
			ROUnSOCConstraint& ref_i_j_nConst = (*(sp_unNorm_const_array.get()))[j];
			
			// Abstraction --- sp_i_j_exprArray
			boost::shared_ptr<ROExprArray> sp_i_j_exprArray = ref_i_j_nConst.getExprArray();
			if(sp_i_j_exprArray.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_exprArray_norm");
				throw exp;
			}	
			// ------------ end ----------

			size_t size_i_j_normArray = sp_i_j_exprArray->getSize();
			for(unsigned int k = 0; k < size_i_j_normArray; k++)
			{
				ROExpr& ref_i_j_k_expr = (*(sp_i_j_exprArray.get()))[k];
			
				// Abstraction --- sp_i_j_exprArray
				boost::shared_ptr<ROExprImpl> sp_i_j_k_exprI = ref_i_j_k_expr.getImpl();
				if(sp_i_j_k_exprI.get() == NULL)
				{
					ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_k_exprI_norm");
					throw exp;
				}	

				boost::shared_ptr<ROExprMapImpl> sp_i_j_k_mapI = sp_i_j_k_exprI->getMapImpl();
				if(sp_i_j_k_mapI.get() == NULL)
				{
					ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_k_mapI_norm");
					throw exp;
				}

				ROExprMapUnion& sp_i_j_k_map_union = sp_i_j_k_mapI->getUnion();
				ROUnsImpl* ptr_i_j_k_unsI = sp_i_j_k_map_union.m_unsI;
				if(ptr_i_j_k_unsI == NULL)
				{
					ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::ptr_i_j_k_unsI_norm");
					throw exp;
				}

				ROUnMap& ref_i_j_k_unMap = ptr_i_j_k_unsI->getMap();
				// ------------ end ----------

				ROVarIndex index = ROVarIndex((v_sp_varNew2D[j][k])->getId());

				ROUnMapIter iter_ijk_N = ref_i_j_k_unMap.find(ROUnIndex(i));
				if(iter_ijk_N != ref_i_j_k_unMap.end())
				{
					double val = 0 - iter_ijk_N->second; // Negative
					ref_i_varMap.insert(std::make_pair(index, val));
				}
			}

			// Abstraction --- sp_i_j_exprArray
			boost::shared_ptr<ROExpr> sp_i_j_expr = ref_i_j_nConst.getExpr();
			if(sp_i_j_expr.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_expr_normE");
				throw exp;
			}	

			boost::shared_ptr<ROExprImpl> sp_i_j_exprI = sp_i_j_expr->getImpl();
			if(sp_i_j_exprI.get() == NULL)
			{
				ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_j_exprI_normE");
				throw exp;
			}	

			boost::shared_ptr<ROExprMapImpl> sp_i_j_mapI = sp_i_j_exprI->getMapImpl();
			if(sp_i_j_mapI.get() != NULL)
			{

				ROExprMapUnion& sp_i_j_map_union = sp_i_j_mapI->getUnion();
				ROUnsImpl* ptr_i_j_unsI = sp_i_j_map_union.m_unsI;
				if(ptr_i_j_unsI == NULL)
				{
					ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::ptr_i_j_unsI_normE");
					throw exp;
				}

				ROUnMap& ref_i_j_unMap = ptr_i_j_unsI->getMap();
				// ------------ end ----------

				ROVarIndex index = ROVarIndex((v_sp_varNew2D[j][size_i_j_normArray])->getId());

				if(ref_i_j_unMap.find(ROUnIndex(i)) != ref_i_j_unMap.end())
				{
					double val = 0 - ref_i_j_unMap.find(ROUnIndex(i))->second; // Negative
					ref_i_varMap.insert(std::make_pair(index, val));
				}
			}
		}

		ROUVSubMapIter iter = uvSubMap.find(ROUnIndex(i));
		if(iter != uvSubMap.end())
		{
			ROUVSubMap::mapped_type element = iter->second;
			if(element.get() != NULL)
			{
				if(sp_i_expr.get() == NULL)
				{
					ROExceptionNullPointer exp("ROModel::transformLeq::Sub_Constraint::sp_i_expr_end");
					throw exp;
				}

				ROExpr& spExprRef = *sp_i_expr.get();
				ROExpr& secondExprRef = *element.get();
				m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(spExprRef == secondExprRef)));
			}

		}
		else
		{
			ROExpr& spExprRef = *sp_i_expr.get();
			m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(spExprRef == 0)));
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART IV --- quadratic constraint
	for(unsigned int i = 0; i < size_unNA; i++)
	{
		boost::shared_ptr<ROExpr> sp_i_expr = boost::shared_ptr<ROExpr>(new ROExpr());
		sp_i_expr->getImpl()->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar)));

		ROExpr& ref_i_expr = *(sp_i_expr.get());

		size_t size_i_soc = v_sp_varNew2D[i].getSize() - 1;
		ref_i_expr -= *(v_sp_varNew2D[i][size_i_soc].get()) * *(v_sp_varNew2D[i][size_i_soc].get());

		ROExpr exprTemp;
		for(unsigned int j = 0; j < size_i_soc; j++)
		{
			exprTemp += (*(v_sp_varNew2D[i][j].get())) * (*(v_sp_varNew2D[i][j].get()));
		}
		ref_i_expr  += exprTemp;
		m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(ref_i_expr <= 0)));

	}

}

void ROModel::transformExpect(const ROConstraint & p_const)
{
	// PART I : decompose expectation part and non expectation part
	boost::shared_ptr<ROExpr> sp_expr0 = boost::shared_ptr<ROExpr>(new ROExpr());
	*(sp_expr0.get()) += p_const.getVarConst()->getExpr()->getImpl()->getNum();
	sp_expr0->getImpl()->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));
	
	boost::shared_ptr<ROExprImpl> sp_expr0I = sp_expr0->getImpl();
	boost::shared_ptr<ROExprMapImpl> sp_expr0_mapI = sp_expr0I->getMapImpl();
	ROExprMapUnion& ref_expr0_mapU = sp_expr0_mapI->getUnion();
	ROVarsImpl* ptr_expr0_varsI = ref_expr0_mapU.m_varsI;
	ROVarMap& ref_expr0_varMap = ptr_expr0_varsI->getMap();

	boost::shared_ptr<ROExpr> sp_expr1 = boost::shared_ptr<ROExpr>(new ROExpr());
	sp_expr1->getImpl()->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar)));

	boost::shared_ptr<ROUnLinConstraintArray> unConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	boost::shared_ptr<ROUnLinConstraintArray> unExConstArray = boost::shared_ptr<ROUnLinConstraintArray>(new ROUnLinConstraintArray());
	
	decomposeExpect(p_const, sp_expr0, sp_expr1, unConstArray, unExConstArray);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART II -- obj constraint
	size_t size_exUnConstArray = unExConstArray->getSize();
	ROVarVector v_sp_varNew((size_exUnConstArray+1));	

	// Base ExUncertain Constraints 
	for(unsigned int i = 0; i < size_exUnConstArray; i++)
	{
		ROUnLinConstraint& ref_i_exBConst = (*(unExConstArray.get()))[i];

		// Abstraction --- ref_i_exBConst ---
		boost::shared_ptr<ROExpr> sp_i_exExpr = ref_i_exBConst.getExpr();
		if(sp_i_exExpr.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::Objective::sp_i_exExpr");
			throw exp;
		}

		boost::shared_ptr<ROExprImpl> sp_i_exExprI = sp_i_exExpr->getImpl();
		if(sp_i_exExprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::Objective::sp_i_exExprI");
			throw exp;
		}
		// ------------- end ------------

		if(ref_i_exBConst.getTag() == EnumEq)
		{
			boost::shared_ptr<ROVar> sp_var_i = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "Ex"));
			v_sp_varNew.push_back(sp_var_i);

			double val = 0 - sp_i_exExprI->getNum();
			ref_expr0_varMap.insert(std::make_pair(ROVarIndex(sp_var_i->getId()), val));
		}
		else
		{
			boost::shared_ptr<ROVar> sp_var_i = boost::shared_ptr<ROVar>(new ROVar(0, ROInfinity, "Ex"));
			v_sp_varNew.push_back(sp_var_i);

			double val = 0 - sp_i_exExprI->getNum();
			ref_expr0_varMap.insert(std::make_pair(ROVarIndex(sp_var_i->getId()), val));
		}
	}
	boost::shared_ptr<ROVar> sp_var = boost::shared_ptr<ROVar>(new ROVar(RONInfinity, ROInfinity, "Ex0"));
	v_sp_varNew.push_back(sp_var);
	ref_expr0_varMap.insert(std::make_pair(ROVarIndex(sp_var->getId()), 1));
	
	// Add into m_baseConst
	m_baseConst.push_back(boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(*(sp_expr0.get())<= 0)));


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART III -- sub constraint
	boost::shared_ptr<ROExpr> sp_sub_expr = boost::shared_ptr<ROExpr>(new ROExpr());
	boost::shared_ptr<ROExprImpl> sp_sub_exprI = sp_sub_expr->getImpl();

	sp_sub_exprI->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar)));

	*(sp_sub_expr.get()) += *(v_sp_varNew[size_exUnConstArray].get());

	// Abstraction --- sp_sub_exprI ---
	boost::shared_ptr<ROExprMapImpl> sp_sub_expr_mapI = sp_sub_exprI->getMapImpl();
	ROExprMapUnion& sp_sub_expr_mapU = sp_sub_expr_mapI->getUnion();
	ROUnVarImpl* ptr_sub_expr = sp_sub_expr_mapU.m_unVarI;
	ROUnVarMap& ref_sub_expr_unVarMap = ptr_sub_expr->getMap();
	// ------------- end ------------

	for(unsigned int i = 0; i < size_exUnConstArray; i++)
	{
		ROUnLinConstraint& ref_i_exBConst = (*(unExConstArray.get()))[i];

		// --------------------------Design defect (Need Refactoring in future)----------------------------------------------
		// Abstraction --- ref_i_exBConst ---
		boost::shared_ptr<ROExpr> sp_i_exExpr = ref_i_exBConst.getExpr();
		if(sp_i_exExpr.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::subConstraint::sp_i_exExpr");
			throw exp;
		}
		
		boost::shared_ptr<ROExprImpl> sp_i_exExprI = sp_i_exExpr->getImpl();
		if(sp_i_exExprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::subConstraint::sp_i_exExprI");
			throw exp;
		}
		boost::shared_ptr<ROExprMapImpl> sp_i_exExpr_mapI = sp_i_exExprI->getMapImpl();
		if(sp_i_exExpr_mapI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::subConstraint::sp_i_exExpr_mapI");
			throw exp;
		}
		ROExprMapUnion& ref_i_exExpr_mapU = sp_i_exExpr_mapI->getUnion();
		ROExUnImpl* ptr_i_exExpr_exUnI = ref_i_exExpr_mapU.m_exUnI;
		if(ptr_i_exExpr_exUnI == NULL)
		{
			ROExceptionNullPointer exp("ROModel::transformExpect::subConstraint::ptr_i_exExpr_exUnI");
			throw exp;
		}

		ROExUnMap& ref_i_exExpr_exUnMap = ptr_i_exExpr_exUnI->getMap();
		// ------------- end ------------

		int id_newVar = v_sp_varNew[i]->getId();
		ROExUnMapIter iter_i_exExpr_exUnMap = ref_i_exExpr_exUnMap.begin();
		while(iter_i_exExpr_exUnMap != ref_i_exExpr_exUnMap.end())
		{
			int id_i_un = iter_i_exExpr_exUnMap->first;
			double val_i_un = iter_i_exExpr_exUnMap->second.first;

			ref_sub_expr_unVarMap.insert(std::make_pair(std::make_pair(id_newVar, id_i_un), val_i_un));
			iter_i_exExpr_exUnMap++;
		}
		// --------------------------------------------Design defect (End)---------------------------------------------------
	}

	// Abstraction --- sp_expr1 ---
	boost::shared_ptr<ROExprImpl> sp_expr1_Impl = sp_expr1->getImpl();
	boost::shared_ptr<ROExprMapImpl> sp_expr1_mapI = sp_expr1_Impl->getMapImpl();
	ROExprMapUnion& ref_expr1_mapU = sp_expr1_mapI->getUnion();
	ROExUnVarImpl* ptr_expr1_exUnVarI = ref_expr1_mapU.m_exUnVarI;

	ROExUnVarMap& ref_expr1_exUnVarMap = ptr_expr1_exUnVarI->getMap();
	// ------------- end ------------

	ROExUnVarMapIter iter_expr1_exUnVarMap = ref_expr1_exUnVarMap.begin();
	while(iter_expr1_exUnVarMap != ref_expr1_exUnVarMap.end())
	{
		ROKeyIndex2 index = iter_expr1_exUnVarMap->first;
		double val = 0 - iter_expr1_exUnVarMap->second.first; // Negative

		ref_sub_expr_unVarMap.insert(std::make_pair(index, val));
		iter_expr1_exUnVarMap++;
	}


	ROExpr& ref_sub_expr = *(sp_sub_expr.get());

	size_t sizeTest = ref_sub_expr.getImpl()->getMapImpl()->getUnion().m_unVarI->getMap().size();

	boost::shared_ptr<ROBaseConstraint> sp_sub_bConst = boost::shared_ptr<ROBaseConstraint>(new ROBaseConstraint(ref_sub_expr >= 0));
	boost::shared_ptr<ROUnSOCConstraintArray> sp_unNorm_const_array = p_const.getUnNormArray();


	ROConstraint sub_ROConst(sp_sub_bConst, unConstArray, sp_unNorm_const_array);

	transformLeq(sub_ROConst);
}

void ROModel::decompose(const ROConstraint & p_const, boost::shared_ptr<ROExpr> p_vExpr, ROUVSubMap & p_uvSubMap)
{
	// Process
	// Abstraction --- sp_i_j_exprArray
	boost::shared_ptr<ROBaseConstraint> sp_uv_bConst = p_const.getVarConst();
	if(sp_uv_bConst.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::uv_Constraint::sp_uv_bConst");
		throw exp;
	}

	boost::shared_ptr<ROExpr> sp_uv_expr = sp_uv_bConst->getExpr();
	if(sp_uv_expr.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::uv_Constraint::sp_uv_expr");
		throw exp;
	}

	boost::shared_ptr<ROExprImpl> sp_uv_exprI = sp_uv_expr->getImpl();
	if(sp_uv_exprI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::uv_Constraint::sp_uv_exprI");
		throw exp;
	}

	boost::shared_ptr<ROExprMapImpl> sp_uv_mapI = sp_uv_exprI->getMapImpl();
	if(sp_uv_mapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::uv_Constraint::sp_uv_mapI");
		throw exp;
	}

	ROExprMapUnion& ref_uv_map_union = sp_uv_mapI->getUnion();
	ROUnVarImpl* ptr_uv_unVarI = ref_uv_map_union.m_unVarI;
	if(ptr_uv_unVarI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::uv_Constraint::ptr_uv_unVarI");
		throw exp;
	}

	ROUnVarMap& uvMap = ptr_uv_unVarI->getMap();
	// ------------ end ----------

	// Abstraction --- sp_p_vExprI
	boost::shared_ptr<ROExprImpl> sp_p_vExprI = p_vExpr->getImpl();
	if(sp_p_vExprI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::sp_p_vExprI");
		throw exp;
	}

	boost::shared_ptr<ROExprMapImpl> sp_p_vMapI = sp_p_vExprI->getMapImpl();
	if(sp_p_vMapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::sp_p_vMapI");
		throw exp;
	}

	ROExprMapUnion& ref_p_vMap_union = sp_p_vMapI->getUnion();
	ROVarsImpl* ptr_p_v_varsI = ref_p_vMap_union.m_varsI;
	if(ptr_p_v_varsI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decompose::ptr_p_v_varsI");
		throw exp;
	}

	ROVarMap& p_v_varMap = ptr_p_v_varsI->getMap();
	// ------------ end ----------


	ROUnVarMapIter iter = uvMap.begin();

	while(iter != uvMap.end())
	{
		if(iter->first.second == 0 && iter->second != 0)
		{
			p_v_varMap.insert(std::make_pair(ROVarIndex(iter->first.first), iter->second));
		}
		else if(iter->first.first == 0 && iter->second != 0)
		{
			ROUnIndex index(iter->first.second);
			ROUVSubMapIter uIter = p_uvSubMap.find(index);

			// Info
			if(uIter != p_uvSubMap.end())
			{
				boost::shared_ptr<ROExpr> sp_u_v_expr = uIter->second;
				*(sp_u_v_expr.get()) += iter->second;
			}
			else
			{
				boost::shared_ptr<ROExpr> sp_vExpr = boost::shared_ptr<ROExpr>(new ROExpr());
				boost::shared_ptr<ROExprImpl> sp_vExprI = sp_vExpr->getImpl();
				sp_vExprI->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));

				*(sp_vExprI.get()) += iter->second;
				p_uvSubMap.insert(std::make_pair(ROUnIndex(iter->first.second), sp_vExpr));
			}
			//
		}
		else if(iter->second != 0)
		{
			ROUnIndex index(iter->first.second);
			ROUVSubMapIter uIter = p_uvSubMap.find(index);
			if(uIter == p_uvSubMap.end())
			{
				boost::shared_ptr<ROExpr> sp_vExpr = boost::shared_ptr<ROExpr>(new ROExpr());
				boost::shared_ptr<ROExprImpl> sp_vExprI = sp_vExpr->getImpl();
				sp_vExprI->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));

				// Abstraction --- sp_vExprI
				boost::shared_ptr<ROExprMapImpl> sp_vMapI = sp_vExprI->getMapImpl();
				if(sp_vMapI.get() == NULL)
				{
					ROExceptionNullPointer exp("ROModel::decompose::sp_vMapI");
					throw exp;
				}

				ROExprMapUnion& sp_vMap_union = sp_vMapI->getUnion();
				ROVarsImpl* ptr_v_varsI = sp_vMap_union.m_varsI;
				if(ptr_v_varsI == NULL)
				{
					ROExceptionNullPointer exp("ROModel::decompose::ptr_v_varsI");
					throw exp;
				}

				ROVarMap& v_varMap = ptr_v_varsI->getMap();
				// ------------ end ----------


				// Info
				int id_var = iter->first.first;
				double value_var = iter->second;
				//

				v_varMap.insert(std::make_pair(ROVarIndex(id_var), value_var));
				p_uvSubMap.insert(std::make_pair(ROUnIndex(iter->first.second), sp_vExpr));
			}
			else
			{
				// Abstraction --- uIter->second
				boost::shared_ptr<ROExpr> sp_vExpr = uIter->second;
				boost::shared_ptr<ROExprImpl> sp_vExprI = sp_vExpr->getImpl();

				boost::shared_ptr<ROExprMapImpl> sp_vMapI = sp_vExprI->getMapImpl();
				if(sp_vMapI.get() == NULL)
				{
					ROExceptionNullPointer exp("ROModel::decompose::sp_vMapI");
					throw exp;
				}

				ROExprMapUnion& sp_vMap_union = sp_vMapI->getUnion();
				ROVarsImpl* ptr_v_varsI = sp_vMap_union.m_varsI;
				if(ptr_v_varsI == NULL)
				{
					ROExceptionNullPointer exp("ROModel::decompose::ptr_v_varsI");
					throw exp;
				}

				ROVarMap& v_varMap = ptr_v_varsI->getMap();
				// ------------ end ----------

				int id_var = iter->first.first;

				ROVarMapIter iter_var = v_varMap.find(ROVarIndex(id_var));
				if(iter_var != v_varMap.end())
				{
					iter_var->second += iter->second;
				}
				else
				{
					v_varMap.insert(std::make_pair(ROVarIndex(id_var), iter->second));
				}
			}
		}
		iter++;
	}
}

void ROModel::decomposeExpect(const ROConstraint & p_const, boost::shared_ptr<ROExpr> p_expr0, boost::shared_ptr<ROExpr> p_expr1,
		boost::shared_ptr<ROUnLinConstraintArray> unConstArray, boost::shared_ptr<ROUnLinConstraintArray> unExConstArray)
{
	// Abstraction --- sp_ex_bConst
	boost::shared_ptr<ROBaseConstraint> sp_ex_bConst = p_const.getVarConst();
	if(sp_ex_bConst.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::sp_ex_bConst");
		throw exp;
	}

	boost::shared_ptr<ROExpr> sp_ex_expr = sp_ex_bConst->getExpr();
	if(sp_ex_expr.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::sp_ex_expr");
		throw exp;
	}

	boost::shared_ptr<ROExprImpl> sp_ex_exprI = sp_ex_expr->getImpl();
	if(sp_ex_exprI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::sp_ex_exprI");
		throw exp;
	}

	boost::shared_ptr<ROExprMapImpl> sp_ex_mapI = sp_ex_exprI->getMapImpl();
	if(sp_ex_mapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::sp_ex_mapI");
		throw exp;
	}

	ROExprMapUnion& ref_ex_map_union = sp_ex_mapI->getUnion();
	ROExUnVarImpl* ptr_ex_exUnVarI = ref_ex_map_union.m_exUnVarI;
	if(ptr_ex_exUnVarI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::ptr_ex_exUnVarI");
		throw exp;
	}

	ROExUnVarMap& exUnVarMap = ptr_ex_exUnVarI->getMap();
	// ------------ end ----------

	// Abstraction --- sp_p_expr0
	boost::shared_ptr<ROExprImpl> sp_p_expr0_I = p_expr0->getImpl();
	if(sp_p_expr0_I.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::sp_p_expr0_I");
		throw exp;
	}

	boost::shared_ptr<ROExprMapImpl> sp_p_expr0_mapI = sp_p_expr0_I->getMapImpl();
	if(sp_p_expr0_mapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::sp_p_expr0_mapI");
		throw exp;
	}

	ROExprMapUnion& ref_p_expr0_mapU = sp_p_expr0_mapI->getUnion();
	ROVarsImpl* ptr_p_expr0_varsI = ref_p_expr0_mapU.m_varsI;
	if(ptr_p_expr0_varsI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::ptr_p_expr0_varsI");
		throw exp;
	}

	ROVarMap& ptr_p_expr0_varMap = ptr_p_expr0_varsI->getMap();
	// ------------ end ----------

	// Abstraction --- sp_p_expr1
	boost::shared_ptr<ROExprImpl> sp_p_expr1_I = p_expr1->getImpl();
	if(sp_p_expr1_I.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::sp_p_expr1_I");
		throw exp;
	}

	boost::shared_ptr<ROExprMapImpl> sp_p_expr1_mapI = sp_p_expr1_I->getMapImpl();
	if(sp_p_expr1_mapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::sp_p_expr1_mapI");
		throw exp;
	}

	ROExprMapUnion& ref_p_expr1_mapU = sp_p_expr1_mapI->getUnion();
	ROExUnVarImpl* ptr_p_expr1_exUnVarI = ref_p_expr1_mapU.m_exUnVarI;
	if(ptr_p_expr1_exUnVarI == NULL)
	{
		ROExceptionNullPointer exp("ROModel::decomposeExpect::ptr_p_expr1_exUnVarI");
		throw exp;
	}

	ROExUnVarMap& ptr_p_expr1_exUnVarMap = ptr_p_expr1_exUnVarI->getMap();
	// ------------ end ----------


	ROExUnVarMapIter iter = exUnVarMap.begin();

	while(iter != exUnVarMap.end())
	{
		ROKeyIndex2 index_uv = iter->first;
		ROKeyValue2 value_ex = iter->second;

		if(index_uv.second == 0)
		{
			ptr_p_expr0_varMap.insert(std::make_pair(ROVarIndex(index_uv.first), value_ex.first));
		}
		else
		{
			ptr_p_expr1_exUnVarMap.insert(std::make_pair(ROKeyIndex2(index_uv), value_ex));
		}
		iter++;
	}

	// Abstraction --- sp_ex_bUnConstArray
	boost::shared_ptr<ROUnLinConstraintArray> sp_ex_bConstArray = p_const.getUnConstArray();
	size_t size_bConstArray = sp_ex_bConstArray->getSize();

	for(unsigned int i = 0; i < size_bConstArray; i++)
	{
		ROUnLinConstraint& bConst_i = (*(sp_ex_bConstArray.get()))[i];

		// Abstraction --- bConst_i
		boost::shared_ptr<ROExpr> sp_expr_i = bConst_i.getExpr();
		if(sp_expr_i.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::decomposeExpect::bConstraintArray::sp_expr_i");
			throw exp;
		}

		boost::shared_ptr<ROExprImpl> sp_exprI_i = sp_expr_i->getImpl();
		if(sp_exprI_i.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::decomposeExpect::uv_Constraint::sp_exprI_i");
			throw exp;
		}

		ROExprType expr_i_type = sp_exprI_i->getType();

		if(expr_i_type == EnumUn)
		{
			unConstArray->add(bConst_i);
		}
		else
		{
			unExConstArray->add(bConst_i);
		}
	}

}

void ROModel::lpSolve()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART I -- variables definition
	ROVarImplManager& ref_varI_manager =  ROVarImplManager::instance();

	ROVarIMap& ref_varIMap = ref_varI_manager.getMap();
	VarMapIterator iter_varIMap;

	LPVarArray& m_vec_lpVar = *m_p_vec_lpVar.get();

	/*
	 * Modified on 05-Apr-3013, for fixing the bug of memory leak in ROVarImplManager
	 */
	for(int i = 0; i < ROVar::getNo(); i++)
	{
		if(ref_varI_manager.findId(i))
		{
			iter_varIMap = ref_varIMap.find(i);
			boost::shared_ptr<ROVarImpl> sp_varI = iter_varIMap->second;
			const long double v_lb = sp_varI->getLB();
			const long double v_ub = sp_varI->getUB();
			const ROVarType v_type = sp_varI->getType();
			std::string v_name = sp_varI->getName();

			// add variable ID into its name setting
			ostringstream os;
			os << v_name << "[" << i << "]";

			//-----------------end-------------------
			
			m_vec_lpVar.add(m_lpFactory->createVar(v_lb, v_ub, os.str().c_str(), v_type));
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART II -- constraint definition
	std::list< boost::shared_ptr<ROBaseConstraint> >::iterator iter;

	for(iter = m_baseConst.begin(); iter != m_baseConst.end(); iter++)
	{
		ROConstTag const_tag = (*iter)->getTag();
		boost::shared_ptr<ROExpr> sp_expr = (*iter)->getExpr();

		// Abstractiong --- expr
		boost::shared_ptr<ROExprImpl> sp_exprI = sp_expr->getImpl();
		if(sp_exprI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::lpSolve::sp_exprI");
			throw exp;
		}
		boost::shared_ptr<ROExprMapImpl> sp_expr_mapI = sp_exprI->getMapImpl();
		if(sp_expr_mapI.get() == NULL)
		{
			ROExceptionNullPointer exp("ROModel::lpSolve::sp_expr_mapI");
			throw exp;
		}
		ROExprMapUnion& ref_expr_mapU = sp_expr_mapI->getUnion();
		// ---------- end --------

		ROExprType type = sp_expr_mapI->getType();

		if(type == EnumVar)
		{
			ROVarsImpl* ptr_expr_varsI = ref_expr_mapU.m_varsI;
			if(ptr_expr_varsI == NULL)
			{
				ROExceptionNullPointer exp("ROModel::lpSolve::ptr_expr_varsI");
				throw exp;
			}
			ROVarMap& ref_expr_varMap = ptr_expr_varsI->getMap();

			ROVarMapIter iter_varMap;
			
			boost::shared_ptr<Expr<TYPE> > expr = m_lpFactory->createExpr();

			*(expr.get()) += sp_exprI->getNum();

			for(iter_varMap = ref_expr_varMap.begin(); iter_varMap != ref_expr_varMap.end(); iter_varMap++)
			{
				ROVarIndex id = iter_varMap->first;
				double val = iter_varMap->second;

				//Info
				boost::shared_ptr<Var<TYPE> > sp_var_test = m_vec_lpVar[id-1];
				if(sp_var_test.get() == NULL)
				{
					std::cout << "NULL pointer : sp_var_test" << std::endl;
				}
				//

				*(expr.get()) += *((m_vec_lpVar[id-1]).get()) * val;
			}

			if(const_tag == EnumEq)
			{
				m_lpModel->addConstraint(*(expr.get()) == 0);
			}
			else
			{
				m_lpModel->addConstraint(*(expr.get()) <= 0);
			}
		}
		else if(type == EnumQVar)
		{
			ROQVarImpl* ptr_expr_qVarI = ref_expr_mapU.m_qVarI;
			if(ptr_expr_qVarI == NULL)
			{
				ROExceptionNullPointer exp("ROModel::lpSolve::ptr_expr_qVarI");
				throw exp;
			}
			ROQVarMap& ref_expr_qVarMap = ptr_expr_qVarI->getMap();

			ROQVarMapIter iter_qVarMap;
			
			boost::shared_ptr<Expr<TYPE> > expr = m_lpFactory->createExpr();

			*(expr.get()) += sp_exprI->getNum();

			for(iter_qVarMap = ref_expr_qVarMap.begin(); iter_qVarMap != ref_expr_qVarMap.end(); iter_qVarMap++)
			{
				ROKeyIndex2 index = iter_qVarMap->first;
				int idL = index.first;
				int idR = index.second;
				double val = iter_qVarMap->second;

				if(idR == 0)
				{
					*(expr.get()) += (*((m_vec_lpVar[idL - 1]).get())) * val;
				}
				else
				{
					*(expr.get()) += (*((m_vec_lpVar[idL - 1]).get())) * (*((m_vec_lpVar[idR - 1]).get()))  * val;
				}
			}

			if(const_tag == EnumEq)
			{
				m_lpModel->addConstraint(*(expr.get()) == 0);
			}
			else
			{
				m_lpModel->addConstraint(*(expr.get()) <= 0);
			}
		}
		else
		{
			ROExceptionIncompatibleExpr exp("ROModel::lpSolve::constraintType incompatible");
			throw exp;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART III -- objective definition
	//
	boost::shared_ptr<ROExpr> sp_obj_expr = m_obj->getExpr();
	ROObjectiveTag obj_tag = m_obj->getTag();

	// Abstractiong --- obj_expr
	boost::shared_ptr<ROExprImpl> sp_obj_exprI = sp_obj_expr->getImpl();
	if(sp_obj_exprI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::lpSolve::sp_obj_exprI");
		throw exp;
	}
	boost::shared_ptr<ROExprMapImpl> sp_obj_expr_mapI = sp_obj_exprI->getMapImpl();
	if(sp_obj_expr_mapI.get() == NULL)
	{
		ROExceptionNullPointer exp("ROModel::lpSolve::sp_obj_expr_mapI");
		throw exp;
	}
	ROExprMapUnion& ref_obj_expr_mapU = sp_obj_expr_mapI->getUnion();
	// ---------- end --------

	ROExprType obj_expr_type = sp_obj_expr_mapI->getType();
	
	if(obj_expr_type == EnumVar)
	{
		ROVarsImpl* ptr_obj_expr_varsI = ref_obj_expr_mapU.m_varsI;
		if(ptr_obj_expr_varsI == NULL)
		{
			ROExceptionNullPointer exp("ROModel::lpSolve::ptr_obj_expr_varsI");
			throw exp;
		}
		ROVarMap& ref_obj_expr_varMap = ptr_obj_expr_varsI->getMap();

		ROVarMapIter iter_obj_varMap;
			
		boost::shared_ptr<Expr<TYPE> > obj_lp_expr = m_lpFactory->createExpr();

		*(obj_lp_expr.get()) += sp_obj_exprI->getNum();

		for(iter_obj_varMap = ref_obj_expr_varMap.begin(); iter_obj_varMap != ref_obj_expr_varMap.end(); iter_obj_varMap++)
		{
			ROVarIndex id = iter_obj_varMap->first;
			double val = iter_obj_varMap->second;

			*(obj_lp_expr.get()) += *((m_vec_lpVar[id-1]).get()) * val;
		}

		if(obj_tag == EnumMax)
		{
			m_lpModel->addObjective(Maximize(*(obj_lp_expr.get())));
		}
		else if(obj_tag == EnumMin)
		{
			m_lpModel->addObjective(Minimize(*(obj_lp_expr.get())));
		}
	}
	else if(obj_expr_type == EnumQVar)
	{
		ROQVarImpl* ptr_obj_expr_qVarI = ref_obj_expr_mapU.m_qVarI;
		if(ptr_obj_expr_qVarI == NULL)
		{
			ROExceptionNullPointer exp("ROModel::lpSolve::ptr_obj_expr_qVarI");
			throw exp;
		}
		ROQVarMap& ref_obj_expr_qVarMap = ptr_obj_expr_qVarI->getMap();

		ROQVarMapIter iter_obj_qVarMap;
			
		boost::shared_ptr<Expr<TYPE> > obj_lp_expr = m_lpFactory->createExpr();

		*(obj_lp_expr.get()) += sp_obj_exprI->getNum();

		for(iter_obj_qVarMap = ref_obj_expr_qVarMap.begin(); iter_obj_qVarMap != ref_obj_expr_qVarMap.end(); iter_obj_qVarMap++)
		{
			ROKeyIndex2 index = iter_obj_qVarMap->first;
			int idL = index.first;
			int idR = index.second;
			double val = iter_obj_qVarMap->second;

			if(idR == 0)
			{
				*(obj_lp_expr.get()) += (*((m_vec_lpVar[idL - 1]).get())) * val;
			}
			else
			{
				*(obj_lp_expr.get()) += (*((m_vec_lpVar[idL - 1]).get())) * (*((m_vec_lpVar[idR - 1]).get()))  * val;
			}
		}

		if(obj_tag == EnumMax)
		{
			m_lpModel->addObjective(Maximize(*(obj_lp_expr.get())));
		}
		else
		{
			m_lpModel->addObjective(Minimize(*(obj_lp_expr.get())));
		}
	}
	else
	{
		ROExceptionIncompatibleExpr exp("ROModel::lpSolve::objectiveType incompatible");
		throw exp;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PART IV -- Model Solve
	//

	m_lpModel->solve();
}

ROModel::~ROModel()
{
	ROUn::resetUniqueId();
	ROVar::resetUniqueId();
	ROVarImplManager::instance().clear();
	ROUnImplManager::instance().clear();
}
