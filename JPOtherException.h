/*
 * MissingParameterException.h
 *
 *  Created on: Nov 28, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_OTHEREXCEPTION_H_
#define SRC_JAMES_OTHEREXCEPTION_H_
#include <exception>

class JPMissingParameterException: public std::exception
{
public:
	enum details {TRAFFIC_MODEL, TRAFFIC_LIGHT, INTERSECTION };

	JPMissingParameterException();
	JPMissingParameterException(int detail);
	virtual ~JPMissingParameterException();
	virtual const char* what() const throw();
	int getDetail() const;

private:
	int _detail;
};

#endif /* SRC_JAMES_OTHEREXCEPTION_H_ */
