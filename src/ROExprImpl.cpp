//
//  ROExprImpl.cpp
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 29/8/12.
//
//

#include "ROExprImpl.h"
#include "ROVar.h"
#include "ROUn.h"
#include "ROExpr.h"
#include "ROVarsImpl.h"
#include "ROUnsImpl.h"
#include "ROQVarImpl.h"
#include "ROExUnImpl.h"
#include "ROUnVarImpl.h"
#include "ROExUnVarImpl.h"
#include "roexprfunctions.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  related to class ROExprMapImpl

ROExprMapImpl::ROExprMapImpl(ROExprType p_type):
	m_type(p_type)
{
	switch(p_type)
	{
		case EnumNull:
			memset(&m_exprMapUnion, 0, sizeof(m_exprMapUnion));
			break;
		case EnumVar:
			m_exprMapUnion.m_varsI = new ROVarsImpl();
			break;
		case EnumUn:
			m_exprMapUnion.m_unsI = new ROUnsImpl();
			break;
		case EnumUnVar:
			m_exprMapUnion.m_unVarI = new ROUnVarImpl();
			break;		
		case EnumQVar:
			m_exprMapUnion.m_qVarI = new ROQVarImpl();
			break;
		case EnumExUn:
			m_exprMapUnion.m_exUnI = new ROExUnImpl();
			break;
		case EnumExUnVar:
			m_exprMapUnion.m_exUnVarI = new ROExUnVarImpl();
			break; 
		default:
			ROExceptionTypeIncompatible exp;
            throw exp;
            break;
	}
}

ROExprType ROExprMapImpl::getType() const
{
	return m_type;
}

ROExprMapUnion& ROExprMapImpl::getUnion()
{
	return m_exprMapUnion;
}

