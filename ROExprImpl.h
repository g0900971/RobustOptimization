//
//  ROExprImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 26/8/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROExprImpl_h
#define RobustOptimizationSolver_ROExprImpl_h

#include "ROTypedefs.h"
#include "roexceptions.h"

enum ROExprType {EnumNull, EnumVar, EnumUn, EnumQVar, EnumExUn, EnumUnVar, EnumExUnVar};

class ROVarsImpl;
class ROUnsImpl;
class ROUnVarImpl;
class ROQVarImpl;
class ROExUnImpl;
class ROUnVarImpl;
class ROExUnVarImpl;


union ROExprMapUnion
{
    ROVarsImpl* m_varsI;
    ROUnsImpl* m_unsI;
	ROUnVarImpl* m_unVarI;
    ROQVarImpl* m_qVarI;
    ROExUnImpl* m_exUnI;
    ROExUnVarImpl* m_exUnVarI;
};

class ROExprMapImpl
{
public:
    ROExprMapImpl(ROExprType p_type);
    ROExprType getType() const;
    ROExprMapUnion& getUnion();

    ~ROExprMapImpl();
    
private:
    ROExprType m_type;
    ROExprMapUnion m_exprMapUnion;
};


class ROExprImpl
{
public:
    ROExprImpl();

	int getId() const;
    
    ROExprType getType() const;
	RONum getNum() const;
    boost::shared_ptr<ROExprMapImpl> getMapImpl() const;
	void setMapImpl(boost::shared_ptr<ROExprMapImpl> p_mapI);
    
    ROExprImpl& operator += (RONum p_val);
    ROExprImpl& operator -= (RONum p_val);
    ROExprImpl& operator *= (RONum p_val);
    ROExprImpl& operator /= (RONum p_val);
    
    ROExprImpl& operator += (const ROVar& p_var);
	ROExprImpl& operator -= (const ROVar& p_var);

	ROExprImpl& operator += (const ROUn& p_un);
	ROExprImpl& operator -= (const ROUn& p_un);

	ROExprImpl& operator *= (const ROVar& p_var);
	ROExprImpl& operator *= (const ROUn& p_un);

	ROExprImpl& operator += (const ROExprImpl& p_exprI);
	ROExprImpl& operator -= (const ROExprImpl& p_exprI);

	ROExprImpl& operator *= (const ROExprImpl& p_exprI);

	ROExprImpl& expect(const ROUn& p_un);
	ROExprImpl& expect(const ROExprImpl& p_exprI);

	~ROExprImpl();

private:
	boost::shared_ptr<ROExprMapImpl> m_exprMapImpl;
    RONum m_val;

	int m_ID;
	static int generateUniqueId();
    static int UniqueId;
    
};

#endif
