/*
 * SimulationEngine.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../../inc/JPSimulationEngine.h"
JPSimulationEngine *JPSimulationEngine::_unique = 0;

JPSimulationEngine::JPSimulationEngine()
{
	// TODO Auto-generated constructor stub
	_initTime = -1; //flag for needing to be set
	_time = 0.0;
	_stepTime = 0.1; //default step time is 0.1 seconds
	_initialized = false;
	_updating = false;

	int i;
	for(i = 0; i<4;  i++)
		_laneCounts[i] = 0;

	//set null pointers to the needed parameters
	_intersection = NULL;
	_iGrid = 0;
	_trafficModel = NULL;
	_light = NULL;
}

JPSimulationEngine::~JPSimulationEngine(){ end(); }

/**
 * \brief Advance the state of the simulation by the preset step time.
 *
 * This function causes the simulation engine to perform the calculations
 * and modification necessary to advance the simulation. For example if step()
 * is called, and the preset step time all is 0.1 seconds cars in the simulation
 * will be moved to their positions 0.1
 * seconds from now. It also advances the simulation's internal clock by 0.1 seconds.
 *
 */
void JPSimulationEngine::step(){ step(_stepTime); }

/**
 * \brief Advance the state of the simulation by sec seconds.
 *
 * This function causes the simulation engine to perform the calculations
 * and modification necessary to advance the simulation. For example if step(0.1)
 * is called, all cars in the simulation will be moved to their positions 0.1
 * seconds from now. It also advances the simulation's internal clock by 0.1 seconds.
 *
 * \param sec The number of seconds to advance the simulation.
 */
void JPSimulationEngine::step(double sec)
{
	if( ! _initialized)
		init();

	int dir, laneNum;
	for(dir = 0; dir < 4; dir++)
		for(laneNum = 0; laneNum < _laneCounts[dir]; laneNum++)
			processLane(_intersection->getLane(dir,laneNum), dir);
	_time += sec;
}

double JPSimulationEngine::intersectionDeceleration(double pos, double speed,
		double pcPos, double pcSpeed, SFCar* car)
{
	return 0.0;
}

void JPSimulationEngine::end()
{
	//todo delete cars from the simulation and pushRemUppdate
}

void JPSimulationEngine::setTrafficLight(JPLightTestStub* light){ _light = light; }//todo swap on merge
//void JPSimulationEngine::setTrafficLight(DJTrafficLightManager* light){ _light = light; }
void JPSimulationEngine::setTrafficModel(JPTrafficModel* model){ _trafficModel = model; }
void JPSimulationEngine::setIntersection(JPIntersection* intersection){ _intersection = intersection; }
void JPSimulationEngine::setStepInterval(double secs){ _stepTime = secs; }
void JPSimulationEngine::setInitTime(double secs) { _initTime = secs; }

void JPSimulationEngine::processLane(JPLane* lane, int direction)
{
	//todo write process lane
	double prevSpeed = -1;
	double prevLeng, prevPos, prevAccel;
	double leng, pos, speed, accel, dspeed;
	SFCar *car;
	while (NULL != getNextCar(lane, direction, leng, pos, speed, dspeed))
	{

	}
}

 JPSimulationEngine* JPSimulationEngine::getInstance()
{
	if(! _unique)
		_unique = new JPSimulationEngine();

	return _unique;
}

//private function used for testing
void JPSimulationEngine::destory()
{
	if(_unique)
	{
		delete _unique;
		_unique = 0;
	}
}

/** The step time is how far the simulation advances in each step. For example with a step time of 0.1 calling the step function would move all of the cars to where they would be 0.1 seconds from now and advance the simulation's internal clock by 0.1 seconds. */
void JPSimulationEngine::setStepTime(double stepTime) { _stepTime = stepTime; }
/** \copydetails JPSimulationEngine::setStepTime() */
double JPSimulationEngine::getStepTime() const { return _stepTime; }

/**
 * \throw JPMissingParameterException if either the intersection, traffic light, traffic model are not set.
 */
