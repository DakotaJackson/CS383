/*
 * JPCarTestStub.h
 *
 *  Created on: Oct 23, 2017
 *      Author: james
 */

#ifndef TEST_JPCARTESTSTUB_H_
#define TEST_JPCARTESTSTUB_H_
#include "SFCar.h"
/**
 * \addtogroup TST
 * @{
 */
/**
 * \brief A configurable car test stub for testing the simulation.
 */
class JPCarTestStub: public SFCar
{
private:
	double _dspeed;
	double _leng;

public:
	JPCarTestStub();
	JPCarTestStub(double leng, double X, double Y, double speed, double dspeed);
	virtual ~JPCarTestStub();
	double getDesiredSpeed() const override;
	double getLength() const override;

};
/** @} */
#endif /* TEST_JPCARTESTSTUB_H_ */
