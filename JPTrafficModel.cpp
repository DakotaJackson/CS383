/*
 * JPTrafficModel.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: james
 */

#include "JPTrafficModel.h"
#include "JPTrafficModelExceptions.h"
#include "JPIntersection.h"
#include <chrono> //for seeding
#include "SFCarGen.h"

JPTrafficModel::JPTrafficModel()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		_rate[i] = 1.0;
		_turnCDF[i][0] = 0.0;
		_turnCDF[i][1] = 1.0;
		_turnCDF[i][2] = 2.0;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	gen = new std::default_random_engine(seed);
	uniform = new std::uniform_real_distribution<double>(0.0, 1.0);

	//todo set direction map
	_directionMappings[0] = Car::DESIRE_LEFT;
	_directionMappings[1] = Car::DESIRE_RIGHT;
	_directionMappings[2] = Car::DESIRE_STRAIGHT;
}

/**
 * \throws JPDirectionOutOfBoundsException If direction is not one of those defined in \link JPIntersection \endlink
 * \throws JPProbabilityLessThanZeroException If any probability is less than zero.
 */
void JPTrafficModel::setProbability(int direction, double left, double right, double straight)
{
	//validate
	if(left < 0)
		throw JPProbabilityLessThanZeroException();
	if(right < 0)
		throw JPProbabilityLessThanZeroException();
	if(straight < 0)
		throw JPProbabilityLessThanZeroException();
	JPIntersection::validateDirection(direction);

	_turnCDF[direction][0] = left;
	_turnCDF[direction][1] = _turnCDF[direction][0] + right;
	_turnCDF[direction][2] = _turnCDF[direction][1] + straight;
}

/**
 * \throws JPDirectionOutOfBounds if direction is not one of those defined in \link JPIntersection \endlink
 * \throws JPRateLessThanZeroException if the rate is negative.
 */
void JPTrafficModel::setTrafficRate(int direction, double rate)
{
	JPIntersection::validateDirection(direction);
	if(rate < 0)
		throw JPRateLessThanZeroException();

	_rate[direction] = rate;
	poisson[direction] = new poisson_distribution<long>(3600/rate);
}


double JPTrafficModel::getNextTiming(int direction)
{
	//don't try to return infinity
	if(0 == _rate[direction])
		return -1.0;

	//return Poisson distributed time
	return (*poisson[direction])(*gen);
}

int JPTrafficModel::getNextTurnDirection(int direction)
{
	//Get a uniformly distributed value and multiply
	//by the maximum value of the CDF
	double p = (*uniform)(*gen);
	p *= _turnCDF[direction][2];

	//Iterate over the cumulative distribution function
	//Price is Right style (as close without going over)
	//The highest index reached without exceeding p is
	//the chosen direction
	int i;
	for(i = 0; p > _turnCDF[direction][i] && i < 3; i++);

	return _directionMappings[i];
}

JPTrafficModel::~JPTrafficModel(){}

