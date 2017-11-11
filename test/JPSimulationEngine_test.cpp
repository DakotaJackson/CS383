/*
 * SimulationEngine_test.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../inc/JPSimulationEngine.h"

/* now they are member functions
int straightGreenTest();
int rightTurnRedTest();
int leftTurnGreenTest();
int leftTurnBlinkYellowTest();
int matchPaceTest();
int redLightStopTest();
*/

/**
 * \addtogroup TST
 * @{
 */

class SETestClass
{
private:
	void destroyEngine(JPSimulationEngine *engine)
	{
		engine->destory();
	}

	int straightGreenTest()
	{
		return -1;
	}

	int rightTurnRedTest()
	{
		JPSimulationEngine *eng = JPSimulationEngine::getInstance();
		return -1;
	}

	int leftTurnGreenTest()
	{
		return -1;
	}

	int leftTurnBlinkYellowTest()
	{
		return -1;
	}

	int matchPaceTest()
	{
		return -1;
	}

	int redLightStopTest()
	{
		return -1;
	}

public:
	SETestClass(){}
	int run()
	{
		int ret;
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				rightTurnRedTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				rightTurnRedTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				leftTurnGreenTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				leftTurnBlinkYellowTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				matchPaceTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: ",
				redLightStopTest() );
		return ret;
	}

};

int main()
{
	//put all the test code in the class so the destroy
	//function can private non static
	SETestClass test;
	test.run();
	return 0;
}

/** @} */
