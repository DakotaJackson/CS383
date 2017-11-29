/*
 * SimulationEngine_test.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../inc/JPSimulationEngine.h"
#include "JPLightTestStub.h"
#include "JPCarTestStub.h"
#include "../inc/JPUpdatableInterface.h"
#include <stdio.h>


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

class SETestClass: JPUpdatableInterface
{
private:
	JPLightTestStub *light; //Stays a stub
	JPTrafficModel *model;
	JPIntersection *inter;
	int carCount[4][4];
	int test;
	int position;
	int testResult;
	enum tests {NULL_TEST, MAKE_CAR, ADD_CAR};

	void destroyEngine(JPSimulationEngine *engine)
	{
		engine->destory();
	}

	void printCar(SFCar *car)
	{
		double x = car->getX();
		double y = car->getY();
		double theta = car->getTheta();
		double insim = car->getTimeInSim();
		double wait = car->getWaitTime();
		double speed = car->getSpeed();
		int turn = car->getTurnDirection();
		char trn = 'S';

		if( SFCar::DESIRE_RIGHT == turn )
			trn = 'R';
		else if( SFCar::DESIRE_LEFT == turn )
			trn = 'L';

		printf("X:%3.2f Y:%3.2f Th: %2.0f %c Sp:%2.1f St:%3.1f Wt:%3.1f \n",
				x, y, theta, trn, speed, insim, wait);
	}

	int makeCarVilidation(SFCar *car)
	{
		printCar(car);
		//X, Y, Theta,
	}
	void updateAddObject(void *object, int objType)
	{
		SFCar *car = (SFCar*) object;

		if(MAKE_CAR == test)
			makeCarVilidation(car);
		else if(ADD_CAR == test)
		{
			int dir = 0; //todo get dir from theta
			double theta = car->getTheta();

			if(consts::deq(theta,0))
				dir = JPIntersection::NORTHBOUND;
			if(consts::deq(theta,90))
				dir = JPIntersection::EASTBOUND;
			if(consts::deq(theta,180))
				dir = JPIntersection::SOUTHBOUND;
			if(consts::deq(theta,270))
				dir = JPIntersection::WESTBOUND;

			carCount[dir][0]++;

			switch(car->getTurnDirection())
			{
				case SFCar::DESIRE_LEFT: carCount[dir][1]++; break;
				case SFCar::DESIRE_RIGHT: carCount[dir][2]++; break;
				case SFCar::DESIRE_STRAIGHT: carCount[dir][3]++; break;
			}
		}

	}

	JPTrafficModel *getNullTrafficModel()
	{
		printf("Here:TM\n");
		model = new JPTrafficModel();
		for(int dir = 0; dir < 4; dir++)
		{
			model->setProbability(dir,0,0,100);
			model->setTrafficRate(dir,0);
		}
		return model;
	}

	/**
	 * \brief Get an intersection with two lanes in each direction: 1SR, 1L
	 */
	JPIntersection *getType1Intersection()
	{
		printf("HereT1I\n");
		inter = new JPIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,1.5);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,0,JPLane::LEFT,1,0);
		}

		return inter;
	}
	JPIntersection *getType2Intersection()
	{
		printf("HereT1I\n");
		inter = new JPIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,2);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,0,JPLane::LEFT,1,0);
		}

		return inter;
	}

	JPIntersection *getType3Intersection()
	{
		printf("HereT1I\n");
		inter = new JPIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,3);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,0,JPLane::STRAIGHT,1,0);
			inter->addLane(dir,0,JPLane::LEFT,2,0);
		}

		return inter;
	}

	JPSimulationEngine *getSetup(int iType)
	{
		getNullTrafficModel();
		switch(iType)
		{
			case 1: getType1Intersection(); break;
			case 2: getType2Intersection(); break;
			case 3: getType3Intersection(); break;
		}

		JPSimulationEngine *eng = JPSimulationEngine::getInstance();
		eng->setInitTime(0);
		eng->setIntersection(inter);
		eng->setTrafficLight(light);
		eng->setTrafficModel(model);
		//eng->init();
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
		//JPSimulationEngine *eng = getSetup(1);

		return -1;
	}

	int redLightStopTest()
	{
		return -1;
	}

	//add cars with two different layouts, verify they are correctly positioned
	int makeCarSubTest(int type, int numLanes)
	{
		JPSimulationEngine *eng;
		model->setProbability(JPIntersection::NORTHBOUND, 100, 0, 0);
		model->setProbability(JPIntersection::SOUTHBOUND, 0, 100, 0);
		//east and west are straight

		eng = getSetup(1);
		eng->subscribeObjectAdded(this);
		int dir, ln;
		for(dir = 0; dir < 4; dir++)
			for(ln = 0; ln < 4; ln++)
			{
				eng->makeCar(dir, ln);
				position++;
			}

		eng->destory();
		return -1;
	}

	int makeCarTest()
	{
		test = MAKE_CAR;
		position = 0;
		makeCarSubTest(1, 2);
		makeCarSubTest(2, 2);
		makeCarSubTest(3, 2);

		return -1;
	}
/*
 * 1) AddCar can't be lane specific must be direction specific
 * 2) change speed limits for makeCar case2
 */

	//three pass of equal with different steps verify correct number is added
	int addCarTest()
	{
		test = ADD_CAR;
		position = 0;

		JPSimulationEngine *eng = getSetup(1);
		eng->subscribeObjectAdded(this);
		//change the traffic model
		int dir;
		for(dir = 0; dir < 4; dir++)
			model->setProbability(dir, 25, 40, 35);
		//model->setTrafficRate(JPIntersection::NORTHBOUND, 720); //5 sec pe
		//model->setTrafficRate(JPIntersection::SOUTHBOUND, 360); //10 sec per
		//model->setTrafficRate(JPIntersection::EASTBOUND, 275); //13.9 sec per
		//model->setTrafficRate(JPIntersection::WESTBOUND, 200); //18 sec per

		//re-init to change the start times

		eng->destory();
		return -1;
	}

	int getNextCarTest()
	{
		return -1;
	}

public:
	SETestClass()
	{
		light = NULL;
		model = NULL;
		inter = NULL;

		test = NULL_TEST;
		position = 0;

		int dir, j;
		for(dir = 0; dir < 4; dir++)
		{
			for(j = 0; j < 4; j++)
				carCount[dir][j] = 0;
		}
	}

	int run()
	{
		int ret;
		ret = consts::testOuptut(
				"JPSimulationEngine: Prerequisites",
				prereqTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Get Next Car Test",
				rightTurnRedTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Make Car Test",
				makeCarTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Add Car Test",
				addCarTest() );
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
	//function can be private non static
	SETestClass test;
	test.run();
	return 0;
}

/** @} */
