/*
 * JPTrafficModelExceptions.h
 *
 *  Created on: Oct 25, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPTRAFFICMODELEXCEPTIONS_H_
#define SRC_JAMES_JPTRAFFICMODELEXCEPTIONS_H_
#include <exception>

/**
 * \addtogroup EXC
 * @{
 */
class JPTrafficModelException: public std::exception
{
public:
	JPTrafficModelException();
	virtual ~JPTrafficModelException() throw();
	virtual const char* what() const throw();
};
/*
class JPDirectionOutOfBoundsException: public JPTrafficModelException
{
public:
	JPDirectionOutOfBoundsException();
	virtual ~JPDirectionOutOfBoundsException() throw();
	virtual const char* what() const throw();
};
*/
class JPRateLessThanZeroException: public JPTrafficModelException
{
public:
	JPRateLessThanZeroException();
	virtual ~JPRateLessThanZeroException() throw();
	virtual const char* what() const throw();
};

class JPProbabilityLessThanZeroException: public JPTrafficModelException
{
public:
	JPProbabilityLessThanZeroException();
	virtual ~JPProbabilityLessThanZeroException() throw();
	virtual const char* what() const throw();
};

/**
 * @}
 */
#endif /* SRC_JAMES_JPTRAFFICMODELEXCEPTIONS_H_ */
