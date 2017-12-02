/*
 * IntersectionGrid.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#include "../../inc/JPIntersectionGrid.h"

JPIntersectionGrid::JPIntersectionGrid(JPIntersection *inter)
{

	int iln, dir;
	_inter = inter;
	for(iln = 0; iln < MAX_LANES_MACRO; iln++)
	{
		for(dir = 0; dir < 4; dir++)
			_firstCars[dir][iln] = NULL;
	}

	for(dir = 0; dir < 4; dir++)
	{
		_offsets[dir] = inter->getLaneOffset(dir);
		_numLanes[dir] = inter->getLaneCount(dir);
	}
	_bounds[NORTH] = _offsets[EAST];
	_bounds[SOUTH] = - _offsets[EAST];
	_bounds[EAST] = _offsets[NORTH];
	_bounds[WEST] = - _offsets[NORTH];

}

JPIntersectionGrid::~JPIntersectionGrid() {}

bool JPIntersectionGrid::checkPath(const int direction, const int lnNum) const
{
	double lnBottom, lnTop;

	if(SOUTH == direction || NORTH == direction)
	{
		//compute top and bottom of lane
		if(NORTH == direction)
		{
			lnBottom = - (_offsets[NORTH] - lnNum) * LANE_WIDTH;
			lnTop = lnBottom + LANE_WIDTH;
		}
		else //SOUTH
		{
			lnTop = (_offsets[NORTH] - lnNum) * LANE_WIDTH;
			lnBottom = lnTop - LANE_WIDTH;
		}

		//check for obstructions
		if(obstructedBelowX(lnTop))
			return false;
		if(obstructedAboveX(lnBottom))
			return false;
	}
	else //east/west
	{
		//compute top and bottom of lane
		if(EAST == direction )
		{
			lnTop = (_offsets[EAST] - lnNum) * LANE_WIDTH;
			lnBottom = lnTop - LANE_WIDTH;
		}
		else //WEST
		{
			lnBottom = - (_offsets[EAST] - lnNum) * LANE_WIDTH;
			lnTop = lnBottom + LANE_WIDTH;
		}

		//check for obstructions
		if(obstructedBelowY(lnTop))
			return false;
		if(obstructedAboveY(lnBottom))
			return false;
	}
	return true;
}
void JPIntersectionGrid::setFirstCar(const int direction, const int lane,
		SFCar* car)
{
	_firstCars[direction][lane] = car;
}


bool JPIntersectionGrid::checkYield(const int direction, const int lane, SFCar *car, const double speed,
		const double distance) const
{
	double intTime, curveTime, a, Vf;
	double V0 = speed;

	// 1) Calculate time for this car to clear the intersection.
	//1.1) Time to the intersection (slowing to 25 FPS)
	//1.2) Calculate curve time
	//todo

	return true;
}

bool JPIntersectionGrid::obstructedAboveX(const double x) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carX, tail;

	//increment over all the lanes in the direction
	total = _inter->getLaneCount(EAST);
	for(ln = 0; ln < total; ln++)
	{
		//increment over all the cars in the lane
		lane = _inter->getLane(EAST, ln);
		lane->resetToFirstCar();
		while(0 != (car = lane->getNextCar()) )
		{
			//check to see if we are past the bounds of the intersection
			carX = car->getX();
			if( carX > _bounds[EAST])
				break; //done with lane

			tail = carX + car->getLength();
			if(tail > x)
				return true;
		}
	}
	//if no obstructions
	return false;
}

bool JPIntersectionGrid::obstructedBelowX(const double x) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carX, tail;

	//increment over all the lanes in the direction
	total = _inter->getLaneCount(WEST);
	for(ln = 0; ln < total; ln++)
	{
		//increment over all the cars in the lane
		lane = _inter->getLane(WEST, ln);
		lane->resetToFirstCar();
		while(0 != (car = lane->getNextCar()) )
		{
			//check to see if we are past the bounds of the intersection
			carX = car->getX();
			if( carX < _bounds[WEST])
				break; //done with lane

			tail = carX - car->getLength();
			if(tail < x)
				return true;
		}
	}
	//if no obstructions
	return false;
}

bool JPIntersectionGrid::obstructedAboveY(const double y) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carX, tail;

	//increment over all the lanes in the direction
	total = _inter->getLaneCount(NORTH);
	for(ln = 0; ln < total; ln++)
	{
		//increment over all the cars in the lane
		lane = _inter->getLane(NORTH, ln);
		lane->resetToFirstCar();
		while(0 != (car = lane->getNextCar()) )
		{
			//check to see if we are past the bounds of the intersection
			carX = car->getX();
			if( carX > _bounds[NORTH])
				break; //done with lane

			tail = carX + car->getLength();
			if(tail > y)
				return true;
		}
	}
	//if no obstructions
	return false;
}

bool JPIntersectionGrid::obstructedBelowY(const double y) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carX, tail;

	//increment over all the lanes in the direction
	total = _inter->getLaneCount(SOUTH);
	for(ln = 0; ln < total; ln++)
	{
		//increment over all the cars in the lane
		lane = _inter->getLane(SOUTH, ln);
		lane->resetToFirstCar();
		while(0 != (car = lane->getNextCar()) )
		{
			//check to see if we are past the bounds of the intersection
			carX = car->getX();
			if( carX < _bounds[SOUTH])
				break; //done with lane

			tail = carX - car->getLength();
			if(tail < y)
				return true;
		}
	}
	//if no obstructions
	return false;
}
