/*
 * SimulationEngine_test.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../inc/JPSimulationEngine.h"
#include "JPLightTestStub.h"
#include "JPCarTestStub.h"

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
	JPLightTestStub *light;
	void destroyEngine(JPSimulationEngine *engine)
	{
		engine->destory();
	}

	JPTrafficModel *getNullTrafficModel()
	{
		printf("Here:TM\n");
		JPTrafficModel *tm = new JPTrafficModel();
		for(int dir = 0; dir < 4; dir++)
		{
			tm->setProbability(dir,0,0,0);
			tm->setTrafficRate(dir,0);
		}
		return tm;
	}

	JPIntersection *getType1Intersection()
	{
		printf("HereT1I\n");
		JPIntersection *inter = new JPIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,1);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,0,JPLane::LEFT,1,0);
		}

		return inter;
	}

	JPSimulationEngine *getType1Setup()
	{
		printf("HereT1S\n");
		JPTrafficModel *tm = getNullTrafficModel();
		JPIntersection *inter = getType1Intersection();
		printf("Here2T1S\n");
		JPSimulationEngine *eng = JPSimulationEngine::getInstance();
		printf("Here3T1S\n");
		eng->init();
		return eng;
	}

	/**
	 * \brief Test the prerequisite check for starting the simulation.
	 */
	int prereqTest()
	{
		//get all the parts
		JPTrafficModel *tm = getNullTrafficModel();
		JPIntersection *inter = getType1Intersection();
		//DJTrafficLightManager *light = new JPLightTestStub();
		JPSimulationEngine *eng;
		light = new JPLightTestStub();

		//without traffic model
		eng = JPSimulationEngine::getInstance();
		eng->setIntersection(inter);
		eng->setTrafficLight(light);
		try{
			eng->init(); //should throw exception
			return 1;
		}
		catch(JPMissingParameterException &e)
		{
			eng->destory();
		}

		//without traffic light
		eng = JPSimulationEngine::getInstance();
		eng->setIntersection(inter);
		//eng->setTrafficLight(tl);
		eng->setTrafficModel(tm);
		try{
			eng->init(); //should throw exception
			return 2;
		}
		catch(JPMissingParameterException &e)
		{
			eng->destory();
		}

		//without intersection
		eng = JPSimulationEngine::getInstance();
		//eng->setIntersection(inter);
		eng->setTrafficLight(light);
		eng->setTrafficModel(tm);
		try{
			eng->init(); //should throw exception
			return 3;
		}
		catch(JPMissingParameterException &e)
		{
			eng->destory();
		}

		//with all the correct parameters
		eng = JPSimulationEngine::getInstance();
		eng->setIntersection(inter);
		eng->setTrafficLight(light);
		eng->setTrafficModel(tm);
		try{
			eng->init(); //should throw exception
			eng->destory();
			return 0;
		}
		catch(JPMissingParameterException &e)
		{
			eng->destory();
			return 4;
		}

		return 0;
	}

	int straightGreenTest()
	{
		return -1;
	}

	int rightTurnRedTest()
	{
		//JPSimulationEngine *eng = JPSimulationEngine::getInstance();
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
		//JPSimulationEngine *eng = getType1Setup();

		return -1;
	}

	int redLightStopTest()
	{
		return -1;
	}

public:
	SETestClass()
	{
		light = NULL;
	}

	int run()
	{
		int ret;
		ret = consts::testOuptut(
				"JPSimulationEngine: Prerequisites",
				prereqTest() );
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
