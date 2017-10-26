/*
 * JPCarTestStub.h
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#ifndef TEST_JPCARTESTSTUB_H_
#define TEST_JPCARTESTSTUB_H_

/**
 * \brief A configurable car test stub for testing the simulation.
 */
class JPCarTestStub
{
public:
	JPCarTestStub();
	virtual ~JPCarTestStub();
	double getDesiredSpeed();
	double getLength();
};

#endif /* TEST_JPCARTESTSTUB_H_ */
