/*
 * IntersectionGrid.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#include "JPIntersectionGrid.h"
#define _USE_MATH_DEFINES //I want pi!
#include <math.h>
#include "JPSimulationEngine.h" //for getNextCar Method
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

/**
 * \return true if there is a clear travel path, false otherwise.
 */
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

double computeTravelTime(const double dist, const double V0,  double &Vf)
{
	double a, remDist, time;
	const double Vt = Vf; //set target speed to what was passed as final

	if( Vt == V0 ) //no acceleration
		time = V0 / dist;
	else if( V0 > Vt) //slowing down
		time = 2 * dist/(Vt + V0);
	else //speed < 25
	{
		a = 5; //acceleration = 5FPS
		//solve dist = 0.5*a*t^2 + V0*t for t (quadratic formula)
		time = (-V0 + sqrt(V0 * V0 + 2 * a * dist) )/a;
		Vf = a * time + V0;
		if(Vf > Vt ) //unlikely but possible
		{
			//speed up to 25
			time = (Vt - V0)/a; //time to accelerate to Vf
			remDist = dist - 0.5 * a * time * time - V0 * time;

			//then go the remaining distance at 25
			time += remDist / Vt;
			Vf = Vt;
		}
	}
	return time;
}

/**
 * This uses the simplifying and conservative approximation that it is a circle with the larger of the
 * two radii.
 *
 * \param lane Origination lane of the car.
 * \param tLane Target lane of the car.
 */
double JPIntersectionGrid::getMaxArcDistance(const int direction, const int lane,
		const int tLane, const int turnDir) const
{
	double r, rOrigin, rTarget;
	if( SFCar::DESIRE_LEFT == turnDir)
	{
		rOrigin = 2 * _offsets[    direction     ] - (lane + 0.5) * LANE_WIDTH;
		rTarget = 2 * _offsets[ (direction+1) % 2] - (lane + 0.5) * LANE_WIDTH;
	}
	else //right
	{
		rOrigin = 2 * _offsets[    direction     ] - (lane + 0.5) * LANE_WIDTH;
		rTarget = 2 * _offsets[ (direction+1) % 2] - (lane + 0.5) * LANE_WIDTH;
	}
	r = std::max(rOrigin, rTarget);
	return r * M_PI; //2pi r /4
}

/**
 * This checks the path of the vehicle during a turn to see if oncomming traffic
 * will interfere.
 *
 * \param direction Origination direction
 * \param lane Origination lane number
 * \param tgLane Origination lane
 * \param car The car.
 * \param speed Speed of the car.
 * \param distance Distance to the intersection boundary
 */
bool JPIntersectionGrid::checkYield(const int direction, const int lane,
		SFCar *car, const double speed,
		const double distance) const
{
	const JPLane *tgLane = _inter->getLane(direction, lane);
	double intTime, curveTime, Vf, remDist, time;
	double V0 = speed;
	const double Vt = 25; //target 25 FPS
	int turn = car->getTurnDirection();
	int tLane;
	if(SFCar::DESIRE_LEFT == turn)
		tLane = tgLane->getLeftTarget();
	else
		tLane = tgLane->getRightTarget();

	// 1) Calculate time for this car to clear the intersection.
	//1.1) Time to the intersection (slowing to 25 FPS (Vf))
	Vf = Vt;
	intTime = computeTravelTime(distance, V0, Vf);

	//1.2) Calculate curve time
	remDist = getMaxArcDistance(direction, lane, tLane, turn);

	V0 = Vf; //Final speed from approach to intersection is new initial speed
	Vf = Vt; //Reset final speed to target speed
	curveTime = computeTravelTime(remDist, V0, Vf);

	time = intTime + curveTime;

	if(SFCar::DESIRE_LEFT == turn)
		return checkLeftYield(direction, lane, tLane, time);
	else
		return checkRightYield(direction, lane, tLane, time);
}