ROExprMapImpl::~ROExprMapImpl() {
		switch(m_type)
		{
			case EnumVar:
				if(m_exprMapUnion.m_varsI != NULL)
				{
					delete m_exprMapUnion.m_varsI;
				}
				break;
			case EnumUn:
				if(m_exprMapUnion.m_unsI != NULL)
				{
					delete m_exprMapUnion.m_unsI;
				}
				break;
			case EnumUnVar:
				if(m_exprMapUnion.m_unVarI != NULL)
				{
					delete m_exprMapUnion.m_unVarI;
				}
				break;
			case EnumQVar:
				if(m_exprMapUnion.m_qVarI != NULL)
				{
					delete m_exprMapUnion.m_qVarI;
				}
				break;
			case EnumExUn:
				if(m_exprMapUnion.m_exUnI != NULL)
				{
					delete m_exprMapUnion.m_exUnI;
				}
				break;
			case EnumExUnVar:
				if(m_exprMapUnion.m_exUnVarI != NULL)
				{
					delete m_exprMapUnion.m_exUnVarI;
				}
				break;
			default:
				break;
		}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  related to class ROExprImpl

int ROExprImpl::UniqueId = 1;

int ROExprImpl::generateUniqueId()
{
    UniqueId++;
	return (UniqueId - 1);
}

ROExprImpl::ROExprImpl():
    m_val(0)
{
	m_ID = generateUniqueId();
}

int ROExprImpl::getId() const
{
    return m_ID;
}

ROExprType ROExprImpl::getType() const
{
	if(m_exprMapImpl.get() == NULL) return EnumNull;
	return m_exprMapImpl->getType();
}

RONum ROExprImpl::getNum() const
{
	return m_val;
}

boost::shared_ptr<ROExprMapImpl> ROExprImpl::getMapImpl() const
{
	return m_exprMapImpl;
}

void ROExprImpl::setMapImpl(boost::shared_ptr<ROExprMapImpl> p_mapI)
{
	m_exprMapImpl = p_mapI;
}

ROExprImpl& ROExprImpl::operator += (RONum p_val)
{
    m_val += p_val;
	return *this;
}

ROExprImpl& ROExprImpl::operator -= (RONum p_val)
{
    m_val -= p_val;
	return *this;
}

ROExprImpl& ROExprImpl::operator *= (RONum p_val)
{
	if(this->getType() == EnumNull)
    {
        m_val *= p_val;
    }
    else
    {
        switch(this->getType())
        {
            case EnumVar:
				m_exprMapImpl->getUnion().m_varsI->times(p_val);
				m_val *= p_val;
                break;
            case EnumUn:
                m_exprMapImpl->getUnion().m_unsI->times(p_val);
				m_val *= p_val;
                break;
			case EnumUnVar:
                m_exprMapImpl->getUnion().m_unVarI->times(p_val);
				m_val *= p_val;
                break;
            case EnumQVar:
                m_exprMapImpl->getUnion().m_qVarI->times(p_val);
				m_val *= p_val;
                break;					
            case EnumExUn:
                m_exprMapImpl->getUnion().m_exUnI->times(p_val);
				m_val *= p_val;
                break;
            case EnumExUnVar:
                m_exprMapImpl->getUnion().m_exUnVarI->times(p_val);
				m_val *= p_val;
                break;
            default:
				ROExceptionTypeIncompatible exp;
                throw exp;
                break;
        }
    }
	return *this;
}

ROExprImpl& ROExprImpl::operator /= (RONum p_val)
{
    if(p_val == 0)
    {
        ROExceptionDivideZero exp;
		throw exp;
    }
    else if (this->getType() == EnumNull)
    {
        m_val /= p_val;
    }
    else
    {
        switch(this->getType())
        {
            case EnumVar:
				m_exprMapImpl->getUnion().m_varsI->divide(p_val);
				m_val /= p_val;
                break;
            case EnumUn:
                m_exprMapImpl->getUnion().m_unsI->divide(p_val);
				m_val /= p_val;
                break;
            case EnumQVar:
                m_exprMapImpl->getUnion().m_qVarI->divide(p_val);
				m_val /= p_val;
                break;
            case EnumUnVar:
                m_exprMapImpl->getUnion().m_unVarI->divide(p_val);
				m_val /= p_val;
                break;
            case EnumExUn:
                m_exprMapImpl->getUnion().m_exUnI->divide(p_val);
				m_val /= p_val;
                break;
            case EnumExUnVar:
                m_exprMapImpl->getUnion().m_exUnVarI->divide(p_val);
				m_val /= p_val;
                break;
            default:
				ROExceptionTypeIncompatible exp;
                throw exp;
                break;
        }
    }
    return *this;
}

ROExprImpl& ROExprImpl::operator += (const ROVar& p_var)
{
    if(this->getType() == EnumNull)
    {
        m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
        m_exprMapImpl->getUnion().m_varsI->insert(p_var);
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {
            case EnumVar:
				m_exprMapImpl->getUnion().m_varsI->insert(p_var);
                break;
            case EnumUn:
                exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
				m_exprMapImpl = exprMapImpl;
				m_exprMapImpl->getUnion().m_unVarI->insert(p_var);
				break;
			case EnumUnVar:
                m_exprMapImpl->getUnion().m_unVarI->insert(p_var);
                break;
            case EnumQVar:
                m_exprMapImpl->getUnion().m_qVarI->insert(p_var);
                break;
            case EnumExUnVar:
                m_exprMapImpl->getUnion().m_exUnVarI->insert(p_var);
                break;
            default:
				ROExceptionTypeIncompatible exp;
                throw exp;
                break;
        }
    }
	return *this;
}


ROExprImpl& ROExprImpl::operator -= (const ROVar& p_var)
{
    if(this->getType() == EnumNull)
    {
        m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
        m_exprMapImpl->getUnion().m_varsI->insertNeg(p_var);
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {
            case EnumVar:
				m_exprMapImpl->getUnion().m_varsI->insertNeg(p_var);
                break;
            case EnumUn:
                exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
				exprMapImpl->getUnion().m_unVarI->insertNeg(p_var);
				m_exprMapImpl = exprMapImpl;
				break;
			case EnumUnVar:
				m_exprMapImpl->getUnion().m_unVarI->insertNeg(p_var);
                break;
            case EnumQVar:
                m_exprMapImpl->getUnion().m_qVarI->insertNeg(p_var);
                break;
            case EnumExUnVar:
                m_exprMapImpl->getUnion().m_exUnVarI->insertNeg(p_var);
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}


ROExprImpl& ROExprImpl::operator += (const ROUn& p_un)
{
    if(this->getType() == EnumNull)
    {
        m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
        m_exprMapImpl->getUnion().m_unsI->insert(p_un);
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {   
			case EnumVar:
				exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
                exprMapImpl->getUnion().m_unVarI->insert(p_un);
				m_exprMapImpl = exprMapImpl;
                break; 
            case EnumUn:
                m_exprMapImpl->getUnion().m_unsI->insert(p_un);
                break;
            case EnumUnVar:
                m_exprMapImpl->getUnion().m_unVarI->insert(p_un);
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}


ROExprImpl& ROExprImpl::operator -= (const ROUn& p_un)
{
    if(this->getType() == EnumNull)
    {
        m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
        m_exprMapImpl->getUnion().m_unsI->insertNeg(p_un);
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {
			case EnumVar:
				exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
                exprMapImpl->getUnion().m_unVarI->insertNeg(p_un);
				m_exprMapImpl =exprMapImpl;
                break; 
            case EnumUn:
                m_exprMapImpl->getUnion().m_unsI->insertNeg(p_un);
                break; 
            case EnumUnVar:
                m_exprMapImpl->getUnion().m_unVarI->insertNeg(p_un);
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}

ROExprImpl& ROExprImpl::operator *= (const ROVar& p_var)
{
	boost::shared_ptr<ROExprMapImpl> exprMapImpl;
	switch(this->getType())
    {
		case EnumNull:
			m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
			m_exprMapImpl->getUnion().m_varsI->add(*((p_var * m_val).getImpl()->getMapImpl()->getUnion().m_varsI));
			m_val = 0;
			break;
		case EnumVar:
			exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
			exprMapImpl->getUnion().m_qVarI->addTimes(*(this->getMapImpl()->getUnion().m_varsI), p_var);
			exprMapImpl->getUnion().m_qVarI->add(*((p_var * m_val).getImpl()->getMapImpl()->getUnion().m_varsI));
			m_exprMapImpl = exprMapImpl;
			m_val = 0;
			break; 		
		case EnumUn:
			exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
			exprMapImpl->getUnion().m_unVarI->addTimes(*(this->getMapImpl()->getUnion().m_unsI), p_var);
			m_exprMapImpl = exprMapImpl;
			m_exprMapImpl->getUnion().m_unVarI->add(*((p_var * m_val).getImpl()->getMapImpl()->getUnion().m_varsI));
			m_val = 0;
			break; 
		default:
			ROExceptionTypeIncompatible exp;
			throw exp;
    }
	return *this;
}

ROExprImpl& ROExprImpl::operator *= (const ROUn& p_un)
{
	boost::shared_ptr<ROExprMapImpl> exprMapImpl;
	switch(this->getType())
    {
		case EnumNull:
			m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
			m_exprMapImpl->getUnion().m_unsI->add(*((p_un * m_val).getImpl()->getMapImpl()->getUnion().m_unsI));
			m_val = 0;
			break;
		case EnumVar:
			exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
			exprMapImpl->getUnion().m_unVarI->addTimes(*(this->getMapImpl()->getUnion().m_varsI), p_un);
			m_exprMapImpl = exprMapImpl;
			m_exprMapImpl->getUnion().m_unVarI->add(*((p_un * m_val).getImpl()->getMapImpl()->getUnion().m_unsI));
			m_val = 0;
			break; 		
		default:
			ROExceptionTypeIncompatible exp;
			throw exp;
    }
	return *this;
}


ROExprImpl& ROExprImpl::operator += (const ROExprImpl& p_expr)
{
    if(this->getType() == EnumNull)
    {
        switch(p_expr.getType())
        {
			case EnumNull:
				m_val += p_expr.getNum();
				break;
            case EnumVar:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
				m_exprMapImpl->getUnion().m_varsI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
				m_val += p_expr.getNum();
                break;
            case EnumUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
				m_exprMapImpl->getUnion().m_unsI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
				m_val += p_expr.getNum();
                break;
			case EnumUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				m_exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unVarI));
                m_val += p_expr.getNum();
                break; 
            case EnumQVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
				m_exprMapImpl->getUnion().m_qVarI->add(*(p_expr.getMapImpl()->getUnion().m_qVarI));
                m_val += p_expr.getNum();
                break;
            case EnumExUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUn));
                m_exprMapImpl->getUnion().m_exUnI->add(*(p_expr.getMapImpl()->getUnion().m_exUnI));
				m_val += p_expr.getNum();
                break;
            case EnumExUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));
                m_exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
                m_val += p_expr.getNum();
                break; 
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {
            case EnumVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_varsI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val += p_expr.getNum();
                        break;
                    case EnumUn:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    case EnumQVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
						exprMapImpl->getUnion().m_qVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_qVarI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    case EnumUnVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unVarI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    case EnumExUnVar:
						exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));
						exprMapImpl->getUnion().m_exUnVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumUn:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
						exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    case EnumUn:
                        m_exprMapImpl->getUnion().m_unsI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_val += p_expr.getNum();
                        break;
                    case EnumUnVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
						exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unVarI));
						m_exprMapImpl = exprMapImpl;
						m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
			case EnumUnVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val += p_expr.getNum();
                        break;
                    case EnumUn:
						m_exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_val += p_expr.getNum();
                        break;
                    case EnumUnVar:
                        m_exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unVarI));
                        m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumQVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_qVarI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val += p_expr.getNum();
                        break;
                    case EnumQVar:
                        m_exprMapImpl->getUnion().m_qVarI->add(*(p_expr.getMapImpl()->getUnion().m_qVarI));
                        m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumExUn:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumExUn:
                        m_exprMapImpl->getUnion().m_exUnI->add(*(p_expr.getMapImpl()->getUnion().m_exUnI));
						m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumExUnVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val += p_expr.getNum();
                        break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val += p_expr.getNum();
                        break;
					case EnumExUn:
                        m_exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_exUnI));
						m_val += p_expr.getNum();
                        break;
					case EnumExUnVar:
                        m_exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
						m_val += p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}

