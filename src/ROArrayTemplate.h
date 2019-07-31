#ifndef _RO_ARRAY_TEMPLATE_H_
#define _RO_ARRAY_TEMPLATE_H_

#include "ROTypedefs.h"

template<class X>
class ROArray
{
public:
    ROArray()
    {
        
    }

    ROArray(const ROArray &roa)
    {
		for(int i = 0; i < roa.getSize(); i++)
		{
			
			m_array.push_back(roa[i]);
		}
    }
    
    ROArray(size_t size)
    {
//        m_array.reserve(size);
		for(size_t i = 0; i < size; i++)
		{
			X x;
			m_array.push_back(x);
		}
    }
    
    void add(const X &x)
    {
        m_array.push_back(x);
    }
    
	X operator[](size_t i) const
	{
        if(i < 0 || i > m_array.size())
        {
			ROExceptionOutRange exp;
            throw exp;
        }
        return m_array[i];
	}

    X& operator[] (size_t i)
    {
        if(i < 0 || i > m_array.size())
        {
			ROExceptionOutRange exp;
            throw exp;
        }
        return m_array[i];
    }

	size_t getSize() const
	{
		return m_array.size();
	}

	ROArray<X>& operator=(const ROArray<X>& p_array)
	{
		if(this == &p_array)
		{
			return *this;
		}
		else
		{
			m_array.clear();
			m_array.reserve(p_array.getSize());
			m_array = p_array.m_array;
			return *this;
		}
	}

private:
    std::vector<X> m_array;
};

template<class X>
class ROVArray
{
public:
    ROVArray()
    {
        
    }
    
	ROVArray(const ROVArray &roa)
    {
		for(int i = 0; i < roa.getSize(); i++)
		{
			
			m_array.push_back(roa[i]);
		}
    }

    ROVArray(const int size, const RONum lb = RONInfinity, const RONum ub = ROInfinity,  
			 const std::string& name = "", const ROVarType p_type = EnumROVar)
    {
        m_array.reserve(size);
		for(int i = 0; i < size; i++)
		{
			X x(lb, ub, name, p_type);
			m_array.push_back(x);
		}
    }
    
    ROVArray(const int size, const int* lb, const int* ub, const std::string& name = "", 
			 const ROVarType p_type = EnumROVar)
    {
        m_array.reserve(size);
		for(int i = 0; i < size; i++)
		{
			X x(lb[i], ub[i], name, p_type);
			m_array[i] = x;
		}
    }
    
    void add(const X &x)
    {
        m_array.push_back(x);
    }
    
    X operator[] (int i) const
    {
        if(i < 0 || i > m_array.size())
        {
			ROExceptionOutRange exp;
            throw exp;
        }
        return m_array[i];
    }

    X& operator[] (int i)
    {
        if(i < 0 || i > m_array.size())
        {
			ROExceptionOutRange exp;
            throw exp;
        }
        return m_array[i];
    }

	size_t getSize() const
	{
		return m_array.size();
	}
    
private:
    std::vector<X> m_array;
};



typedef ROVArray<ROVar> ROVarArray;
typedef ROArray<ROVarArray> ROVar2DArray;
typedef ROArray<ROUn> ROUnArray;
typedef ROArray<ROConstraint> ROConstraintArray;
typedef ROArray<ROVarDR> ROVarDRArray;
typedef ROArray<ROExpr> ROExprArray;

typedef ROArray<ROInt> ROIntArray;
typedef ROArray<RONum> RONumArray;

typedef ROVArray<LPNumVar> LPNumVarArray;

#endif