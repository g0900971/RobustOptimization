//
//  ROUnImpl.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 28/8/12.
//
//

#ifndef RobustOptimizationSolver_ROUnImpl_h
#define RobustOptimizationSolver_ROUnImpl_h

#include "ROTypedefs.h"

class ROUnImpl
{
public:
    ROUnImpl(const int p_id);
    int getId() const { return m_id; }
    
private:
    int m_id;
    
};

typedef boost::unordered_map<int, boost::shared_ptr<ROUnImpl> > ROUnIMap;
typedef boost::unordered_map<int, boost::shared_ptr<ROUnImpl> >::iterator UnMapIterator;

class ROUnImplManager
{
public:
    static ROUnImplManager& instance();
	static void destroy();
    void add(const boost::shared_ptr<ROUnImpl> p_impl);
    void remove(const int p_id);
    
    bool findId(const int p_id);

	ROUnIMap& getMap();

	void clear();
    
private:
    static ROUnImplManager* m_instance;
    ROUnIMap m_unMap;
};

#endif
