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
#include <string.h>

//# define NIX_IS_HERE
#ifndef NIX_IS_HERE
#include <windows.h> /* sleep for demo */
#endif


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
	int _carCount[4][4];
	int test;
	int position;
	int _testResult;
	int _lane;
	int _direction;

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

		printf("X:%3.2f Y:%3.2f Th: %2.0f %c Sp:%2.1f St:%3.1f Wt:%3.1f ptr:%d\n",
				x, y, theta, trn, speed, insim, wait, car);
	}

	void makeCarValidation(SFCar *car, double x[4][3], double y[4][3], double theta[4])
	{
		//verify car is as expected.
		int dir = _direction;
		int ln = _lane;

		//printf("Dir %d, Lane: %d\n", dir, ln);
		//printf("Exp X: %f\tY: %f\tTheta: %f\n", x[dir][ln], y[dir][ln], theta[dir]);
		//theta
		if(! consts::deq(theta[dir], car->getTheta()) )
			_testResult += 1;

		//x
		if(! consts::deq(x[dir][ln], car->getX()) )
			_testResult += 2;

		//y
		if(! consts::deq(x[dir][ln], car->getX()) )
			_testResult += 4;

		//times
		if( (! consts::deq(1, 1 + car->getTimeInSim())) ||
				(! consts::deq(1, 1 + car->getWaitTime())) )
		{
			_testResult += 8;
		}
	}

	void makeCarValidation(SFCar *car)
	{
		//printCar(car);
		//X, Y, Theta,
		double theta[] = {180,270,0,90};

		//x and y for intersection 1 (last col not used for this intersection)
		double y1[4][3] =
		{{300,300, 0},
		{10, 0, 0},
		{-300,-300,0},
		{-10, 0, 0}};

		double x1[4][3] =
		{{-10,0, 0},
		{300,300,0},
		{10, 0, 0},
		{-300,-300,0}};

		//intersection 2
		double y2[4][3] =
		{{1320,1320, 0},
		{15, 5,0},
		{-1320,-1320,0},
		{-15, -5,0}};

		double x2[4][3] =
		{{-15, -5, 0},
		{1320,1320,0},
		{15, 5, 0},
		{-1320,-1320,0}};

		//intersection 3 (offset 3)
		double y3[4][3] =
		{{400, 400, 400},
		{25, 15, 5},
		{-500,-500,-500},
		{-25, -15, -5}};

		double x3[4][3] =
		{{-25,-15, -5},
		{450,450,450},
		{25,15,5},
		{-550,-550,-550}};

		//pick the correct solution set
		switch(position)
		{
			case 1:
				makeCarValidation(car, x1, y1, theta);
				break;
			case 2:
				makeCarValidation(car, x2, y2, theta);
				break;
			case 3:
				makeCarValidation(car, x3, y3, theta);
				break;
		}

	}

	/**
	 * \brief Track where cars were added for testing of add car function.
	 */
	void addCarTracking(SFCar *car)
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

		_carCount[dir][0]++;
		//double time = JPSimulationEngine::getInstance()->getTime();
		//printf("%f::[%d]\t%d\n", time, dir, _carCount[dir][0]);

		switch(car->getTurnDirection())
		{
			case SFCar::DESIRE_LEFT: _carCount[dir][1]++; break;
			case SFCar::DESIRE_RIGHT: _carCount[dir][2]++; break;
			case SFCar::DESIRE_STRAIGHT: _carCount[dir][3]++; break;
		}

	}

	/**
	 * \brief Observer function. Called when a car is added to the sim.
	 * Dispatches to the appropriate test handler based on what test is in progress.
	 */
	void updateAddObject(void *object, int objType)
	{
		SFCar *car = (SFCar*) object;

		if(MAKE_CAR == test)
			makeCarValidation(car);
		else if(ADD_CAR == test)
			addCarTracking(car);

	}

	JPTrafficModel *getNullTrafficModel()
	{
		model = new JPTrafficModel();
		for(int dir = 0; dir < 4; dir++)
		{
			model->setProbability(dir,0,0,100);
			model->setTrafficRate(dir,0);
		}
		return model;
	}

	JPIntersection *getFreshIntersection()
	{
		if(NULL != inter)
			delete inter;

		inter = new JPIntersection();
		return inter;
	}

	/**
	 * \brief Get an intersection with two lanes in each direction: 1SR, 1L
	 */
	JPIntersection *getType1Intersection()
	{
		//printf("HereT1I\n");
		getFreshIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
		{
			inter->setLaneOffset(dir,1.5);
			inter->setTrackedLaneLength(dir, 300);
		}

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,1,JPLane::LEFT,1,0);
		}

		return inter;
	}
	JPIntersection *getType2Intersection()
	{
		//printf("HereT2I\n");
		getFreshIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,2);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,1,JPLane::LEFT,1,0);
		}

		return inter;
	}

	JPIntersection *getType3Intersection()
	{
		//printf("HereT3I\n");
		getFreshIntersection();
		int dir;
		for(dir = 0; dir < 4; dir++)
			inter->setLaneOffset(dir,3);

		inter->setTrackedLaneLength(JPIntersection::NORTH, 400);
		inter->setTrackedLaneLength(JPIntersection::EAST, 450);
		inter->setTrackedLaneLength(JPIntersection::SOUTH, 500);
		inter->setTrackedLaneLength(JPIntersection::WEST, 550);

		for(dir = 0; dir < 4; dir++)
		{
			inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
			inter->addLane(dir,1,JPLane::STRAIGHT,1,0);
			inter->addLane(dir,2,JPLane::LEFT,2,0);
		}

		return inter;
	}

	/**
	 * A setup of lanes with various turnOptions to make sure cars get added to the correct lanes
	 */
	JPIntersection *getType4Intersection()
	{
		getFreshIntersection();

		inter->setLaneOffsets(4,4,3,3);

		//NORTH 4 lanes 0R, 1,2S, 3L
		inter->addLane(JPIntersection::NORTH,0,JPLane::RIGHT,1,0);
		inter->addLane(JPIntersection::NORTH,1,JPLane::STRAIGHT,0,0);
		inter->addLane(JPIntersection::NORTH,2,JPLane::STRAIGHT,0,0);
		inter->addLane(JPIntersection::NORTH,3,JPLane::LEFT,2,0);

		//SOUTH two lefs, 1 Straight, 1 straight right
		inter->addLane(JPIntersection::SOUTH,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
		inter->addLane(JPIntersection::SOUTH,1,JPLane::STRAIGHT,1,0);
		inter->addLane(JPIntersection::SOUTH,2,JPLane::LEFT,1,0);
		inter->addLane(JPIntersection::SOUTH,3,JPLane::LEFT,2,0);

		//EAST a left straight, a straight, and a right
		inter->addLane(JPIntersection::EAST,0,JPLane::RIGHT,1,0);
		inter->addLane(JPIntersection::EAST,1,JPLane::STRAIGHT,0,0);
		inter->addLane(JPIntersection::EAST,2,JPLane::LEFT + JPLane::STRAIGHT,2,0);

		//WEST1 1 left, 1 straight right straight, 1 right
		inter->addLane(JPIntersection::WEST,0,JPLane::RIGHT,1,0);
		inter->addLane(JPIntersection::WEST,1,JPLane::STRAIGHT+JPLane::RIGHT,0,0);
		inter->addLane(JPIntersection::WEST,2,JPLane::LEFT,2,0);
		return inter;
	}

	/**
	 * \brief Obtain a new blank unconfigured simulation engine.
	 */
	JPSimulationEngine *getFreshSim()
	{
		JPSimulationEngine *eng = JPSimulationEngine::getInstance();
		eng->destory(); //cleanup after any failed test
		eng = JPSimulationEngine::getInstance();
		return eng;
	}

	JPSimulationEngine *getSetup(int iType)
	{
		getNullTrafficModel();
		switch(iType)
		{
			case 1: getType1Intersection(); break;
			case 2: getType2Intersection(); break;
			case 3: getType3Intersection(); break;
			case 4: getType4Intersection(); break;
		}

		JPSimulationEngine *eng = getFreshSim();
		eng->setInitTime(0);
		eng->setIntersection(inter);
		light = new JPLightTestStub();
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
		JPSimulationEngine *eng;
		eng = getSetup(2);
		eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::Cases::GREEN_EW));
		eng->init();
		double t, stepTime = 0.1;

		//position car 5 seconds from light with expected stop time of 10 seconds
		JPLane *lane = inter->getLane(3,0);

		//lead car: pos = -10k, (d)speed 30 FPS
		double thirty = 30.0 * 3600/5280 - 35; //MPH delta from FPS actual (35 speed limit)
		JPCarTestStub *lcar = new JPCarTestStub(15,-10000,-15, 30, thirty);
		lcar->setTimeInSim(0);
		lcar->setTurnDirection(SFCar::DESIRE_STRAIGHT);
		lane->addCarAtEnd(lcar);	

		//Initial gap between front of lead car and front of back car is 90
		//Front car is 15 feet, and a 5 (actual target is 5.5) foot gap is to be maintained when speed is matched
		//This gives an effective gap of 70 ft.
		//With a speed difference of 10 FPS and a lookahead of 5 seconds, speed should begin chaning
		//when effective gap is 50 (i.e. approximately 2 seconds.
		//2 second till speed change should begin
		double fourty = 40.0 * 3600/5280 - 35; //MPH delta from FPS actual (35 speed limit)
		JPCarTestStub *bcar = new JPCarTestStub(15,-10090, -15, 40 , fourty);
		bcar->setTimeInSim(0);
		bcar->setTurnDirection(SFCar::DESIRE_STRAIGHT);
		lane->addCarAtEnd(bcar);	

		//iterate to the upper bound of 11 seconds.
		for(t = 0; t < 12.5; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(lcar);
			//printCar(bcar);
			//no change before 2 seconds
			if(t <= 1.5 && bcar->getSpeed() < 39.999)
					return 1; //started slowing early

			if(t <= 11 && bcar->getSpeed() < 30.001)
					return 2; //finished slowing too early
		}
		
		//verify speed is correct
		double speed = bcar->getSpeed();
		if(speed < 29.8 || speed > 30.2)
			return 3; //speed not matched

		//check gap
		double dX = lcar->getX() - bcar->getX();
		dX -= 15; //account for length of lcar;
		if(dX < 5 || dX > 6)
			return 4; //gaps is wrong

		return 0;
	}

	int rearCarAccelerationTest()
	{
		//Test 2 can behind car speed up to desired speed?
		JPSimulationEngine *eng;
		eng = getSetup(2);
		eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::Cases::GREEN_EW));
		eng->init();
		double t, stepTime = 0.1;

		//position car 5 seconds from light with expected stop time of 10 seconds
		JPLane *lane = inter->getLane(3,0);

		//lead car: pos = -10k, (d)speed 30 FPS
		double thirty = 30.0 * 3600/5280 - 35; //MPH delta from FPS actual (35 speed limit)
		JPCarTestStub *lcar = new JPCarTestStub(15,-10000,-15, 30, thirty);
		lcar->setTimeInSim(0);
		lcar->setTurnDirection(SFCar::DESIRE_STRAIGHT);
		lane->addCarAtEnd(lcar);

		//rear car going 10, should speed up
		// acceleration is 5 FPS/S so approximately 4 seconds
		double fourty = 40.0 * 3600/5280 - 35; //MPH delta from FPS actual (35 speed limit)
		JPCarTestStub *bcar = new JPCarTestStub(15,-10190, -15, 10 , fourty);
		bcar->setTimeInSim(0);
		bcar->setTurnDirection(SFCar::DESIRE_STRAIGHT);
		lane->addCarAtEnd(bcar);

		//iterate to the upper bound of 11 seconds.
		for(t = 0; t < 4.5; t += stepTime)
		{
			eng->step(stepTime);

			if(t <= 3.5 && bcar->getSpeed() > 39.999)
					return 1; //finished slowing too early
		}

		//verify speed is correct
		double speed = bcar->getSpeed();
		if(speed < 39.8 || speed > 40.2)
			return 2; //speed not matched

		return 0;
	}

	int redLightStopTest()
	{
		JPSimulationEngine *eng;
		eng = getSetup(2);
		eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::Cases::GREEN_NS));
		eng->init();
		bool stopSpeed = false;
		double t, pos, stepTime = 0.1;
		double bound = - 2 * JPIntersection::LANE_WIDTH;

		//position car 5 seconds from light with expected stop time of 10 seconds
		JPLane *lane = inter->getLane(3,0);
		SFCar *car = new SFCar();
		car->setX(-280);
		car->setY(-15);
		car->setTimeInSim(0);
		car->setSpeed(51.3);
		car->setTurnDirection(SFCar::DESIRE_STRAIGHT);
		lane->addCarAtEnd(car);	

		//iterate to the upper bound of 11 seconds.
		for(t = 0; t < 11; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				if( t < 9)
					return 1; //slowed down too quickly
				
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 2; //it didn't slow down fast enough

		pos = car->getX();
		if(pos < bound - 1 || pos > bound)
			return 3; //it did not stop at the right position
		
		//test 2 start an extra 5 seconds out
		stopSpeed = false;
		car->setX(-537);
		car->setSpeed(51.3);
		car->setTimeInSim(0);
		
		//iterate to the upper bound of 16 seconds.
		for(t = 0; t < 16; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				if( t < 14)
					return 4; //slowed down too quickly
				
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 5; //it didn't slow down fast enough
		
		pos = car->getX();
		if(pos < bound - 1 || pos > bound)
			return 6; //it did not stop at the right position

		//test 6 (past 0.5)
		stopSpeed = false;
		car->setX(-20.45);
		car->setSpeed(10.);
		car->setTimeInSim(0);
		
		//iterate to the upper bound of 16 seconds.
		for(t = 0; t < 16; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 16; //it didn't slow down fast enough
		
		pos = car->getX();
		if(pos < bound - 1 || pos > bound)
			return 17; //it did not stop at the right position

		lane->removeFirstCar(); //cleanup

		//repeat with WEST
		bound = -bound;
		stopSpeed = false;
		car->setX(280);
		car->setY(15);
		car->setSpeed(51.3);
		car->setTimeInSim(0);
		lane = inter->getLane(1,0);
		lane->addCarAtEnd(car);	

		//iterate to the upper bound of 17 seconds.
		for(t = 0; t < 11; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				if( t < 9)
					return 7; //slowed down too quickly
				
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 8; //it didn't slow down fast enough
		
		pos = car->getX();
		if(pos < bound || pos > bound + 1)
			return 9; //it did not stop at the right position
		
		lane->removeFirstCar(); //cleanup

		//new intersection for NORTH and SOUTH
 		eng = getSetup(2);
		eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::Cases::GREEN_NS));
		eng->init();

		//SOUTH
		bound = -bound; //make negative
		stopSpeed = false;
		car->setY(-280);
		car->setX(-15);
		car->setSpeed(51.3);
		car->setTimeInSim(0);
		lane = inter->getLane(2,0);
		lane->addCarAtEnd(car);	

		//iterate to the upper bound of 17 seconds.
		for(t = 0; t < 11; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				if( t < 9)
					return 10; //slowed down too quickly
				
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 11; //it didn't slow down fast enough
		
		pos = car->getY();
		if(pos < bound - 1 || pos > bound)
			return 12; //it did not stop at the right position
		
		lane->removeFirstCar(); //cleanup

		//NORTH
		bound = -bound; //make positive
		stopSpeed = false;
		car->setY(280);
		car->setX(15);
		car->setSpeed(51.3);
		car->setTimeInSim(0);
		lane = inter->getLane(0,0);
		lane->addCarAtEnd(car);	

		//iterate to the upper bound of 17 seconds.
		for(t = 0; t < 11; t += stepTime)
		{
			eng->step(stepTime);
			//printCar(car);
			if(car->getSpeed() < 0.0001)
			{
				if( t < 9)
					return 13; //slowed down too quickly
				
				stopSpeed = true; //flag that the car did stop
				break;
			}
		}
		
		if(! stopSpeed)
			return 14; //it didn't slow down fast enough
		
		pos = car->getY();
		if(pos < bound || pos > bound + 1)
			return 15; //it did not stop at the right position
		
		lane->removeFirstCar(); //cleanup

		//todo repeat for starting less than 0.5
		return 0;
	}

	int determineLaneTest()
	{
		JPSimulationEngine *eng;
		//model->setProbability(JPIntersection::NORTHBOUND, 100, 0, 0);
		//model->setProbability(JPIntersection::SOUTHBOUND, 0, 100, 0);
		//east and west are straight

		eng = getSetup(4);
		//eng->subscribeObjectAdded(this);
		eng->init();

		//add 1000 cars in each direction
		//make sure each valid option appears and no invalid options appear
		int runs = 1000; //00;
		int i, desire, ln;
		int valids[50];
		for(i = 0; i < runs; i++)
		{
			switch(i%3)
			{
				case 0: desire = SFCar::DESIRE_LEFT; break;
				case 1: desire = SFCar::DESIRE_STRAIGHT; break;
				case 2: desire = SFCar::DESIRE_RIGHT; break;
			}

			SFCar car;
			car.setTurnDirection(desire);

			//NORTH 4 lanes 0R, 1,2S, 3L
			ln = eng->determineLane(&car, JPIntersection::NORTH);
			if(SFCar::DESIRE_LEFT == desire) //lane must be 3
				if(3 == ln )
					valids[0]++;
				else
					return 1;
			else if (SFCar::DESIRE_RIGHT == desire) //lane must be 0
				if(0 == ln )
					valids[1]++;
				else
					return 2;
			else //lane must be 1 or 2
				if(1 == ln )
					valids[2]++;
				else if(2 == ln )
					valids[3]++;
				else
					return 3;

			//SOUTH two lefs, 1 Straight, 1 straight right
			ln = eng->determineLane(&car, JPIntersection::SOUTH);
			if (SFCar::DESIRE_RIGHT == desire) //lane must be 0
				if(0 == ln )
					valids[4]++;
				else
					return 4;
			else if(SFCar::DESIRE_STRAIGHT == desire) //lane must be 0 or 1
				if(0 == ln )
					valids[5]++;
				else if(1 == ln )
					valids[6]++;
				else
					return 5;
			else //lane must be 2 or 3
				if(2 == ln )
					valids[7]++;
				else if(3 == ln )
					valids[8]++;
				else
					return 6;

			//EAST a left straight, a straight, and a right
			ln = eng->determineLane(&car, JPIntersection::EAST);
			if (SFCar::DESIRE_RIGHT == desire) //lane must be 0
				if(0 == ln )
					valids[9]++;
				else
					return 7;
			else if(SFCar::DESIRE_STRAIGHT == desire) //lane must be 1 or 2
				if(1 == ln )
					valids[10]++;
				else if(2 == ln )
					valids[11]++;
				else
					return 8;
			else //left must be 2
				if(2 == ln )
					valids[12]++;
				else
					return 9;

			//WEST1 1 left, 1 straight right straight, 1 right
			ln = eng->determineLane(&car, JPIntersection::WEST);
			if (SFCar::DESIRE_RIGHT == desire) //lane must be 0 or 1
				if(0 == ln )
					valids[13]++;
				else if(1 == ln )
					valids[14]++;
				else
					return 10;
			else if(SFCar::DESIRE_STRAIGHT == desire) //lane must be 1
				if(1 == ln )
					valids[15]++;
				else
					return 11;
			else //left must be 2
				if(2 == ln )
					valids[16]++;
				else
					return 12;
		}


		//now make sure all of excpected valid locations received cars
		for(i = 0; i <= 16; i++)
			if( ! valids[i])
				return 100+i; //100 distinguishes error codes from above

		eng->destory();
		return 0;
	}

	//add cars with two different layouts, verify they are correctly positioned
	int makeCarSubTest(int type, int numLanes)
	{
		JPSimulationEngine *eng;
		model->setProbability(JPIntersection::NORTHBOUND, 100, 0, 0);
		model->setProbability(JPIntersection::SOUTHBOUND, 0, 100, 0);
		//east and west are straight
		eng = getSetup(type);
		eng->subscribeObjectAdded(this);
		eng->init();
		int dir, ncars;
		int nruns = 10;
		position++;
		for(ncars = 0; ncars < nruns; ncars++)
			for(dir = 0; dir < 4; dir++)
			{
				_testResult = 0;
				_direction = dir;
				eng->makeCar(dir,_lane);

				//if there were any errors exit
				if(_testResult)
					return _testResult;
			}


		eng->destory();
		return -1;
	}

	int makeCarTest()
	{
		test = MAKE_CAR;
		position = 0;
		_testResult = 0;
		try{
			makeCarSubTest(1, 2);
			makeCarSubTest(2, 2);
			makeCarSubTest(3, 2);
		}catch(exception &e) { e.what(); }

		return _testResult;
	}

	void initCarCount()
	{
		for(int i = 0; i < 4; i ++)
			for(int j = 0; j < 4; j ++)
				_carCount[i][j] = 0;
	}

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
		model->setTrafficRate(JPIntersection::NORTH, 720); //5 sec pe
		model->setTrafficRate(JPIntersection::EAST, 360); //10 sec per
		model->setTrafficRate(JPIntersection::SOUTH, 275); //13.9 sec per
		model->setTrafficRate(JPIntersection::WEST, 200); //18 sec per

		//re-init to change the start times
		eng->init();

		//run 1 hr worth of sim in 0.1 sec steps
		int i, steps = 36000;
		initCarCount();
		for(i = 0; i < steps; i++)
			eng->step(0.1);

		//verify
		int target[4][4] =
			{{720, 180, 288, 252},
			{360, 90, 144, 126},
			{275, 69, 110, 96},
			{200, 50, 80, 70}
		};

		for(dir = 0; dir < 4; dir++)
		{
			//10% error acceptable for totals
			if(consts::percentError(target[dir][0], _carCount[dir][0]) > 10)
				return 1;

			//25% error acceptable for individual directions (20 caused spurious failures)
			for(i = 1; i < 4; i++)
				if(consts::percentError(target[dir][i], _carCount[dir][i]) > 25)
					return 1+i;
		}

		eng->destory();
		return 0;
	}

	int getNextCarCheck(JPSimulationEngine *eng, int dir, double leng, double x, double y, double pos)
	{
		JPCarTestStub *stub;
		stub = new JPCarTestStub(leng, x, y, 25, -5);

		JPLane *lane = inter->getLane(dir, 0);
		lane->addCarAtEnd(stub);
		lane->resetToFirstCar();
		double nleng, npos, nspeed, ndspeed;
		double dspeed = inter->getSpeedLimitsInFPS(dir) - 5 *5280.0/3600;
		SFCar *car = eng->getNextCar(lane, dir, nleng, npos, nspeed, ndspeed);
		stub = (JPCarTestStub*)car;

		//begin checks
		if(! consts::deq(nleng,leng) )
			return 1;
		if(! consts::deq(npos,pos) )
			return 2;
		if(! consts::deq(nspeed,25) )
			return 3;
		if(! consts::deq(ndspeed, dspeed) )
			return 4;

		//otherwise all is good
		return 0;
	}
	int getNextCarTest()
	{
		JPSimulationEngine *eng = getSetup(1);

		// 1) check that we get the right cars back
		int dir = 0;
		SFCar *cars[10];
		SFCar *car;
		JPLane *lane = inter->getLane(dir,1);

		int i;
		for(i = 0; i < 10; i++)
		{
			cars[i] = new SFCar();
			lane->addCarAtEnd(cars[i]);
		}

		lane->resetToFirstCar();
		double leng, pos, speed, dspeed;
		//verify A) all cars are retrieved in the correct order and NULL terminates the last
		for(i = 0; true; i++)
		{
			car = eng->getNextCar(lane, dir, leng, pos, speed, dspeed);
			if(NULL == car)
				break;

			if(i >= 10)
				return 1;
			if(cars[i] != car)
				return 2;
		}
		if( i < 10)
			return 3;

		//cleanup
		for(i = 0; i < 10; i++)
			delete lane->removeFirstCar();

		//2 check computations and retrievals
		int ret = 0;
		double inx[] = {-1,	  125,	   1, -175};
		double iny[] = {100,  1,	-150,   -1};
		double opos[]={-100,  -125, -150, -175};
		double lengs[]= {10, 12, 14, 15};
		for(dir = 0; dir < 4; dir++)
		{
			ret = getNextCarCheck(eng, dir, lengs[dir], inx[dir], iny[dir], opos[dir]);
			if(ret)
				return ret + 10 * dir;
		}

		return 0;
	}

	int prevCarDecelTest()
	{
		JPSimulationEngine eng;

		//getPrevCarDecel(pSpeed, pPos, speed, dSpeed, pos, timeStep)
		double accel, expected;

		//test 1 no previous car, going desired speed
		accel = eng.getPrevCarDecel(-1, 0, 32, 32, 100, 0.1);
		if(! consts::deq(accel,0))
			return 1;

		//test 2 no previous car, going slower than desired speed
		accel = eng.getPrevCarDecel(-1, 0, 32, 100, 100, 0.1);
		expected = 5 * 5280./3600;
		if(! consts::deq(accel,expected))
			return 2;

		//test 3 no previous car, going slower accel bound by dspeed
		accel = eng.getPrevCarDecel(-1, 0, 32, 32.5, 100, 0.1);
		expected = .5 /.1;
		if(! consts::deq(accel,expected))
			return 3;


		//test 4 previous car, no change need
		accel = eng.getPrevCarDecel(0, 5, 60, 60, -1075, 0.1);
		expected = 0;
		if(! consts::deq(accel,expected))
			return 4;

		//test 5 previous car stopped
		//getPrevCarDecel(pSpeed, pPos, speed, dSpeed, pos, timeStep)
		accel = eng.getPrevCarDecel(0, 5, 60, 60, -175, 0.1);
		expected = -10;
		if(! consts::deq(accel,expected))
			return 5;

		//test 6 previous car stopped (slow per car accel)
		//getPrevCarDecel(pSpeed, pPos, speed, dSpeed, pos, timeStep)
		accel = eng.getPrevCarDecel(0, 5, 60, 60, -238, 0.1);
		expected = -7.33;
		//printf("%f\t%f\n", accel, expected);
		if(! consts::deq(accel,expected))
			return 6;

		//todo maybe more
		return 0;
	}
public:
	int run()
	{
		int ret;
		ret = consts::testOuptut(
				"JPSimulationEngine: Prerequisites",
				prereqTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Get Next Car Test",
				getNextCarTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Make Car Test",
				makeCarTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Determine Lane Test",
				determineLaneTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Previous Car Deceleration Test",
				prevCarDecelTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Match Pace Test",
				matchPaceTest() );
		ret = consts::testOuptut(
				"JPSimulationEngine: Rear Car Acceleration Test",
				rearCarAccelerationTest() );

printf("Ret: %d\n", ret);
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
				"JPSimulationEngine: Red Light Stop Test",
				redLightStopTest() );

		//long tests
		if(false)
		{
			ret = consts::testOuptut(
					"JPSimulationEngine: Add Car Test",
					addCarTest() );

		}
		return ret;
	}

	void printIntersection()
	{
		int dir, ln;
		JPLane *lane;
		SFCar *car;
		for(dir = 0; dir < 4; dir++)
		{
//if(3 != dir) continue;
			printf("Direction: %d\n", dir);
			for(ln = 0; ln < inter->getLaneCount(dir); ln++)
			{
				lane = inter->getLane(dir,ln);
				lane->resetToFirstCar();
				while(0 != (car = lane->getNextCar()) )
				   this->printCar(car);
			}
		}
	}

	void demo()
	{
		JPSimulationEngine *eng = getSetup(1);
		int dir;
		for(dir = 0; dir < 4; dir++)
			model->setProbability(dir, 0,0,25);
		model->setTrafficRate(JPIntersection::SOUTHBOUND, 1200);
		model->setTrafficRate(JPIntersection::NORTHBOUND, 1200);
		model->setTrafficRate(JPIntersection::EASTBOUND, 1200);
		eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::Cases::GREEN_NS));
		eng->init();

		printf("Ctrl+c to exit\n");
		long cycles = 0;
		for(cycles = 0; 1; cycles++)
		{
			eng->step(0.1);
#ifndef NIX_IS_HERE
			Sleep(100);
#endif
			if(cycles % 10 == 0) //print every 1 seconds
			{
				printf("Time: %f\n", JPSimulationEngine::getInstance()->getTime());
				printIntersection();
			}
		}


	}
	SETestClass()
	{
		light = NULL;
		model = NULL;
		inter = NULL;
		_lane = 0;

		test = NULL_TEST;
		position = 0;
		_testResult = 0;
		_direction = 0;


		int dir, j;
		for(dir = 0; dir < 4; dir++)
		{
			for(j = 0; j < 4; j++)
				_carCount[dir][j] = 0;
		}
	}

};

int main(int argc, char *argv[])
{
	//put all the test code in the class so the destroy
	//function can be private non static
	SETestClass test;
	if(2 == argc && 0 == strcmp("-d", argv[1]))
		test.demo();
	else
		test.run();
	return 0;
}

/** @} */
