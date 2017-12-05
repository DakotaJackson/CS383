/*
 * TrafficModel_test.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: james
 */

#include <stdio.h>
#include <math.h>
#include "JPTrafficModel.h"
#include "JPConstants.h"
#include "JPIntersection.h"

//The number of calls to
#define ITERATIONS 20000
//20000

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
int directionOutOfBoundsTest()
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

int rateLessThanZeroTest()
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

int probabilityLessThanZeroTest()
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

	return 0;
}


double rateCheck(double expected, double total, int iterations)
{
	double rate;
	if(0 == total)
		rate = 0;
	else
		rate = 3600 * iterations / total;
//printf("%f\t%f\n", expected, rate);
	return consts::percentError(expected, rate);
}

double varianceCheck(double expRate, double stdDev)
{
	//zero is a special case due to infinite time
	if(0 == stdDev)
		return consts::percentError(expRate, 0);

	//for Poisson distribution the mean and variance are the same
	//stdDev is calculated in seconds not rate
	double expTime = 3600 / expRate; //convert rate to time.
	double variance = stdDev * stdDev; //variance is stdDev^2
	return consts::percentError(expTime, variance);
}

int timingCheck(double sumTime[4], double times[4][ITERATIONS] )
{
	int rateFail = 0;
	int dir;
	double stdDev[4];

	//for clarity and brevity
	const int NORTH = JPIntersection::NORTH;
	const int SOUTH = JPIntersection::SOUTH;
	const int EAST = JPIntersection::EAST;
	const int WEST = JPIntersection::WEST;

	//verify average output times
	//N 0, S 10, E 100, W 1000
	if(rateCheck(0, sumTime[NORTH], ITERATIONS ) > 2.0 )  rateFail += 2;
	if(rateCheck(10, sumTime[SOUTH], ITERATIONS ) > 2.0 ) rateFail += 4;
	if(rateCheck(100, sumTime[EAST], ITERATIONS ) > 2.0 ) rateFail += 8;
	if(rateCheck(1000, sumTime[WEST], ITERATIONS ) > 2.0 )rateFail += 16;
	if(rateFail)
		rateFail += 1; //distinguish between rate failure and variance failure
	else //if no rate failures, test variance
	{
		for(dir = 0; dir < 4; dir++)
			stdDev[dir] = consts::computeStdDev(times[dir], sumTime[dir]/ITERATIONS, ITERATIONS);

		if(varianceCheck(0, stdDev[NORTH] ) > 5.0 )  rateFail += 2;
		if(varianceCheck(10, stdDev[SOUTH] ) > 5.0 ) rateFail += 4;
		if(varianceCheck(100, stdDev[EAST] ) > 5.0 ) rateFail += 8;
		if(varianceCheck(1000, stdDev[WEST] ) > 5.0 )rateFail += 16;
	}
	return rateFail;
}

int directionDistributionCheck(int dCtr[4][3])
{
	/*
	 *	L,R,C
	 * N:15,60,25
	 * S: 1,,0
	 * E: 0,1,0
	 * W: 0,0,1
	 */
	int errField = 0;

	//for clarity and brevity
	const int NORTH = JPIntersection::NORTH;
	const int SOUTH = JPIntersection::SOUTH;
	const int EAST = JPIntersection::EAST;
	const int WEST = JPIntersection::WEST;

	//compute percentages for north
	double lperc = 15. / (15 + 60 + 25);
	double rperc = 60. / (15 + 60 + 25);
	double sperc = 25. / (15 + 60 + 25);
	if( consts::percentError( lperc, (double)dCtr[NORTH][0]/ITERATIONS) > 5.0)
		errField += 1;
	if( consts::percentError( rperc, (double)dCtr[NORTH][1]/ITERATIONS) > 5.0)
		errField += 1;
	if( consts::percentError( sperc, (double)dCtr[NORTH][2]/ITERATIONS) > 5.0)
		errField += 1;

	//check that all iterations yielded the correct turn direction for E,W,S
	if(ITERATIONS !=  dCtr[SOUTH][0])
		errField += 2;
	if(dCtr[EAST][1] != ITERATIONS)
		errField += 4;
	if( dCtr[WEST][2] != ITERATIONS)
		errField += 8;

	return errField;
}

/**
 * \brief Check the distributions
 */
int distributionTests()
{
	//same data is used for both tests.
	//setup the model
	JPTrafficModel tm;
	tm.setProbability(JPIntersection::NORTH,15,60,25); // -> no more than 5% error in distribution
	tm.setProbability(JPIntersection::SOUTH,10,0,0); // -> Only left turns
	tm.setProbability(JPIntersection::EAST,0,10,0); // -> Only right turns
	tm.setProbability(JPIntersection::WEST,0,0,10); // -> Only straight
	tm.setTrafficRate(JPIntersection::NORTH, 0);  //no more than 2% error in mean, and 5% in variance
	tm.setTrafficRate(JPIntersection::SOUTH, 10);
	tm.setTrafficRate(JPIntersection::EAST, 100);
	tm.setTrafficRate(JPIntersection::WEST, 1000);

	int i, j, dir, dest;
	double time;
	double sumTime[4];
	int dircounter[4][3];
	double times[4][ITERATIONS];

	//initialize probably unnecessary but a good practice.
	for(i = 0; i < 4; i++)
	{
		sumTime[i] = 0;
		for(j = 0; j < 3; j++)
		{
			dircounter[i][j] = 0;
		}
	}

	//20,000 calls getNextTiming()
	for(i = 0; i < ITERATIONS; i++)
	{
		for(dir = 0; dir < 4; dir++)
		{
			time = tm.getNextTiming(dir);
			if( time >= 0 )
			{
					sumTime[dir] += time; //add to sum for future averaging
					times[dir][i] = time;
			}
			else
				times[dir][i] = 0;

			//check destination and increment appropriately
			dest = tm.getNextTurnDirection(dir);
			//todo check against actual direction from Car
			if(Car::DESIRE_LEFT == dest) //left
				dircounter[dir][0]++;
			else if(Car::DESIRE_RIGHT == dest) //right
				dircounter[dir][1]++;
			else if(Car::DESIRE_STRAIGHT == dest) //straight
				dircounter[dir][2]++;
		}
	}

	//verify distributions.
	int rateFail = timingCheck(sumTime, times);
	int dirFail = directionDistributionCheck(dircounter);

	consts::testOuptut("JPTrafficModel: Direction Distribution Test", dirFail);
	consts::testOuptut("JPTrafficModel: Rate Distribution Test", rateFail);

	return (rateFail<<4) + dirFail;
}
