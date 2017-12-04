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
	/** \brief Test Cases */
	enum Cases {GREEN_EW, /// Green lights for east and west, red otherwise
		GREEN_NS ///green lights for north and south,  red otherwise
	};
	JPLightTestStub();

	/** Initialize a test stub with a test case from one of enum \link Cases \endlink*/
	JPLightTestStub(int testCase);
	virtual ~JPLightTestStub();

	/** \brief Return the current test case number which coresponds to one of enum \link Cases \endlink */
	int getTestCase() const;

	/** \brief set the test case from one of enum \link Cases \endlink */
	void setTestCase(int testCase);

	/** \brief Return the state for the given time and lane */
	int getState(int direction, int lane, double time);

private:
	int _testCase;
};
/** @} */
#endif /* SRC_JAMES_TESTLIGHTSTUB_H_ */