bool JPIntersectionGrid::checkLeftYield(const int direction, const int lane,
		const int tLane, const double clearTime) const
{
	JPSimulationEngine *eng = JPSimulationEngine::getInstance();
	//for right turns, we only car about traffic coming from the left upto
	//and including the target lane.
	int l;
	JPLane *oncLane;
	int fromLeft    = (direction + 1) %4;
	int fromAcross = (direction + 2) %4;
	SFCar *car;
	double leng, pos, speed, dspeed, tail, lbound, ubound, lnBottom, lnTop;

	//traffic from the right and left should be stopped so we only
	//care about what is already in the intersection
	lbound = - _offsets[fromLeft];
	ubound =  _offsets[fromLeft];
	lnBottom = lbound; //actually the bottom of the box encapsulating the arc
	lnTop = 2 * _offsets[fromLeft] - LANE_WIDTH * lane;

	//from the LEFT
	for(l = 0; l < _numLanes[fromLeft]; l++) //all lanes cross our path
	{
		oncLane = _inter->getLane(fromLeft, l);
		while(1)
		{
			car = eng->getNextCar(oncLane, fromLeft, leng, pos, speed, dspeed);
			if( NULL == car) break; //end of cars
			if(pos < lbound) break; //true on the first car beneath the intersection

			//make sure it is not in the intersection
			tail = pos - car->getLength();
			if( tail < lnTop) return false;
		}
	}

	//from the RIGHT
	for(l = tLane; l < tLane; l++) //only target at beyond cross our path
	{
		oncLane = _inter->getLane(fromLeft, l);
		while(1)
		{
			car = eng->getNextCar(oncLane, fromLeft, leng, pos, speed, dspeed);
			if( NULL == car) break; //end of cars
			if(pos < lbound) break; //true on the first car beneath the intersection

			//make sure it is not in the intersection
			tail = pos - car->getLength();
			if( tail < ubound) return false;
		}
	}

	//from across (anything already in the intersection or an oncomming car)
	lbound = - _offsets[fromAcross];
	ubound =  _offsets[fromAcross];
	lnBottom = - ubound + LANE_WIDTH * tLane;


	for(l = 0; l < tLane; l++)
	{
		oncLane = _inter->getLane(fromLeft, l);
		while(1)
		{
			car = eng->getNextCar(oncLane, fromLeft, leng, pos, speed, dspeed);
			if( NULL == car) break; //end of cars

			if(pos < lbound) //true on the first car beneath the intersection
			{
				pos = pos + speed * clearTime;
				if( pos > lnBottom) //make sure it won't reach
					return false;
				break;
			}

			//make sure it is not in the intersection
			tail = pos - car->getLength();
			if( tail < ubound)
				return false;
		}
	}

	return true;
}


bool JPIntersectionGrid::checkRightYield(const int direction, const int lane,
		const int tLane, const double clearTime) const
{
	JPSimulationEngine *eng = JPSimulationEngine::getInstance();
	//for right turns, we only car about traffic coming from the left upto
	//and including the target lane.
	int l;
	JPLane *oncLane;
	int fromLeft = (direction + 1) %4;
	SFCar *car;
	double leng, pos, speed, dspeed, tail, lbound, ubound, lnBottom;

	//2 criteria
	//There must be no cars in the intersection
	//The first car before the intersection must not reach the origination lane before this car clears
	lbound = - _offsets[fromLeft];
	ubound =  _offsets[fromLeft];
	lnBottom = _offsets[direction] - LANE_WIDTH * ( lane + 1);

	for(l = 0; l < tLane; l++)
	{
		oncLane = _inter->getLane(fromLeft, l);
		while(1)
		{
			car = eng->getNextCar(oncLane, fromLeft, leng, pos, speed, dspeed);
			if( NULL == car) break;

			//if it's the first car before the intersection
			//make sure it won't reach
			if(pos < lbound)
			{
				pos = pos + speed * clearTime;
				if( pos > lnBottom) //this car will enter the lane before the turning car clears the turn
					return false;
				break;
			}

			//make sure it is not in the intersection
			tail = pos - car->getLength();
			if( tail < ubound)
				return false;
		}
	}
	return false;
}

/**
 * For all cars that have entered the intersection check, to see that
 * they have completely passed the specified coordinate.
 */
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

			//ensure that the tail end of the car is beyond x
			tail = carX + car->getLength();
			if(tail > x)
				return true;
		}
	}
	//if no obstructions
	return false;
}
/** \copydoc JPIntersectionGrid::obstructedAboveX */
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

			//ensure that the tail end of the car is beyond x
			tail = carX - car->getLength();
			if(tail < x)
				return true;
		}
	}
	//if no obstructions
	return false;
}

/** \copydoc JPIntersectionGrid::obstructedAboveX */
bool JPIntersectionGrid::obstructedAboveY(const double y) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carY, tail;

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
			carY = car->getY();
			if( carY > _bounds[NORTH])
				break; //done with lane

			//ensure that the tail end of the car is beyond y
			tail = carY + car->getLength();
			if(tail > y)
				return true;
		}
	}
	//if no obstructions
	return false;
}

/** \copydoc JPIntersectionGrid::obstructedAboveX */
bool JPIntersectionGrid::obstructedBelowY(const double y) const
{
	int ln, total;
	JPLane *lane;
	SFCar *car;
	double carY, tail;

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
			carY = car->getY();
			if( carY < _bounds[SOUTH])
				break; //done with lane

			tail = carY - car->getLength();
			if(tail < y)
				return true;
		}
	}
	//if no obstructions
	return false;
}
