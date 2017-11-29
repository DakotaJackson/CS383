/*
 * MissingParameterException.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: james
 */

#include "../../inc/JPOtherException.h"

JPMissingParameterException::JPMissingParameterException()
{
	_detail = 0;
}

JPMissingParameterException::JPMissingParameterException(int detail)
{
	_detail = detail;
}

JPMissingParameterException::~JPMissingParameterException() {}

const char* JPMissingParameterException::what() const throw ()
{
	return "Missing one of the required parameters";
}

int JPMissingParameterException::getDetail() const { return _detail; }
