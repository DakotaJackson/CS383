/*
 * JPCarTestStub.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#include "JPCarTestStub.h"

JPCarTestStub::JPCarTestStub()
{
	// TODO Auto-generated constructor stub

}

JPCarTestStub::~JPCarTestStub()
{
	// TODO Auto-generated destructor stub
}

double JPCarTestStub::getDesiredSpeed() const
{
	return _dspeed;
}

double JPCarTestStub::getLength() const
{
	return _leng;
}

JPCarTestStub::JPCarTestStub(double leng, double X, double Y, double speed,
		double dspeed)
{
	this->setSpeed(speed);
	this->setX(X);
	this->setY(Y);
	_dspeed = dspeed;
	_leng = leng;
}
