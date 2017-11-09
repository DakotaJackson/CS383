/*
 * JPLightTestStub.h
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_TESTLIGHTSTUB_H_
#define SRC_JAMES_TESTLIGHTSTUB_H_

/**
 * \addtogroup TST
 * @{
 */

/**
 * \brief a test stub for testing JPSimulation Engine.
 *
 * Provides specific traffic light situations for testing of the simulation engine.
 */
class JPLightTestStub
{

public:
	JPLightTestStub();
	virtual ~JPLightTestStub();
	void setTestCase(int testCase);

private:
	int _testCase;
};
/** @} */
#endif /* SRC_JAMES_TESTLIGHTSTUB_H_ */
