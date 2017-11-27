/*
 * JPIntersection.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: james
 */

#include "../../inc/JPIntersection.h"
#include "../../inc/JPIntersectionExceptions.h"

JPIntersection::JPIntersection()
{
	//lane exists have defaults
	_laneExit[0] = 600.0;
	_laneExit[1] = 600.0;
	_finalized = false;
	_speedLimits[0] = 35;
	_speedLimits[1] = 35; //TODO change these to -1 flags?

	//set all of these to default values
	//or to -1 flagging them as not set
	int i,j;
	for(i = 0; i < 4; i++)
	{
		_laneOffsets[i] = -1;
		_laneCounts[i] = 0;
		_laneLengths[i] = 5280;
		for(j = 0; j < MAX_LANES; j++)
		_lanes[i][j] = 0;
	}
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
void JPIntersection::setLaneOffset(int direction, double offset)
{
	validateDirection(direction);
	/*

	if(offset <= 0)
		throw TODO;
	if( oposing offset is not the same (e.g. both must be x.0 or x.5))
	 	 throw TODO
	*/

	_laneOffsets[direction] = offset;
}

/**
 * \copydoc JPIntersection::validateDirection()
*/
void JPIntersection::setTrackedLaneLength(int direction, double distance)
{
	validateDirection(direction);

	//enforce maximum and minimum distances
	if(distance < 150)
		distance = 150;
	if(distance > MAX_LANE_LENG)
		distance = MAX_LANE_LENG;

	_laneLengths[direction] = distance;
}

/**
 * \throw JPMalformedIntersectionException if either speed limit is less than 5 mph (direction = 0 if northSouth is less than 5, direction = 1 if eastWest is less than 5)
 */
void JPIntersection::setSpeedLimits(double northSouth, double eastWest)
{
	if(northSouth < 5)
		throw JPMalformedIntersectionException(0);
	if(eastWest < 5)
		throw JPMalformedIntersectionException(1);

	_speedLimits[0] = northSouth;
	_speedLimits[1] = eastWest;
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
double JPIntersection::getTrackedLaneLength(int direction)
{
	validateDirection(direction);
	return _laneLengths[direction];
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
double JPIntersection::getSpeedLimits(int direction)
{
	validateDirection(direction);
	return _speedLimits[direction % 2];
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
double JPIntersection::getSpeedLimitsInFPS(int direction)
{
	validateDirection(direction);
	return _speedLimits[direction % 2] * 5280.0/3600;
}

JPIntersection::~JPIntersection()
{
	int i,j;
	for(i = 0; i< 4; i++)
		for(j = 0; j < _laneCounts[i]; j++)
			delete _lanes[i][j];
}

/**
 *
 */
void JPIntersection::finalize()
{
	_finalized = true;
}

/**
 * \brief set the offset (in lanes) of the rightmost lane.
 *
 * This function is used to setup the physical configuration of the lane. It sets how far from the center
 * of the intersection the first lane should start measured in lanes. For example consider an intersection
 * with 3 south bound lanes and 3 northbound lanes. For both directions
 *
 */
void JPIntersection::setLaneOffsets(double north, double south, double east,
		double west)
{
	//todo checks
	_laneOffsets[JPIntersection::NORTH] = north;
	_laneOffsets[JPIntersection::SOUTH] = south;
	_laneOffsets[JPIntersection::EAST] = east;
	_laneOffsets[JPIntersection::WEST] = west;

}

void JPIntersection::setTrackedLaneLengths(double north, double south,
		double east, double west)
{
	//todo checks

	setTrackedLaneLength(NORTH, north);
	setTrackedLaneLength(SOUTH, south);
	setTrackedLaneLength(EAST, east);
	setTrackedLaneLength(WEST, west);
}

void JPIntersection::setTrackedExitLengths(double northSouth,
		double eastWest)
{
	//todo checks
//printf("%f\t%f\n", northSouth, eastWest);
	_laneExit[0] = northSouth;
	_laneExit[1] = eastWest;
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
void JPIntersection::addLane(int direction, int position, int turnOptions,
		int leftTarget, int rightTarget)
{
	validateDirection(direction);
	if(position > MAX_LANES)
		throw JPLaneNumberOutOfBoundsException(position);

	//todo check lane overlap, two into one, left crossing, others?
	if(0 != _lanes[direction][position])
		delete _lanes[direction][position];

	JPLane *lane = new JPLane(turnOptions, leftTarget, rightTarget );
	_lanes[direction][position] = lane;
	_laneCounts[direction] = std::max(_laneCounts[direction], position + 1);
}

double JPIntersection::getLaneOffset(int direction)
{
	validateDirection(direction);
	return _laneOffsets[direction];
}

double JPIntersection::getLaneOffsetInFeet(int direction)
{
	validateDirection(direction);
	return 10.0 * _laneOffsets[direction];
}

void JPIntersection::getLaneCounts(int counts[])
{
	int i;
	for(i = 0; i < 4; i++)
		counts[i] = _laneCounts[i];
}

int JPIntersection::getLaneCount(int direction)
{
	validateDirection(direction);
	return _laneCounts[direction];
}

/**
 * \param direction Zero for north/south, 1 for east/west
 */
double JPIntersection::getTrackedExitLength(int direction)
{
	validateDirection(direction);
	return _laneExit[direction % 2];
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
JPLane* JPIntersection::getLane(int direction, int position)
{
	validateDirection(direction);
	//todo validate position
	return _lanes[direction][position];
}
