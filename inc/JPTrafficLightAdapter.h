/*
 * JPTrafficLightAdapter.h
 *
 *  Created on: Dec 4, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPTRAFFICLIGHTADAPTER_H_
#define SRC_JAMES_JPTRAFFICLIGHTADAPTER_H_
#include "DJTrafficLightManager.h"
#include "../test/JPLightTestStub.h"
/**
 * \brief A simple adapter class that can use either a  DJTrafficLightManager or a JPLightTestStub.
 *
 * It's an ugly last minute solution. In the long run it would be refactored away by building the desired
 * traffic lights into the test class.
 */
class JPTrafficLightAdapter {
public:
	JPTrafficLightAdapter();
	void setTestStub(JPLightTestStub *stub);
	virtual ~JPTrafficLightAdapter();
	int getState(const int dir, const int lane, const double time) const;

private:
	DJTrafficLightManager *_dj;
	JPLightTestStub *_jp;
};

#endif /* SRC_JAMES_JPTRAFFICLIGHTADAPTER_H_ */
