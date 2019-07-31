//
//  lptemplate.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 19/9/12.
//  Copyright (c) 2012 __Shaman__. All rights reserved.
//

#ifndef RobustOptimizationSolver_lptemplate_h
#define RobustOptimizationSolver_lptemplate_h

#include <ilcplex/ilocplex.h>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include "ROTypedefs.h"
#include "ROArrayTemplate.h"

typedef double LPNum;

template<class T>
class Var;

template<class T>
class Expr
{
public:
	Expr<T>& operator +=(LPNum);
	Expr<T>& operator +=(const Var<T>&);
	Expr<T>& operator +=(const Expr<T>&);

	Expr<T>& operator -=(LPNum);
	Expr<T>& operator -=(const Var<T>&);
	Expr<T>& operator -=(const Expr<T>&);

	Expr<T>& operator *=(LPNum);
	Expr<T>& operator *=(const Var<T>&);
	Expr<T>& operator *=(const Expr<T>&);

	Expr<T>& operator /=(LPNum);

};

template<class T>
class Objective;

template<class T>
class Constraint;

template<class T>
class Model
{
public:
	void add(boost::shared_ptr<Constraint<T> > p_sp_const);
	void add(boost::shared_ptr<Objective<T> > p_sp_const);

	void solve();
	std::string getStatus();
};

