/*
 * SimulationEngine.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../../inc/JPSimulationEngine.h"
#include <stdlib.h> /* rand */
#include <time.h> /* time for seeding rand */

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

	srand(time(NULL)); //seed RNG for lane selection
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
	{
		for(laneNum = 0; laneNum < _laneCounts[dir]; laneNum++)
			processLane(_intersection->getLane(dir,laneNum), dir, sec);
		addCars(dir, sec);
	}
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

/**
 * \breif Determine the ammount of deceleration required or acceleration possible without coming within
 * 5 feet of the next car.
 */
double JPSimulationEngine::getPrevCarDecel(const double pSpeed, const double pPos, const double speed,
		const double dSpeed, const double pos, const double timeStep) const
{
		double capableAccel = this->acceleration;
		double accel = 0;
		double lookAhead = 5;

		//if there is no next car only look at the possibility
		if(-1 == pSpeed )
		{
			if(speed < dSpeed)
			{
				accel = capableAccel;

				//but don't exceed desired speed
				if(speed + accel * timeStep > dSpeed)
					accel = (dSpeed - speed)/timeStep;
			}
			else
				accel = 0;
			return accel;
		}

		//will we hit the car ahead if we don't slow down?
		double pnext, next, reqdDecl;
		pnext = pPos + pSpeed * lookAhead; //where the car will
		next = pos + speed * lookAhead; //where we will be
//printf("pnext: %f, next %f\n", pnext, next);

		//this gives either the required deceleration (-) to not come within 5 feet
		//of the car in front or the allowable acceleration (+) to do the same
		reqdDecl =  2 * (pnext - 5 - next)/pow(5, 2); //maintain 5ft + gap
		if( reqdDecl < 0) //we need to slow down
		{
			//slow down at the car's normal acceleration rate or however fast we need to
			accel = std::min(reqdDecl, -capableAccel);

			//but don't slow down to less than the prevCar speed
			if(speed + accel * timeStep < pSpeed)
				accel = (pSpeed - speed)/timeStep;
		}
		else if( speed < dSpeed && reqdDecl > 0)
		{
			//speed up as fast as we can
			accel = std::min(reqdDecl, capableAccel);

			//but don't exceed desired speed
			if(speed + accel * timeStep > dSpeed)
				accel = (dSpeed - speed)/timeStep;
		}
		return accel;
}
void JPSimulationEngine::updateCar(SFCar *car, int dir, double &speed,double &pos,const double accel, const double timeStep)
{
	//calculate new position and speed
	pos += 0.5 * accel * pow(timeStep, 2) + speed * timeStep;
	speed = speed + accel * timeStep;
	if(speed < 0) //ugh floating points and those -1e-50
		speed = 0;

	//translate position to x/y
	switch(dir)
	{
		case JPIntersection::SOUTHBOUND: car->setY(-pos); break;
		case JPIntersection::NORTHBOUND: car->setY(pos);  break;
		case JPIntersection::EASTBOUND: car->setX(pos);   break;
		case JPIntersection::WESTBOUND: car->setX(-pos);  break;
	}

	car->setTimeInSim(car->getTimeInSim()+timeStep);
	if( speed < 1 )
		car->setWaitTime(car->getWaitTime()+timeStep);
}
void JPSimulationEngine::processLane(JPLane* lane, int direction, double timeStep)
{
	//todo write process lane
	double prevSpeed = -1;
	double prevPos = 0;
	double leng, pos, speed, carAccel, lightAccel, accel, dspeed;
	SFCar *car;

	//cycle through the entire lane
	lane->resetToFirstCar();
	while (1)
	{
		car = getNextCar(lane, direction, leng, pos, speed, dspeed);
		if( NULL == car)
			break;

		carAccel = getPrevCarDecel(prevSpeed, prevPos,speed, dspeed, pos, timeStep);
		lightAccel = 1000000; //placeholder
		accel = std::min(carAccel, lightAccel);

		//turning? = want to turn + inside intersection bounds

		//compute new position
		this->updateCar(car, direction, speed, pos, accel, timeStep);
		prevPos = pos - leng; //make it the back of the previous car
		prevSpeed = speed;
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
	//get local copies of lane counts and turnOpts to minimize information requests
	//get intersection bounds
	int dir, ln;
	for(dir = 0; dir < 4; dir++)
	{
		_nextCreationTime[dir] =  _trafficModel->getNextTiming(dir);
		_laneCounts[dir] = _intersection->getLaneCount(dir);
		_intersectionBounds[dir] = _intersection->getLaneOffsetInFeet( (dir+1)  % 4);
		for(ln = 0; ln < _laneCounts[dir]; ln++)
		{
			_yellowTime[dir][ln] = -1;
			_turnOpts[dir][ln] = (_intersection->getLane(dir, ln))->getTurnOptions();
		}
	}

	//adjust init
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
void JPSimulationEngine::addCars(int direction, double timeStep)
{
	double effTime = _time + timeStep;

	//handle rates of zero by skipping
	if(_nextCreationTime[direction] < 0)
		return;

	int ln;
//printf("efft: %f\t nct:%f\n", effTime, _nextCreationTime[direction]);
	SFCar *car;
	while(effTime > _nextCreationTime[direction])
	{

		car = makeCar(direction, ln);
		_intersection->getLane(direction, ln)->addCarAtEnd(car);
		_nextCreationTime[direction] += _trafficModel->getNextTiming(direction);
	}
}

/**
 * \brief Generate and initialize car.
 *
 * Sets the location, turn desire, and orientation of the car
 */
SFCar *JPSimulationEngine::makeCar(int direction, int &lane)
{
	double theta = 0, x = 0, y = 0;
	SFCar *car = new SFCar();

	//determine direction and lane
	int turn = _trafficModel->getNextTurnDirection(direction);
	car->setTurnDirection(turn);
	lane = determineLane(car, direction);

	//determine x, y, and theta at starting point
	switch(direction)
	{
		case JPIntersection::NORTHBOUND:
			x = (_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			y = - _intersection->getTrackedLaneLength(direction);
			theta = 0;
			break;

		case JPIntersection::EASTBOUND:
			x =   - _intersection->getTrackedLaneLength(direction);
			y = - (_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			theta = 90;
			break;

		case JPIntersection::SOUTHBOUND:
			x =-(_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			y =  _intersection->getTrackedLaneLength(direction);
			theta = 180;
			break;

		case JPIntersection::WESTBOUND:
			x =  _intersection->getTrackedLaneLength(direction);
			y = (_intersection->getLaneOffset(direction) - lane - 0.5 ) * JPIntersection::LANE_WIDTH;
			theta = 270;
			break;
	}
	car->setX(x);
	car->setY(y);
	car->setTheta(theta);

	//initialize other parameters
	car->setTimeInSim(0);
	car->setSpeed(_intersection->getSpeedLimitsInFPS(direction));
	car->setWaitTime(0);

	pushAdd(car, 0);

	return car;
}

/**
 * \brief Determine which lane to put the car in.
 */
int JPSimulationEngine::determineLane(SFCar* car, int direction)
{
	//Valid lanes will be consecutive
	int numValid = 0;
	int startValid = -1;
	int desire;

	//get direction to match against
	switch(car->getTurnDirection())
	{
		case SFCar::DESIRE_LEFT: desire = JPLane::LEFT; break;
		case SFCar::DESIRE_RIGHT: desire = JPLane::RIGHT; break;
		default:  desire = JPLane::STRAIGHT; break;
	}

	//get a count and starting point of valid lanes
	int ln;
	for(ln = 0; ln < _laneCounts[direction]; ln++)
	{
		if( (_turnOpts[direction][ln] & desire) == desire)
		{
			numValid++;
			if(-1 == startValid)
				startValid = ln;
		}
	}

	//could have done a balanced distribution instead :/
	//pick one
	if(0 == numValid) //if TM allows a turn that is not available modulo will crash on 0 (just like dividing)
		return 0;
	if(1 == numValid)
		return startValid;
	else
		return (rand() % numValid) + startValid;
}

/**
 * \brief Retrieve the next car from the lane, and set a few variables.
 */
SFCar* JPSimulationEngine::getNextCar(JPLane* lane, int dir, double& leng, double& pos,
	double& speed, double& dspeed)
{
	SFCar *car = lane->getNextCar();;

	//If last car exit.
	if(NULL == car)
		return NULL;
	leng = car->getLength();
	speed = car->getSpeed();
	dspeed = car->getDesiredSpeed() * 5280 /3600;//assuming speed limit +/-
	//dspeed = 0; //remove on merge
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