ROExprImpl& ROExprImpl::operator -= (const ROExprImpl& p_expr)
{
    if(this->getType() == EnumNull)
    {
        switch(p_expr.getType())
        {
			case EnumNull:
				m_val -= p_expr.getNum();
                break;
            case EnumVar:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
				m_exprMapImpl->getUnion().m_varsI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
				m_val -= p_expr.getNum();
                break;
            case EnumUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
				m_exprMapImpl->getUnion().m_unsI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unsI));
				m_val -= p_expr.getNum();
                break;
			case EnumUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				m_exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unVarI));
                m_val -= p_expr.getNum();
                break; 
            case EnumQVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
				m_exprMapImpl->getUnion().m_qVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_qVarI));
                m_val -= p_expr.getNum();
                break;
            case EnumExUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUn));
                m_exprMapImpl->getUnion().m_exUnI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnI));
				m_val -= p_expr.getNum();
                break;
            case EnumExUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));
                m_exprMapImpl->getUnion().m_exUnVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
                m_val -= p_expr.getNum();
                break; 
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
        switch(this->getType())
        {
            case EnumVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_varsI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val -= p_expr.getNum();
                        break;
                    case EnumUn:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    case EnumQVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
						exprMapImpl->getUnion().m_qVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_qVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    case EnumUnVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unVarI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    case EnumExUnVar:
						exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));
						exprMapImpl->getUnion().m_exUnVarI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprMapImpl->getUnion().m_exUnVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumUn:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
					case EnumVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
						exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    case EnumUn:
                        m_exprMapImpl->getUnion().m_unsI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_val -= p_expr.getNum();
                        break;
                    case EnumUnVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->add(*(this->getMapImpl()->getUnion().m_unsI));
						exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unVarI));
						m_exprMapImpl = exprMapImpl;
						m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
			case EnumUnVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val -= p_expr.getNum();
                        break;
                    case EnumUn:
						m_exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unsI));
						m_val -= p_expr.getNum();
                        break;
                    case EnumUnVar:
                        m_exprMapImpl->getUnion().m_unVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_unVarI));
                        m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumQVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_qVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val -= p_expr.getNum();
                        break;
                    case EnumQVar:
                        m_exprMapImpl->getUnion().m_qVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_qVarI));
                        m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumExUn:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
                    case EnumExUn:
                        m_exprMapImpl->getUnion().m_exUnI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnI));
						m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumExUnVar:
                switch(p_expr.getType())
                {
					case EnumNull:
						m_val -= p_expr.getNum();
						break;
                    case EnumVar:
                        m_exprMapImpl->getUnion().m_exUnVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_varsI));
						m_val -= p_expr.getNum();
                        break;
					case EnumExUn:
                        m_exprMapImpl->getUnion().m_exUnVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnI));
						m_val -= p_expr.getNum();
                        break;
					case EnumExUnVar:
                        m_exprMapImpl->getUnion().m_exUnVarI->addNeg(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
						m_val -= p_expr.getNum();
                        break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}

