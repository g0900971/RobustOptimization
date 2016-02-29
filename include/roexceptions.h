//
//  roexceptions.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 30/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.

#ifndef RobustOptimizationSolver_roexceptions_h
#define RobustOptimizationSolver_roexceptions_h

#include <iostream>
#include <exception>
#include <string>
#include <sstream>


/**
 * This class is the base class for exceptions in robust optimization.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Exception happened";
  }
};


/**
 * An instance of this class is an exception thrown when types are incompatible.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionTypeIncompatible: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Type Incompatible";
  }
};


/**
 * An instance of this class is an exception thrown when types are incompatible.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionIncompatibleExpr: public std::exception
{
public:
	ROExceptionIncompatibleExpr(const char* log = NULL)
	{
		if(log)
		{
			m_log = std::string(log);
		}
	}

	  virtual const char* what() const throw()
	  {
		  std::ostringstream os;
		  os << "Type Incompatible: ";
		  os << m_log;
		  return os.str().c_str();
	  }
private:
	std::string m_log;
};


/**
 * An instance of this class is an exception thrown when expressions are divided by zero.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionDivideZero: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Cannot divide by zero";
  }
};


/**
 * An instance of this class is an exception thrown when index out of range.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionOutRange: public std::exception
{
	  virtual const char* what() const throw()
	  {
	    return "Index Out of Range";
	  }
};


/**
 * An instance of this class is an exception thrown when null pointer encountered.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionNullPointer: public std::exception
{
public:
	ROExceptionNullPointer(const char* log = NULL)
	{
		if(log)
		{
			m_log = std::string(log);
		}
	}

	  virtual const char* what() const throw()
	  {
		  std::ostringstream os;
		  os << "Null Pointer: ";
		  os << m_log;
		  return os.str().c_str();
	  }
private:
	std::string m_log;
};


/**
 * An instance of this class is an exception thrown when dynamic cast impossible.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionDynamicCast: public std::exception
{
public:
	ROExceptionDynamicCast(const char* log = NULL)
	{
		if(log)
		{
			m_log = std::string(log);
		}
	}

	  virtual const char* what() const throw()
	  {
		  std::ostringstream os;
		  os << "Cannot Dynamic Cast: ";
		  os << m_log;
		  return os.str().c_str();
	  }
private:
	std::string m_log;
};


/**
 * An instance of this class is an exception thrown when model is used before solve.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionModelUnsolve: public std::exception
{
public:
	ROExceptionModelUnsolve(const char* log = NULL)
	{
		if(log)
		{
			m_log = std::string(log);
		}
	}

	  virtual const char* what() const throw()
	  {
		  std::ostringstream os;
		  os << "Model has not been solved: ";
		  os << m_log;
		  return os.str().c_str();
	  }
private:
	std::string m_log;
};


/**
 * An instance of this class is an exception thrown when unexpected var or unvar count met.
 *
 * Date: 05-Apr-2013
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROExceptionUnExpectCount: public std::exception
{
public:
	ROExceptionUnExpectCount(const char* log = NULL)
	{
		if(log)
		{
			m_log = std::string(log);
		}
	}

	  virtual const char* what() const throw()
	  {
		  std::ostringstream os;
		  os << "Unexpected count for var or unvar in the ROCountManager: ";
		  os << m_log;
		  return os.str().c_str();
	  }
private:
	std::string m_log;
};

#endif
