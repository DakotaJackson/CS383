/*
 * JPTrafficLightAdapter.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: james
 */

#include "JPTrafficLightAdapter.h"
#include <stdio.h> //for NULL

JPTrafficLightAdapter::JPTrafficLightAdapter()
{
	_dj = DJTrafficLightManager::GetInstance();
	_jp = NULL;
}

void JPTrafficLightAdapter::setTestStub(JPLightTestStub* stub)
{
	_jp = stub;
}

JPTrafficLightAdapter::~JPTrafficLightAdapter() {
	// TODO Auto-generated destructor stub
}

int JPTrafficLightAdapter::getState(const int dir, const int lane,
		const double time) const
{
	if(_jp)
		return _jp->getState(dir, lane, time);
	else
		return _dj->getState(time, dir, lane);
}