ROExprImpl& ROExprImpl::operator *= (const ROExprImpl& p_expr)
{
   if(this->getType() == EnumNull)
    {
		switch(p_expr.getType())
		{
			case EnumNull:
				m_val *= p_expr.getNum();
				break;
            case EnumVar:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));
				m_exprMapImpl->getUnion().m_varsI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
				this->operator*=(m_val);
				m_val *= p_expr.getNum();
                break;
            case EnumUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn));
				m_exprMapImpl->getUnion().m_unsI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
				this->operator*=(m_val);
				m_val *= p_expr.getNum();
                break;
			case EnumUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
				m_exprMapImpl->getUnion().m_unVarI->add(*(p_expr.getMapImpl()->getUnion().m_unVarI));
				this->operator*=(m_val);
                m_val *= p_expr.getNum();
                break; 
            case EnumQVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
				m_exprMapImpl->getUnion().m_qVarI->add(*(p_expr.getMapImpl()->getUnion().m_qVarI));
				this->operator*=(m_val);
                m_val *= p_expr.getNum();
                break;
            case EnumExUn:
                m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUn));
                m_exprMapImpl->getUnion().m_exUnI->add(*(p_expr.getMapImpl()->getUnion().m_exUnI));
				this->operator*=(m_val);
				m_val *= p_expr.getNum();
                break;
            case EnumExUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));
                m_exprMapImpl->getUnion().m_exUnVarI->add(*(p_expr.getMapImpl()->getUnion().m_exUnVarI));
				this->operator*=(m_val);
                m_val *= p_expr.getNum();
                break; 
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
		}
    }
    else
    {
		boost::shared_ptr<ROExprMapImpl> exprMapImpl;
		boost::shared_ptr<ROExprImpl> exprImpl_L;
		boost::shared_ptr<ROExprImpl> exprImpl_R;
        switch(this->getType())
        {
            case EnumVar:
                switch(p_expr.getType())
                {
                    case EnumVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumQVar));
						exprMapImpl->getUnion().m_qVarI->addTimes(*(p_expr.getMapImpl()->getUnion().m_varsI), *(this->getMapImpl()->getUnion().m_varsI));

						exprImpl_L = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_L->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));
						exprImpl_L->getMapImpl()->getUnion().m_varsI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						exprImpl_L->operator*=(m_val);

						exprImpl_R = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_R->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));
						exprImpl_R->getMapImpl()->getUnion().m_varsI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprImpl_R->operator*=(p_expr.getNum());

						exprMapImpl->getUnion().m_qVarI->add((*(exprImpl_L->getMapImpl()->getUnion().m_varsI)));
						exprMapImpl->getUnion().m_qVarI->add(*(exprImpl_R->getMapImpl()->getUnion().m_varsI));
						m_val *=  p_expr.getNum();
						m_exprMapImpl = exprMapImpl;
                        break;
                    case EnumUn:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->addTimes(*(p_expr.getMapImpl()->getUnion().m_unsI), *(this->getMapImpl()->getUnion().m_varsI));

						exprImpl_L = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_L->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn)));
						exprImpl_L->getMapImpl()->getUnion().m_unsI->add(*(p_expr.getMapImpl()->getUnion().m_unsI));
						exprImpl_L->operator*=(m_val);

						exprImpl_R = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_R->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));
						exprImpl_R->getMapImpl()->getUnion().m_varsI->add(*(this->getMapImpl()->getUnion().m_varsI));
						exprImpl_R->operator*=(p_expr.getNum());

						exprMapImpl->getUnion().m_unVarI->add((*(exprImpl_L->getMapImpl()->getUnion().m_unsI)));
						exprMapImpl->getUnion().m_unVarI->add(*(exprImpl_R->getMapImpl()->getUnion().m_varsI));
						m_val *=  p_expr.getNum();
						m_exprMapImpl = exprMapImpl;
                        break;
					case EnumNull:
						this->operator*=(p_expr.getNum());
						break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            case EnumUn:
                switch(p_expr.getType())
                {
                    case EnumVar:
                    	exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUnVar));
						exprMapImpl->getUnion().m_unVarI->addTimes(*(p_expr.getMapImpl()->getUnion().m_varsI), *(this->getMapImpl()->getUnion().m_unsI));

						exprImpl_L = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_L->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar)));
						exprImpl_L->getMapImpl()->getUnion().m_varsI->add(*(p_expr.getMapImpl()->getUnion().m_varsI));
						exprImpl_L->operator*=(m_val);

						exprImpl_R = boost::shared_ptr<ROExprImpl>(new ROExprImpl());
						exprImpl_R->setMapImpl(boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumUn)));
						exprImpl_R->getMapImpl()->getUnion().m_unsI->add(*(this->getMapImpl()->getUnion().m_unsI));
						exprImpl_R->operator*=(p_expr.getNum());

						exprMapImpl->getUnion().m_unVarI->add((*(exprImpl_L->getMapImpl()->getUnion().m_varsI)));
						exprMapImpl->getUnion().m_unVarI->add(*(exprImpl_R->getMapImpl()->getUnion().m_unsI));
						m_val *=  p_expr.getNum();
						m_exprMapImpl = exprMapImpl;
                        break;
					case EnumNull:
						this->operator*=(p_expr.getNum());
						break;
                    default:
                        ROExceptionTypeIncompatible exp;
                        throw exp;
                }
                break;
            default:
                ROExceptionTypeIncompatible exp;
                throw exp;
        }
    }
	return *this;
}


