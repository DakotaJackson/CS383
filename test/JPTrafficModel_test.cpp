/*
 * TrafficModel_test.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: james
 */

#include <stdio.h>
#include "../inc/JPTrafficModel.h"
#include "../inc/JPConstants.h"
#include "../inc/JPIntersection.h"


int directionOutOfBoundsTest();
int rateLessThanZeroTest();
int probabilityLessThanZeroTest();
int distributionTests();
int main()
{

	// "\033[32mtext[\033[0m" change 32 to 31 for red. Not working on MSYS
	consts::testOuptut("JPTrafficModel: Direction Out Of Bounds Test",
			directionOutOfBoundsTest() );
	consts::testOuptut("JPTrafficModel: Rate Less Than Zero Test",
			rateLessThanZeroTest() );
	consts::testOuptut("JPTrafficModel: Probability Less Than Zero Test",
			probabilityLessThanZeroTest() );
	distributionTests();

	return 0;
}

/**
 * Verify that direction out of bounds is properly thrown when the direction is out of bounds.
 */
inline int directionOutOfBoundsTest()
{
	JPTrafficModel tm;

	try//test probability direction low
	{
		tm.setProbability(-1, 1, 2, 3);
		return 1;
	}
	catch(JPDirectionOutOfBoundsException &ex){}

	try//test probability direction high
	{
		tm.setProbability(5, 1, 2, 3);
		return 1;
	}
	catch(JPDirectionOutOfBoundsException &ex){}

	try//test traffic rate direction high
	{
		tm.setTrafficRate(5,25);
		return 1;
	}
	catch(JPDirectionOutOfBoundsException &ex){}

	try//test traffic rate direction low
	{
		tm.setTrafficRate(-1,25);
		return 1;
	}
	catch(JPDirectionOutOfBoundsException &ex){}

	return 0;
}

inline int rateLessThanZeroTest()
{
	JPTrafficModel tm;
	try//test traffic rate less than 0
	{
		tm.setTrafficRate(0,-1);
		return 1;
	}
	catch(JPRateLessThanZeroException &ex){}

	return 0;
}

inline int probabilityLessThanZeroTest()
{
	JPTrafficModel tm;
	try//test right probability less than 0
	{
		tm.setProbability(2	, -1, 2, 3);
		return 1;
	}
	catch(JPProbabilityLessThanZeroException &ex){}

	try//test left probability less than 0
	{
		tm.setProbability(3, 1, 2, -1);
		return 1;
	}
	catch(JPProbabilityLessThanZeroException &ex){}

	try//test straight probability less than 0
	{
		tm.setProbability(3, 1, 2, -1);
		return 1;
	}
	catch(JPProbabilityLessThanZeroException &ex){}

	try //verify zeros do not throw the exception
	{
		tm.setProbability(3, 0, 0, 0);
		return 0;
	}
	catch(JPProbabilityLessThanZeroException &ex)
	{
		return 1;
	}

	return -1;
}

inline int distributionTests()
{
	//same data is used for both tests.

	JPTrafficModel tm;
	tm.setProbability(JPIntersection::NORTH,15,60,25); // -> no more than 10% error in distribution
	tm.setProbability(JPIntersection::SOUTH,10,0,0); // -> Only left turns
	tm.setProbability(JPIntersection::EAST,0,10,0); // -> Only right turns
	tm.setProbability(JPIntersection::WEST,0,0,10); // -> Only straight
	tm.setTrafficRate(JPIntersection::NORTH, 1);
	tm.setTrafficRate(JPIntersection::SOUTH, 10);
	tm.setTrafficRate(JPIntersection::EAST, 100);
	tm.setTrafficRate(JPIntersection::WEST, 1000);

	//20,000 calls getNextTiming()
	int i,dir, dest;
	double time;
	double sumTime[4];
	int dircounter[4][3];
	for(i = 0; i < 20000; i++)
	{
		for(dir = 0; dir < 4; dir++)
		{
			time = tm.getNextTiming(dir);
			sumTime += time; //add to sum for future averaging
			//todo add to

			//check destination and increment appropriately
			dest = tm.getNextTurnDirection(dir);
			//todo check against actual direction from SFCar
			if(0 == dest)
				dircounter[dir][0]++;
			else if(1 == dest)
				dircounter[dir][1]++;
			else if(2 == dest)
				dircounter[dir][2]++;

		}
	}

	//verify distributions.
	//todo verify outputs
	consts::testOuptut("JPTrafficModel: Direction Distribution Test", -1);
	consts::testOuptut("JPTrafficModel: Rate Distribution Test", -1);
/*
	int i,j;
	for(i = 0; i < 50; i++)
		printf("%f\n", tm.getNextTiming(JPIntersection::EAST,j));
*/
	return -1;
}
