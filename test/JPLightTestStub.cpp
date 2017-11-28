/*
 * JPLightTestStub.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#include "JPLightTestStub.h"

JPLightTestStub::JPLightTestStub()
{
	_testCase = 0;
}

JPLightTestStub::~JPLightTestStub()
{
	// TODO Auto-generated destructor stub
}

JPLightTestStub::JPLightTestStub(int testCase)
{
	_testCase = testCase;
}

int JPLightTestStub::getTestCase() const {	return _testCase; }
void JPLightTestStub::setTestCase(int testCase) { _testCase = testCase; }