void JPSimulationEngine::checkPrereqs()
{
	if(NULL == _intersection )
		throw JPMissingParameterException(JPMissingParameterException::details::INTERSECTION);
	if(NULL == _light )
		throw JPMissingParameterException(JPMissingParameterException::details::TRAFFIC_LIGHT);
	if(NULL == _trafficModel )
		throw JPMissingParameterException(JPMissingParameterException::details::TRAFFIC_MODEL);
	_intersection->finalize();

	//todo setup _iGrid
}
void JPSimulationEngine::init()
{
	checkPrereqs();
	_initialized = true; //prevent infinite recursion

	//initialize car creation and yellow times
	int dir, ln;
	for(dir = 0; dir < 4; dir++)
	{
		_nextCreationTime[dir] =  _trafficModel->getNextTiming(dir);
		for(ln = 0; ln < _laneCounts[dir]; ln++)
			_yellowTime[dir][ln] = -1;
	}

	if( -1 == _initTime  )
	{
		//todo default to two cycles of the light
	}
	else
	{
		//todo raise initTime to the next highest cycle time
	}

	//step through all but the last 5 seconds of init time over maximum 50 steps
	_time = 0;
	if( _initTime > 10)
	{
		double stepTime = (_initTime - 5)/50;
		while( _time < _initTime - 5 )
			step(stepTime);
	}

	//step through the last 5 seconds of init time in 0.1 sec/step
	while( _time < _initTime )
		step(0.1);

	//reset the clock for tabulation
	_time = 0;
}

/**
 * Add cars to the simulation and schedule the next arrival
 */
void JPSimulationEngine::addCars(int direction, int ln, JPLane lane, double timeStep)
{
	double effTime = _time + timeStep;

	//handle rates of zero by skipping
	if(_nextCreationTime[direction] < 0)
		return;

	while(effTime < _nextCreationTime[direction])
	{
		lane.addCarAtEnd( makeCar(direction, ln));
		_nextCreationTime[direction] += _trafficModel->getNextTiming(direction);
	}
}

/**
 * \brief Generate and initialize car.
 *
 * Sets the location, turn desire, and orientation of the car
 */
SFCar *JPSimulationEngine::makeCar(int direction, int lane)
{
	double theta = 0, x = 0, y = 0;
	switch(direction)
	{
		case JPIntersection::NORTHBOUND:
			x = (_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			y = - _intersection->getTrackedLaneLength(direction);
			theta = 0;
			break;

		case JPIntersection::EASTBOUND:
			x =  _intersection->getTrackedLaneLength(direction);
			y = (_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			theta = 90;
			break;

		case JPIntersection::SOUTHBOUND:
			x =-(_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			y =  _intersection->getTrackedLaneLength(direction);
			theta = 180;
			break;

		case JPIntersection::WESTBOUND:
			x = - _intersection->getTrackedLaneLength(direction);
			y =-(_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			theta = 270;
			break;
	}

	SFCar *car = new SFCar();
	car->setTheta(theta);
	car->setTimeInSim(0);
	car->setSpeed(_intersection->getSpeedLimitsInFPS(direction));
	car->setTurnDirection(_trafficModel->getNextTurnDirection(direction));
	car->setWaitTime(0);
	car->setX(x);
	car->setY(y);

	pushAdd(car, 0);

	return car;
}

SFCar* JPSimulationEngine::getNextCar(JPLane* lane, int dir, double& leng, double& pos,
	double& speed, double& dspeed)
{
	SFCar *car = lane->getNextCar();;
	leng = car->getLength();
	speed = car->getSpeed();
	dspeed = car->getDesiredSpeed();//assuming speed limit +/-
	dspeed = 0; //remove on merge
	dspeed += _intersection->getSpeedLimitsInFPS(dir);

	double x = car->getX();
	double y = car->getY();

	switch(dir)
	{
		case JPIntersection::SOUTHBOUND: pos = -y; break;
		case JPIntersection::NORTHBOUND: pos = y;  break;
		case JPIntersection::EASTBOUND: pos = x;   break;
		case JPIntersection::WESTBOUND: pos = -x;  break;
	}

	return car;
}
