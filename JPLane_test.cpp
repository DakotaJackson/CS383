/*
 * JPLane_test.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: james
 */

#include "JPLane.h"
#include <stdio.h>
#include "JPConstants.h"
#include <stdexcept>
#include "JPCarTestStub.h"

int iterateTest();
int removeCarTest();
int addCarAtPositionTest();
int removeCarEarlyTest();
int laneDirectionBitFieldCheck();


int main()
{
	int ret;
	ret = consts::testOuptut(
			"JPLane: constants: Lane Direction Bit Field Check",
			laneDirectionBitFieldCheck());

	ret = consts::testOuptut(
			"JPLane: Iterate Test",
			iterateTest() );
	ret = consts::testOuptut(
			"JPLane: Remove Car Test",
			removeCarTest() );


	ret = consts::testOuptut(
			"JPLane: Add Car At Position Test",
			addCarAtPositionTest() );


	ret = consts::testOuptut(
			"JPLane: Remove Car Early Test",
			removeCarEarlyTest() );
	/**/
	if(ret == 102) printf ("Will the compiler ever leave ret alone?");

	return 0;
}

int laneDirectionBitFieldCheck()
{
	int sumField = JPLane::STRAIGHT;

	//check against right
	if( ((sumField | JPLane::RIGHT) == sumField)&&
			((sumField & JPLane::RIGHT) == 0))
		return 1;
	sumField += JPLane::RIGHT;


	//check against left
	if( ((sumField | JPLane::LEFT) == sumField) &&
			((sumField & JPLane::LEFT) == 0))
		return 1;

	return 0;
}


inline int iterateTest()
{
	//add some cars
	//verify they are there
	//reset verify they are still there
	//start scanning reset midway, verify scans correctly
	//delete lane

	JPLane *lane;
	lane = new JPLane(JPLane::STRAIGHT, 0, 0);
	Car *car;

	//add cars
	int i;
	Car *cars[10];
	for(i = 0; i < 10; i++)
	{
		cars[i] = new Car();
		lane->addCarAtEnd(cars[i]);
	}

	//iterate once
	lane->resetToFirstCar();
	int end = lane->getSize();
	if(10 != end)
		return 1;
	for(i = 0; i < end; i++)
	{
		car = lane->getNextCar();
		if( cars[i] != car)
			return 2;
	}
	if(NULL != lane->getNextCar() )
		return 3;


	//iterate second time
	lane->resetToFirstCar();
	for(i = 0; i < 10; i++)
	{
		car = lane->getNextCar();
		if( cars[i] != car)
			return 4;
	}
	if(NULL != lane->getNextCar() )
		return 5;


	delete lane;
	return 0;
}

/**
 * \brief Test the removal of the first car.
 */
inline int removeCarTest()
{
	//add some cars
	//remove the first
	//verify all but the first are there
	//repeat until lane is empty


	JPLane *lane;
	lane = new JPLane(JPLane::STRAIGHT, 0, 0);
	Car *car, *remCar;

	//add cars
	int i,j;
	Car *cars[10];
	for(i = 0; i < 10; i++)
	{
		cars[i] = new Car();
		//printf("[%d]:\t%d\n", i, cars[i]);
		lane->addCarAtEnd(cars[i]);
	}

	//test
	for(i = 0; i < 10; i++)
	{
		//remove car and get new first
		remCar = lane->removeFirstCar();
		lane->resetToFirstCar();

		//check that the returned car is the i'th car
		//and that cars beyond the i'th car are still there
		for(j = 0; j < 10; j++)
		{
			if(i==j)
			{
				//printf("[i:j:%d]\t %d\t%d\n", i, cars[i], remCar);
				if( remCar != cars[i])
					return 1;
			}
			else if (j > i)
			{
				car = lane->getNextCar();
				//printf("[%d][%d]\t %d\t%d\n", i, j, cars[j], car);
				if( car != cars[j])
					return 2;
			}
		} //end j
	}//end i

	delete lane;
	return 0;
}

inline int addCarAtPositionTest()
{
	//TODO write this test
	//add some cars
	//add one at a specified position
//	return -1;

	JPLane *lane;
	lane = new JPLane(JPLane::STRAIGHT, 0, 0);
	Car *car;

	//add cars
	int i;
	Car *cars[10];
	for(i = 0; i < 9; i++)
	{
		//skip numbers 0 and 5;
		if(5 == i || 0 == i)
			i++;
		//JPCarTestStub(double leng, double X, double Y, double speed, double dspeed);
		cars[i] = new JPCarTestStub(10, i * -20, 1, 35, 0);
		//printf("[%d]:\t%d\n", i, cars[i]);
		lane->addCarAtEnd(cars[i]);
	}

	//add at front (0)
	car = new JPCarTestStub(10, 0 * -20, 1, 35, 0);
	lane->addCarAtPos(car, JPIntersection::EASTBOUND); //increasing the positive X direction
	cars[0] = car;

	//add at 5
	car = new JPCarTestStub(10, 5 * -20, 1, 35, 0);
	lane->addCarAtPos(car, JPIntersection::EASTBOUND); //increasing the positive X direction
	cars[5] = car;

	//add at end (9)
	car = new JPCarTestStub(10, 9 * -20, 1, 35, 0);
	lane->addCarAtPos(car, JPIntersection::EASTBOUND); //increasing the positive X direction
	cars[9] = car;


	//test
	lane->resetToFirstCar();
	for(i = 0; i < 10; i++)
	{
		car = lane->getNextCar();
		if(car != cars[i])
			return i+1;
	}

	delete lane;
	return 0;
}


inline int removeCarEarlyTest()
{
	//add some cars
	//remove a car from the middle to simulate a lane change
	//verify correct car was removed

	JPLane *lane;
	lane = new JPLane(JPLane::STRAIGHT, 0, 0);
	Car *car;

	//add cars
	int i;
	Car *cars[10];
	for(i = 0; i < 10; i++)
	{
		cars[i] = new Car();
		//printf("[%d]:\t%d\n", i, cars[i]);
		lane->addCarAtEnd(cars[i]);
	}

	//remove car number 5;
	lane->resetToFirstCar();
	for(i = 0; i < 10; i++)
	{
		lane->getNextCar();
		if( 5 == i)
		{
			cars[i] = 0;
			lane->removeCurrentCar();
		}
	}

	//test
	lane->resetToFirstCar();
	for(i = 0; i < 10; i++)
	{
		//skip over 5 because it shoudln't be there
		if( 5 == i)
			i++;

		car = lane->getNextCar();

		if(car != cars[i])
			return 1;
	}

	delete lane;
	return 0;
}
