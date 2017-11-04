/*
 * JPTrafficModelExceptions.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: james
 */

#include "../../inc/JPTrafficModelExceptions.h"

JPTrafficModelException::JPTrafficModelException() {
	// TODO Auto-generated constructor stub

}

JPTrafficModelException::~JPTrafficModelException() throw() {
	// TODO Auto-generated destructor stub
}

const char* JPTrafficModelException::what() const throw ()
{
	return "";
}

JPRateLessThanZeroException::JPRateLessThanZeroException()
{
}

JPRateLessThanZeroException::~JPRateLessThanZeroException() throw () {
}

const char* JPRateLessThanZeroException::what() const throw ()
{
	return "";
}

JPProbabilityLessThanZeroException::JPProbabilityLessThanZeroException() {
}

JPProbabilityLessThanZeroException::~JPProbabilityLessThanZeroException() throw () {
}

const char* JPProbabilityLessThanZeroException::what() const throw ()
{
	return "";
}


