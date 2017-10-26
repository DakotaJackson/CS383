/*
 * IntersectionExceptions.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#include "../../inc/JPIntersectionExceptions.h"

JPMalformedIntersectionException::JPMalformedIntersectionException()
{
	_direction = -1;
	_lane = -1;
}
JPMalformedIntersectionException::JPMalformedIntersectionException(int direction)
{
	_direction = direction;
	_lane = -1;
}
JPMalformedIntersectionException::JPMalformedIntersectionException(int direction, int lane)
{
	_direction = direction;
	_lane = lane;
}

JPMalformedIntersectionException::~JPMalformedIntersectionException() throw()
{
	// TODO Auto-generated destructor stub
}

int JPMalformedIntersectionException::getOriginationLane()
{
	return _lane;
}

int JPMalformedIntersectionException::getDirection()
{
	return _direction;
}

const char* JPMalformedIntersectionException::what() const throw ()
{
	return "The intersection is not build correctly!";
}
//collide colliding
JPTwoLanesToOneException::JPTwoLanesToOneException(int direction, int thisLane, int targetLane, int collidingLane ):
		JPMalformedIntersectionException(direction, thisLane)
{
	_targetLane = targetLane;
	_collidingLane = collidingLane;
}

const char* JPTwoLanesToOneException::what() const throw ()
{
	return "The lane you are trying to add turns into a lane that already receives turning cars from another lane. ";
}

int JPTwoLanesToOneException::getTargetLane()
{
	return _targetLane;
}

int JPTwoLanesToOneException::getCollidingLane()
{
	return _collidingLane;
}

JPMultipleIntersectionsException::JPMultipleIntersectionsException(){}

const char* JPMultipleIntersectionsException::what() const throw ()
{
	return "You can only instantiate one instance of JPIntersection";
}


JPLaneCollidesWithOncomingLane::JPLaneCollidesWithOncomingLane(int direction,
		int thisLane, int collidingLane)
{
	_collidingLane = collidingLane;
}

const char* JPLaneCollidesWithOncomingLane::what() const throw ()
{
	return "";
}

int JPLaneCollidesWithOncomingLane::getCollidingLane()
{
	return _collidingLane;
}

JPTurningLaneCrossingStraightLane::JPTurningLaneCrossingStraightLane(
		int direction, int thisLane)
{
}

const char* JPTurningLaneCrossingStraightLane::what() const throw ()
{
	return "";
}

JPLaneOffsetMismatch::JPLaneOffsetMismatch()
{

}

const char* JPLaneOffsetMismatch::what() const throw ()
{
	return "";
}

JPLaneNumberOutOfBounds::JPLaneNumberOutOfBounds(int lane)
{
}

const char* JPLaneNumberOutOfBounds::what() const throw ()
{
	return "";
}

JPDirectionOutOfBounds::JPDirectionOutOfBounds(int direction)
{
}

const char* JPDirectionOutOfBounds::what() const throw ()
{
	return "";
}

JPIntersectionException::JPIntersectionException() {
}

JPIntersectionException::~JPIntersectionException() throw () {
}

const char* JPIntersectionException::what() const throw ()
{
	return "";
}

JPConfigurationOrderException::JPConfigurationOrderException() {
}

JPConfigurationOrderException::~JPConfigurationOrderException() throw ()
{
	_detail = 0;
}

const char* JPConfigurationOrderException::what() const throw ()
{
	return "";
}

JPConfigurationOrderException::JPConfigurationOrderException(int which)
{
	_detail = which;
}

int JPConfigurationOrderException::getDetail()
{
	return _detail;
}
