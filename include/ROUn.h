//
//  ROUn.h
//  RobustOptimizationSolver
//
//  Created by Meilin Zhang on 27/8/12.
//  Copyright (c) 2012 __ROC__. All rights reserved.
//

#ifndef RobustOptimizationSolver_ROUn_h
#define RobustOptimizationSolver_ROUn_h

#include "ROTypedefs.h"

class ROUnImpl;


/**
 * An instance of this class is an uncertain variable.
 *
 * Date: 30-Sep-2012
 * @author Zhang Meilin, National University of Singapore
 * @version 1.0
 */
class ROUn
{
public:

	/**
	 * The default constructor of ROUn.
	 */
    ROUn();

	/**
	 * The copy constructor of ROUn.
	 */
	ROUn(const ROUn&);

    /**
     * Return the number of uncertain variables created.
     */
	static int getNo();

	/**
	 * This member function returns the unique ID of invoking uncertainty variable.
	 *
	 * @return  Unique ID of invoking object.
	 */
    int getId() const;

    /**
     * The destructor of ROUn.
     *
     */
    ~ROUn();
    
private:
	friend class ROModel;
    int m_id;
    static int generateUniqueId();
	static void resetUniqueId();
    static int UniqueId;
    
};

#endif
