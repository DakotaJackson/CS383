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
	_speedLimits[1] = 35;

	//set all of these to default values
	//or to -1 flagging them as not set
	int i,j;
	for(i = 0; i < 4; i++)
	{
		_laneOffsets[i] = -1;
		_laneCounts[i] = 0;
		_laneLengths[i] = 5280/4;
		for(j = 0; j < MAX_LANES; j++)
		_lanes[i][j] = NULL;
	}
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
	//if we already checked we're good
	if(_finalized)
		return;

	//make sure all lanes are present
	int dir, ln;
	for(dir = 0; dir < 4; dir++)
		for(ln = 0; ln < _laneCounts[dir]; ln++)
			if( NULL == _lanes[dir][ln])
				throw JPConfigurationOrderException(JPConfigurationOrderException::FINALIZE_MISSING_LANES);

	_finalized = true;
}


/**
 * \brief set the offset (in lanes) of the rightmost lane.
 *
 * This function is used to setup the physical configuration of the lane. It sets how far from the center
 * of the intersection the first lane should start measured in lanes. For example consider an intersection
 * with 3 south bound lanes and 3 northbound lanes. For both directions
 * \throw JPLaneOffsetException if any offset is less than 1.
 * \throw JPConfigurationOrderException if any lanes have already been added
 */
void JPIntersection::setLaneOffsets(double north, double south, double east,
		double west)
{
	if(north < 1 || south < 1 || east < 1 || west < 1)
		throw JPLaneOffsetException();

	int dir;
	for(dir = 0; dir < 4; dir++)
		if(0 != _laneCounts[dir])
			throw JPConfigurationOrderException(JPConfigurationOrderException::CONFIG_OFFSET_AFTER_LANES);

	_laneOffsets[JPIntersection::NORTH] = north;
	_laneOffsets[JPIntersection::SOUTH] = south;
	_laneOffsets[JPIntersection::EAST] = east;
	_laneOffsets[JPIntersection::WEST] = west;

}

/**
 * This function is used to setup the physical configuration of the lane. It sets how far from the center
 * of the intersection the first lane should start measured in lanes. For example consider an intersection
 * with 3 south bound lanes and 3 northbound lanes. For both directions
 * \throw JPLaneOffsetException if any offset is less than 1.
 * \throw JPConfigurationOrderException if any lanes have already been added
 * \copydoc JPIntersection::validateDirection()
 */
void JPIntersection::setLaneOffset(int direction, double offset)
{
	validateDirection(direction);
	if(offset < 1)
		throw JPLaneOffsetException();

	int dir;
	for(dir = 0; dir < 4; dir++)
		if(0 != _laneCounts[dir])
			throw JPConfigurationOrderException(JPConfigurationOrderException::CONFIG_OFFSET_AFTER_LANES);

	_laneOffsets[direction] = offset;
}


void JPIntersection::setTrackedLaneLengths(double north, double south,
		double east, double west)
{
	setTrackedLaneLength(NORTH, north);
	setTrackedLaneLength(SOUTH, south);
	setTrackedLaneLength(EAST, east);
	setTrackedLaneLength(WEST, west);
}
/**
 * \copydoc JPIntersection::validateDirection()
 */
void JPIntersection::setTrackedLaneLength(int direction, double distance)
{
	validateDirection(direction);

	//enforce maximum and minimum distances
	if(distance < MIN_LANE_LENG)
		distance = MIN_LANE_LENG;
	if(distance > MAX_LANE_LENG)
		distance = MAX_LANE_LENG;

	_laneLengths[direction] = distance;
}

void JPIntersection::setTrackedExitLengths(double northSouth,
		double eastWest)
{
	setTrackedExitLaneLength(0, northSouth);
	setTrackedExitLaneLength(1, eastWest);
}
void JPIntersection::setTrackedExitLaneLength(int direction, double distance)
{
	//enforce maximum and minimum distances
	if(distance < MIN_LANE_LENG)
		distance = MIN_LANE_LENG;
	if(distance > MAX_LANE_LENG)
		distance = MAX_LANE_LENG;

	_laneExit[direction] = distance;
}


void JPIntersection::addLaneBasicChecks(int direction, int position)
{
	//check position and direction
	validateDirection(direction);
	if(position >= MAX_LANES || position < 0)
		throw JPLaneNumberOutOfBoundsException(position);

	//make sure offsets are configured
	int dir;
	for(dir = 0; dir < 4; dir++)
		if(-1 == _laneOffsets[dir])
			throw JPConfigurationOrderException(JPConfigurationOrderException::CONFIG_LANES_BEFORE_OFFSET);

	//make sure the intersection is not finalized
	if(_finalized)
		throw JPConfigurationOrderException(JPConfigurationOrderException::CONFIG_FINALIZED);
}

void JPIntersection::addLaneInterferenceChecks(int direction, int position, int turnOptions,
		int leftTarget, int rightTarget)
{
	//todo check lane overlap, two into one, left crossing, others?
}

/**
 * \copydoc JPIntersection::validateDirection()
 * \throw JPLaneNumberOutOfBoundsException if the lane number exceeds JPIntersection::MAX_LANES
 * \throw JPTwoLanesToOneException if the specified rightTarget or leftTarget will cause the added lane to turn into the same lane as an existing lane
 * \throw JPLaneCollidesWithOncomingLaneException if the added lane will collide with an oncomming lane
 * \throw JPTurningLaneCrossingStraightLaneException if A) the added lane is a right turn lane and there is a lane to the right that permits straight, B) if the added lane is a left turn lane and there is a lane to the left that permits straight, or C) the added lane permits straight and there is either a right turn lane to the left or a left turn lane to the right
 * \throw JPConfigurationOrderException if lane offsets have not been configured.
 */
void JPIntersection::addLane(int direction, int position, int turnOptions,
		int leftTarget, int rightTarget)
{
	addLaneBasicChecks(direction,position);
	addLaneInterferenceChecks(direction, position, turnOptions,leftTarget,rightTarget);

	//if a lane already exits here, delete the old one
	if(0 != _lanes[direction][position])
		delete _lanes[direction][position];

	JPLane *lane = new JPLane(turnOptions, leftTarget, rightTarget );
	_lanes[direction][position] = lane;
	_laneCounts[direction] = std::max(_laneCounts[direction], position + 1);
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
double JPIntersection::getLaneOffset(int direction)
{
	validateDirection(direction);
	return _laneOffsets[direction];
}

/**
 * \copydoc JPIntersection::validateDirection()
 */
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

/**
 * \copydoc JPIntersection::validateDirection()
 */
int JPIntersection::getLaneCount(int direction)
{
	validateDirection(direction);
	return _laneCounts[direction];
}

/**
 * \param direction Zero for north/south, 1 for east/west
 * \copydoc JPIntersection::validateDirection()
 */
double JPIntersection::getTrackedExitLength(int direction)
{
	validateDirection(direction);
	return _laneExit[direction % 2];
}

/**
 * \copydoc JPIntersection::validateDirection()
 * \throw JPLaneNumberOutOfBoundsException if the lane number does not correspond to an existing lane
 */
JPLane* JPIntersection::getLane(int direction, int position)
{
	validateDirection(direction);
	if( position >= _laneCounts[direction] || position < 0)
		throw JPLaneNumberOutOfBoundsException(position);

	return _lanes[direction][position];
}
