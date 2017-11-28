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
	enum Cases {GREEN_EW, GREEN_NS};
	JPLightTestStub();
	JPLightTestStub(int testCase);
	virtual ~JPLightTestStub();
	int getTestCase() const;
	void setTestCase(int testCase);
	/** a placeholder function to ease catching all changes when integrating */
	int getTheState(int direction, int lane, double time);

private:
	int _testCase;
};
/** @} */
#endif /* SRC_JAMES_TESTLIGHTSTUB_H_ */
