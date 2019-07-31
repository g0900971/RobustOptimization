//
//  ROVarDRImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 24/10/12.
//
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROVarDRImpl_h
#define RobustOptimizationSolver_ROVarDRImpl_h

#include "ROTypedefs.h"
#include "ROExpr.h"
#include "ROUn.h"
#include "ROExprImpl.h"

struct ROVarDRHash
{
	std::size_t operator() (const boost::shared_ptr<ROExpr> &px) const
	{
		const ROExpr& x = *px.get();
		boost::hash<int> h;
		
		return h(x.getImpl()->getId());
	}

};

struct ROVarDREqualTo
{
	bool operator() (const boost::shared_ptr<ROExpr> &pa, const boost::shared_ptr<ROExpr> &pb) const
	{
		const ROExpr& a = *pa.get();
		const ROExpr& b = *pb.get();

		return(a.getImpl() == b.getImpl());
	}
};

struct ROVarDRUnHash
{
	std::size_t operator() (const boost::shared_ptr<ROUn> &px) const
	{
		const ROUn& x = *px.get();
		boost::hash<int> h;
		
		return h(x.getId());
	}

};

struct ROVarDRUnEqualTo
{
	bool operator() (const boost::shared_ptr<ROUn> &pa, const boost::shared_ptr<ROUn> &pb) const
	{
		const ROUn& a = *pa.get();
		const ROUn& b = *pb.get();

		return(a.getId() == b.getId());
	}
};
/*
typedef boost::unordered_map<boost::shared_ptr<ROVar>, boost::shared_ptr<ROExpr> > VarDRMap;
typedef boost::unordered_map<boost::shared_ptr<ROVar>, boost::shared_ptr<ROExpr> >::iterator VarDRIter;
*/
typedef boost::unordered_map<boost::shared_ptr<ROExpr>, boost::shared_ptr<ROVar>, ROVarDRHash, ROVarDREqualTo > ReVarDRMap;
typedef boost::unordered_map<boost::shared_ptr<ROExpr>, boost::shared_ptr<ROVar>, ROVarDRHash, ROVarDREqualTo >::iterator ReVarDRIter;
/*
typedef boost::unordered_map<boost::shared_ptr<ROVar>, boost::shared_ptr<ROUn> > VarDRUnMap;
typedef boost::unordered_map<boost::shared_ptr<ROVar>, boost::shared_ptr<ROUn> >::iterator VarDRUnIter;
*/
typedef boost::unordered_map<boost::shared_ptr<ROUn>, boost::shared_ptr<ROVar>, ROVarDRUnHash, ROVarDRUnEqualTo> ReVarDRUnMap;
typedef boost::unordered_map<boost::shared_ptr<ROUn>, boost::shared_ptr<ROVar>, ROVarDRUnHash, ROVarDRUnEqualTo>::iterator ReVarDRUnIter;

class ROVarDRImpl
{
public:
	ROVarDRImpl();

	ROExpr getExpr();

	// --- Given expression to derive the mapping variable 
	ROVar& getVar(ROExpr&) const;
	ROVar& getVar(ROUn&) const;
	ROVar& getVar() const;
	// --- End ---

	// --- Clone decision rule from other decision rule variables
	ReVarDRMap& getReVarDRMap();
	ReVarDRUnMap& getReVarDRUnMap();
	// --- End ---

	void add(ROExpr&);
	void add(ROUn&);

	void add(boost::shared_ptr<ROVarDRImpl> sp_DRImpl);

private:
	//VarDRMap m_varDRMap;

	// --- Double Map Mapping ---
	ReVarDRMap m_varDRMapReverse;
	//VarDRUnMap m_varDRUnMap;
	ReVarDRUnMap m_varDRUnMapReverse;
	// --- End ---

	// Eg. Y_DR_0 without uncertainty involved
	boost::shared_ptr<ROVar> m_sp_var_Z;

};

#endif