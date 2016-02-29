//
//  ROVarImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 27/8/12.
//  Added by Tianjue Lin on 28/8/12
//
//

#ifndef RobustOptimizationSolver_ROVarImpl_h
#define RobustOptimizationSolver_ROVarImpl_h

#include "ROTypedefs.h"

class ROVarImpl
{
public:
    ROVarImpl(const int p_id, const double p_lb, const double p_ub, const std::string& p_name, const ROVarType p_type);
    
    int getId() const { return m_id; }
    double getLB() const { return m_lb; }
    double getUB() const { return m_ub; }
	ROVarType getType() const { return m_type;}
    std::string getName() const { return m_name;}
    
    void setName(const std::string& p_name) { m_name = p_name; }
    
private:
    int m_id;
    double m_lb;
    double m_ub;
	ROVarType m_type;
    std::string m_name;
};

typedef boost::unordered_map<int, boost::shared_ptr<ROVarImpl> > ROVarIMap;
typedef boost::unordered_map<int, boost::shared_ptr<ROVarImpl> >::iterator VarMapIterator;

class ROVarImplManager
{
public:
    static ROVarImplManager& instance();
	static void destroy();
    void add(const boost::shared_ptr<ROVarImpl> p_impl);
    bool findId(const int p_id);
	void remove(const int id);
    
    ROVarIMap& getMap();

	void clear();

private:
    static ROVarImplManager* m_instance;
    ROVarIMap m_varMap;

};

#endif