ROExprImpl& ROExprImpl::expect(const ROUn& p_un)
{
	if(this->getType() == EnumNull)
    {
		m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUn));
		m_exprMapImpl->getUnion().m_exUnI->expect(p_un);
    }
    else
    {
		ROExceptionTypeIncompatible exp;
        throw exp;
    }
	return *this;
}

ROExprImpl& ROExprImpl::expect(const ROExprImpl& p_exprI)
{
	if(this->getType() == EnumNull)
	{
        switch(p_exprI.getMapImpl()->getType())
        {
			case EnumNull:
				m_val += p_exprI.getNum();
				break;	
			case EnumVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumVar));       
				m_exprMapImpl->getUnion().m_varsI->add(*(p_exprI.getMapImpl()->getUnion().m_varsI));
				m_val += p_exprI.getNum();
				break;
			case EnumUn:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUn));       
				m_exprMapImpl->getUnion().m_exUnI->expect(*(p_exprI.getMapImpl()->getUnion().m_unsI));
				m_val += p_exprI.getNum();
				break;
            case EnumUnVar:
				m_exprMapImpl = boost::shared_ptr<ROExprMapImpl>(new ROExprMapImpl(EnumExUnVar));       
				m_exprMapImpl->getUnion().m_exUnVarI->expect(*(p_exprI.getMapImpl()->getUnion().m_unVarI));
				m_val += p_exprI.getNum();
				break;
			default:
				ROExceptionTypeIncompatible exp;
                throw exp;
		}
    }
    else
    {
		ROExceptionTypeIncompatible exp;
        throw exp;
    }
	return *this;
}


ROExprImpl::~ROExprImpl()
{
    
}