template<class T>
class Factory
{
public:
	boost::shared_ptr<Model<T> > createModel();
	boost::shared_ptr<Var<T> > createVar(LPNum, LPNum, const char*);
	//boost::shared_ptr<VarArray<T> > createVarArray();
	boost::shared_ptr<Expr<T> > createExpr();
	boost::shared_ptr<Objective<T> > createObjective();
	boost::shared_ptr<Constraint<T> > createConstraint();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// related to expr  + - / *

template<class T>
Expr<T> operator + (LPNum, const Var<T>&);

template<class T>
Expr<T> operator + (const Var<T>&, LPNum);
//

template<class T>
Expr<T> operator - (LPNum, const Var<T>&);

template<class T>
Expr<T> operator - (const Var<T>&, LPNum);
//

template<class T>
Expr<T> operator * (LPNum, const Var<T>&);

template<class T>
Expr<T> operator * (const Var<T>&, LPNum);
//

template<class T>
Expr<T> operator * (LPNum, const Expr<T>&);

template<class T>
Expr<T> operator * (const Expr<T>&, LPNum);
//

template<class T>
Expr<T> operator / (const Var<T>&, LPNum);

template<class T>
Expr<T> operator / (const Expr<T>&, LPNum);
//

template<class T>
Expr<T> operator + (const Var<T>&, const Var<T>&);

template<class T>
Expr<T> operator - (const Var<T>&, const Var<T>&);
//

template<class T>
Expr<T> operator + (LPNum, const Expr<T>&);

template<class T>
Expr<T> operator + (const Expr<T>&, LPNum);

template<class T>
Expr<T> operator - (LPNum, const Expr<T>&);

template<class T>
Expr<T> operator - (const Expr<T>&, LPNum);
//

template<class T>
Expr<T> operator + (const Var<T>&, const Expr<T>&);

template<class T>
Expr<T> operator + (const Expr<T>&, const Var<T>&);

template<class T>
Expr<T> operator - (const Var<T>&, const Expr<T>&);

template<class T>
Expr<T> operator - (const Expr<T>&, const Var<T>&);
//

template<class T>
Expr<T> operator + (const Expr<T>&, const Expr<T>&);

template<class T>
Expr<T> operator - (const Expr<T>&, const Expr<T>&);
//

template<class T>
Expr<T> operator * (const Var<T>&, const Var<T>&);

template<class T>
Expr<T> operator * (const Expr<T>&, const Var<T>&);

template<class T>
Expr<T> operator * (const Var<T>&, const Expr<T>&);

template<class T>
Expr<T> operator * (const Expr<T>&, const Expr<T>&);
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Objective Function
template<class T>
Objective<T> Minimize(const Expr<T>& p_expr);

template<class T>
Objective<T> Maximize(const Expr<T>& p_expr);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	 Constraints Operations
// 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// "<=" "<=" "=="

template<class T>
Constraint<T> operator <= (LPNum lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator <= (const Var<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator <= (LPNum lhs, const Expr<T>& rhs);

template<class T>
Constraint<T> operator <= (const Expr<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator <= (const Expr<T>& lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator <= (const Var<T>& lhs, const Expr<T>& rhs);


template<class T>
Constraint<T> operator <= (const Expr<T>& lhs, const Expr<T>& rhs);


// " >= " 
template<class T>
Constraint<T> operator >= (LPNum lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator >= (const Var<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator >= (LPNum lhs, const Expr<T>& rhs);

template<class T>
Constraint<T> operator >= (const Expr<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator >= (const Expr<T>& lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator >= (const Var<T>& lhs, const Expr<T>& rhs);


template<class T>
Constraint<T> operator >= (const Expr<T>& lhs, const Expr<T>& rhs);

// " == "
template<class T>
Constraint<T> operator == (LPNum lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator == (const Var<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator == (LPNum lhs, const Expr<T>& rhs);

template<class T>
Constraint<T> operator == (const Expr<T>& lhs, LPNum rhs);


template<class T>
Constraint<T> operator == (const Expr<T>& lhs, const Var<T>& rhs);

template<class T>
Constraint<T> operator == (const Var<T>& lhs, const Expr<T>& rhs);


template<class T>
Constraint<T> operator == (const Expr<T>& lhs, const Expr<T>& rhs);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Template Secialization for CPLEX

class CPLEX
{
public:
	typedef IloNumVar::Type VarType;
};
typedef CPLEX::VarType CPLEX_VAR_TYPE;


//class MOSEK;

template<>
class Var<CPLEX>
{
public:
	Var(IloEnv& p_env, LPNum p_lb = -IloInfinity, LPNum p_ub = IloInfinity, const char* p_name=0, IloNumVar::Type type = IloNumVar::Type::Float):
	  m_env(p_env)
	{
		m_sp_var = boost::shared_ptr<IloNumVar>(new IloNumVar(p_env, p_lb, p_ub, type, p_name));
	}

	boost::shared_ptr<IloNumVar> getVar() const
	{
		return m_sp_var;
	}

	IloEnv& getEnv() const
	{
		return m_env;
	}

private:
	boost::shared_ptr<IloNumVar> m_sp_var;
	IloEnv& m_env;
};

class LPVarArray: public ROArray<boost::shared_ptr<Var<CPLEX> > >
{
public:
};

template<>
class Expr<CPLEX>
{
public:
	Expr(IloEnv& p_env):
	  m_env(p_env)
	{
		m_sp_expr = boost::shared_ptr<IloExpr>(new IloExpr(p_env));
	}

	Expr(const Expr& p_expr):
	  m_env(p_expr.getEnv()),
	  m_sp_expr(p_expr.getExpr())
	{

	}

	Expr& operator = (const Expr& p_expr)
	{
		if(this != &p_expr)
		{
			m_sp_expr = p_expr.getExpr();
		}
		return *this;
	}

	boost::shared_ptr<IloExpr> getExpr() const
	{
		return m_sp_expr;
	}

	void setExpr(boost::shared_ptr<IloExpr> p_sp_expr)
	{
		m_sp_expr = p_sp_expr;
	}

	IloEnv& getEnv() const
	{
		return m_env;
	}

	Expr& operator +=(LPNum p_val)
	{
		*(m_sp_expr.get()) += p_val;
		return *this;
	}

	Expr& operator +=(const Var<CPLEX>& p_var)
	{
		*(m_sp_expr.get()) += *(p_var.getVar().get());
		return *this;
	}

	Expr& operator +=(const Expr<CPLEX>& p_expr)
	{
		*(m_sp_expr.get()) += *(p_expr.getExpr().get());
		return *this;
	}


	Expr& operator -=(LPNum p_val)
	{
		*(m_sp_expr.get()) += p_val;
		return *this;
	}

	Expr& operator -=(const Var<CPLEX>& p_var)
	{
		*(m_sp_expr.get()) -= *(p_var.getVar().get());
		return *this;
	}

	Expr& operator -=(const Expr<CPLEX>& p_expr)
	{
		*(m_sp_expr.get()) -= *(p_expr.getExpr().get());
		return *this;
	}


	Expr& operator *=(LPNum p_val)
	{
		*(m_sp_expr.get()) *= p_val;
		return *this;
	}

	Expr& operator /=(LPNum p_val)
	{
		*(m_sp_expr.get()) /= p_val;
		return *this;
	}

private:
	boost::shared_ptr<IloExpr> m_sp_expr;
	IloEnv& m_env;
};


template<>
class Objective<CPLEX>
{
public:
	Objective(IloEnv& p_env):
	  m_env(p_env)
	{
		m_sp_obj = boost::shared_ptr<IloObjective>(new IloObjective(p_env));
	}

	Objective(const Objective& p_objective):
	  m_env(p_objective.getEnv()),
	  m_sp_obj(p_objective.getObjective())
	{
		
	}

	Objective& operator = (const Objective& p_obj)
	{
		if(this != &p_obj)
		{
			m_env = p_obj.getEnv();
			m_sp_obj = p_obj.getObjective();
		}
		return *this;
	}

	boost::shared_ptr<IloObjective> getObjective() const
	{
		return m_sp_obj;
	}

	void setObjective(boost::shared_ptr<IloObjective> p_sp_obj)
	{
		m_sp_obj = p_sp_obj;
	}

	IloEnv& getEnv() const
	{
		return m_env;
	}

	void setExpr(Expr<CPLEX>& p_expr)
	{
		(*(m_sp_obj.get())).setExpr(*(p_expr.getExpr().get()));
	}

private:
	boost::shared_ptr<IloObjective> m_sp_obj;
	IloEnv& m_env;
};


template<>
class Constraint<CPLEX>
{
public:
	Constraint()
	{

	}

	Constraint(const Constraint& p_constraint):
	  m_sp_const(p_constraint.getConstraint())
	{
		
	}

	Constraint& operator = (const Constraint& p_const)
	{
		if(this != &p_const)
		{
			m_sp_const = p_const.getConstraint();
		}
		return *this;
	}

	boost::shared_ptr<IloConstraint> getConstraint() const
	{
		return m_sp_const;
	}

	void setConstraint(boost::shared_ptr<IloConstraint> p_sp_const)
	{
		m_sp_const = p_sp_const;
	}

private:
	boost::shared_ptr<IloConstraint> m_sp_const;
};


template<>
class Model<CPLEX>
{
public:
	Model(IloEnv& p_env):
	  m_solved(false)
	{
		m_sp_model = boost::shared_ptr<IloModel>(new IloModel(p_env));
		m_sp_cplex = boost::shared_ptr<IloCplex>(new IloCplex(*(m_sp_model.get())));
	}

	boost::shared_ptr<IloModel> getModel() const
	{
		return m_sp_model;
	}

	void addConstraint(const Constraint<CPLEX> p_const)
	{
		m_sp_model->add(*(p_const.getConstraint().get()));
	}

	void addObjective(const Objective<CPLEX> p_obj)
	{
		m_sp_model->add(*(p_obj.getObjective().get()));
	}

	void solve()
	{
		m_sp_cplex->setOut(m_sp_model->getEnv().getNullStream());
		m_sp_cplex->setWarning(m_sp_model->getEnv().getNullStream());

		try{
			m_sp_cplex->solve();
		}
		catch(IloException& exp)
		{
			std::cerr << "Error: " << exp << std::endl;
		}
		m_solved = true;
	}

	std::string getStatus()
	{
		std::string status;
		switch (m_sp_cplex->getStatus())
		{
			case IloAlgorithm::Unknown:
				status = "Unknown";
				break;
			case IloAlgorithm::Feasible:
				status = "Feasible";
				break;
			case IloAlgorithm::Optimal:
				status = "Optimal";
				break;
			case IloAlgorithm::Infeasible:
				status = "Infeasible";
				break;
			case IloAlgorithm::Unbounded:
				status = "Unbounded";
				break;
			case IloAlgorithm::InfeasibleOrUnbounded:
				status = "InfeasibleOrUnbounded";
				break;
			case IloAlgorithm::Error:
				status = "Error";
				break;
		}
		return status;
	}

	double getObjValue()
	{
		try{
		if(m_solved)
		{
			return m_sp_cplex->getObjValue();
		}
		else
		{
			ROExceptionModelUnsolve exp("model unsolved");
			throw exp;
		}
		}
		catch(IloException& exp)
		{
			std::cerr << "Error: " << exp << std::endl;
		}
		return -1;
	}

	double getVarValue(Var<CPLEX>& p_sp_var)
	{
		if(m_solved)
		{
			IloNum varValue = m_sp_cplex->getValue((*(p_sp_var.getVar().get())));
			return varValue;
		}
		else
		{
			ROExceptionModelUnsolve exp("model unsolved");
			throw exp;
		}
	}

	void exportModel()
	{
		m_sp_cplex->exportModel("Model.lp");
	}

	void exportModel(std::string& p_dirPath)
	{
		std::string fullPath = p_dirPath + "\\Model.lp";
		m_sp_cplex->exportModel(fullPath.c_str());
	}

private:
	boost::shared_ptr<IloModel> m_sp_model;
	boost::shared_ptr<IloCplex> m_sp_cplex;

	bool m_solved;
	double m_objValue;

};

template<class T, class LPVarType>
class LPUtils
{
public:
	static LPVarType ROVarType2LPType(const ROVarType type);
};

template<>
class LPUtils<CPLEX, CPLEX_VAR_TYPE> {
public:
    static CPLEX_VAR_TYPE ROVarType2LPType(const ROVarType type) {
        switch (type) {
            case EnumROVar:
                return CPLEX_VAR_TYPE::Float;

            case EnumROInt:
                return CPLEX_VAR_TYPE::Int;

            case EnumROBool:
                return CPLEX_VAR_TYPE::Bool;

            default:
                return CPLEX_VAR_TYPE::Float;
        }
    }
};

template<>
class Factory<CPLEX>
{
public:
	Factory()
	{

	}

	boost::shared_ptr<Model<CPLEX>  > createModel()
	{
		return boost::shared_ptr<Model<CPLEX>  >(new Model<CPLEX>(m_env));
	}

	boost::shared_ptr<Var<CPLEX>  > createVar(LPNum p_lb = -IloInfinity, LPNum p_ub = IloInfinity, 
		const char* p_name=0, const ROVarType p_type = EnumROVar)
	{	
		return boost::shared_ptr<Var<CPLEX>  >(new Var<CPLEX>(m_env,  p_lb, p_ub, p_name, LPUtils<CPLEX, CPLEX_VAR_TYPE>::ROVarType2LPType(p_type)));
	}

	boost::shared_ptr<Expr<CPLEX>  > createExpr()
	{
		return boost::shared_ptr<Expr<CPLEX>  >(new Expr<CPLEX>(m_env));
	}

	IloEnv& getEnv()
	{
		return m_env;
	}

	~Factory()
	{
		m_env.end();
	}

private:
	IloEnv m_env;
};

#endif
