/*
 * JPLightTestStub.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#include "JPLightTestStub.h"
#include "JPConstants.h"
#include "JPIntersection.h"

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
void JPLightTestStub::setTestCase(int testCase)
{
	_testCase = testCase;
}

int JPLightTestStub::getState(int direction, int lane, double time)
{
	switch(_testCase)
	{
		case GREEN_NS:
			if(direction %2 == JPIntersection::NORTH % 2)
				return consts::GREEN;
			else
				return consts::RED;
		case GREEN_EW:
			if(direction %2 == JPIntersection::EAST % 2)
				return consts::GREEN;
			else
				return consts::RED;
	}

	return 0;
}
