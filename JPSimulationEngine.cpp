/*
 * SimulationEngine.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "JPSimulationEngine.h"
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
	_light = new JPTrafficLightAdapter();

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
			processLane(laneNum, dir, sec);
		addCars(dir, sec);
	}
	_time += sec;
	updateYellowTimes(sec);
}

void JPSimulationEngine::end()
{
	//todo delete cars from the simulation and pushRemUppdate
}

void JPSimulationEngine::setTrafficLight(JPLightTestStub* light)
{
	_light->setTestStub(light);
}
//todo swap on merge
//void JPSimulationEngine::setTrafficLight(DJTrafficLightManager* light){ _light = light; }
void JPSimulationEngine::setTrafficModel(JPTrafficModel* model){ _trafficModel = model; }
void JPSimulationEngine::setIntersection(JPIntersection* intersection){ _intersection = intersection; }
void JPSimulationEngine::setStepInterval(double secs){ _stepTime = secs; }

/**
 * If a value less than 0 is specified, it resets the initialization time to the default of two cycles of the light
 */
void JPSimulationEngine::setInitTime(double secs)
{
	if(_initTime >= 0)
		_initTime = secs;
	else
		_initTime = -1;
}


/**
 * A forward car is traveling at Vt. The rear car is traveling at V0. There is a gap between the
 * two of dX + desired final gap. This function computes the time and acceleration required to
 * match speed while closing the desired ammount of the gap.
 * While named deceleration, this function actually returns the acceleration. (i.e.) The value is negative
 * for its intended usage.
 *
 * \param V0 The velocity of the rear car.
 * \param Vt The velocity of the forward car.
 * \param dX The distance over which the deceleration should occur
 * \param time A destination for outputting the computed time.
 *
 * \return The acceleration that would be required for the rear car to match the pace of the forward car while closing the gap dX.
 */
double JPSimulationEngine::movingTargetDecel(const double V0, const double Vt, const double dX, double &time) const
{
	double a;
	//eq1: Vt = a*t + V0
	//eq2: t*Vt + dX = 0.5 * a * t^2  + V0*t
	//solve by substitution
	time = 2 * dX/(V0-Vt);
	a = (Vt - V0)/time;
	return a;
}

/** \brief Determine the amount of deceleration required or acceleration possible without coming within 5 feet of the next car.*/
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
		double pnext, next, reqdDecl, time, dX;
		pnext = pPos + pSpeed * lookAhead; //where the car will
		next = pos + speed * lookAhead; //where we will be
		//maintain 5 feet between cars
		//so target "decrease in gap" is 5 less than the current gap
		dX = pPos - pos - 5.5;

		//this gives either the required deceleration (-) to not come within 5 feet
		//of the car in front or the allowable acceleration (+) to do the same
		reqdDecl =  movingTargetDecel(speed, pSpeed, dX, time);
		if( (pnext - 5.6) < next ) //we may need to slow down
		{
			if(reqdDecl < 0) //we do need to slow down
			{
				//slow down  however fast we need to
				accel = reqdDecl;

				//but don't slow down to less than the prevCar speed
				if(speed + accel * timeStep < pSpeed)
				{
					accel = (pSpeed - speed)/timeStep;
				}
			}
		}
		else if( speed < dSpeed)
		{
			//speed up as fast as we can
			accel = capableAccel;

			//but don't exceed desired speed
			if(speed + accel * timeStep > dSpeed)
				accel = (dSpeed - speed)/timeStep;
		}

		return accel;
}
double getTurnedDistance( const double ac, const double V0, const double tm)
{
	double time, dist;
	if(25 > V0 + ac * tm)
	{
		time = -V0/ac;
		dist = 0.5 * ac * time * time + V0 * time; //accelerating
		dist += (tm - time) * 25; //steady speed
		return dist;
	}
	else
		return 0.5 * ac * tm * tm + V0 * tm;
}

void JPSimulationEngine::updateTurnCar(Car *car,const int dir, double speed,
		double &pos,const double accel, const int turn, const double timeStep,
		const int lane)
{

	//1 get axes and circumference
	double r, rOrigin, rTarget, circ, radius, deg, theta, otheta, x, y;
	if( Car::DESIRE_LEFT == turn)
	{
		rOrigin = 2 * _offsets[    dir     ] - (lane + 0.5) * LANE_WIDTH;
		rTarget = 2 * _offsets[ (dir+1) % 2] - (lane + 0.5) * LANE_WIDTH;
	}
	else //right
	{
		rOrigin = 2 * _offsets[    dir     ] - (lane + 0.5) * LANE_WIDTH;
		rTarget = 2 * _offsets[ (dir+1) % 2] - (lane + 0.5) * LANE_WIDTH;
	}
	radius = (rOrigin + rTarget)/2;
	circ = M_PI * radius / 2;

	otheta = car->getTheta();
	theta =  remainder(otheta, 90); //How far we are into the turn
	double linTravel = getTurnedDistance(accel, speed, timeStep);
	deg = 90 * linTravel/circ;

	//did we exit?
	double deltaPos, deltaOrth, newDeg;
	if(theta + deg > 90) //we've completed the turn
	{
		deltaPos = (theta + deg - 90 ) * circ/90;
		exitTurn(car, dir, deltaPos, turn, lane);
		return;
	}

	x = sin( theta + deg);
	deltaPos = x - sin(theta); //pos should be incremented by this
	y = rTarget * sqrt( 1 - pow(x/rOrigin, 2));


	//todo compute deltaPos and deltaOrth.
	car->setTheta( remainder(deg + otheta,360));

}
void JPSimulationEngine::exitTurn(Car *car, int dir, const double excess,const int turn, const int lane)
{
	int target;
	double pos;

	//change directions
	JPLane *originLane = _intersection->getLane(dir, lane);
	if(Car::DESIRE_LEFT == turn)
	{
		target = originLane->getLeftTarget();
		dir = (dir + 1) % 4;
	}
	else
	{
		target = originLane->getRightTarget();
		dir = (dir + 3) % 4;
	}

	pos = excess + _offsets[dir];
	car->setTheta( 90 * ( (dir + 2)%2) );

	originLane->removeCurrentCar();
	//todo set positins

}
void JPSimulationEngine::updateCar(Car *car, int dir, double speed,double &pos,const double accel, const double timeStep)
{
	//calculate new position and speed
	double dX, newSpeed, time;
	dX = 0.5 * accel * pow(timeStep, 2) + speed * timeStep;
	newSpeed = speed + accel * timeStep;
//printf("Accel: %f\tnewSpeed%f\n",accel, newSpeed);
	//depending on how acceleration was calculated it may lead to speed less than 0
	//prevent that and recalculate dX assuming deceleration stops at 0
	if(newSpeed < 0 )
	{
		time = - speed / accel;
		dX = 0.5 * accel * pow(time, 2) + speed * time;;
		newSpeed = 0;
	}

	pos += dX;
	speed = newSpeed;
	if(speed < 0.1) //just stop already
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
	car->setSpeed(speed);
}
void JPSimulationEngine::dispose(Car *car, JPLane *lane)
{
	Car *remcar;
	remcar = lane->removeFirstCar();
	this->pushRemove(car, 0);
	if( remcar != car)
	{
		fprintf(stderr, "Car removal error!\n");
		fprintf(stderr, "Car: %p\t remcar: %p\n", car, remcar);
	}
	else
		delete car;
}

int JPSimulationEngine::determineLightEffect(Car *car, const int dir, const int ln) const
{
	int state = _light->getState(dir,ln,_time);
	int turn = car->getTurnDirection();

	switch(turn)
	{
	case Car::DESIRE_RIGHT:
		if( (state & consts::GREEN) == consts::GREEN) return GO;
		if( (state & consts::YELLOW) == consts::YELLOW) return CAUTION;
		return YIELD; //right turn on red
	case Car::DESIRE_LEFT:
		if( (state & consts::LEFT_GREEN) == consts::LEFT_GREEN) return GO;
		if( (state & consts::LEFT_CAUTION) == consts::LEFT_CAUTION) return CAUTION;
		if( (state & consts::LEFT_YIELD) == consts::LEFT_YIELD) return YIELD;
		return STOP; //stop on red
	default: //straight
		if( (state & consts::GREEN) == consts::GREEN) return GO;
		if( (state & consts::YELLOW) == consts::YELLOW) return CAUTION;
		return STOP; //stop on red
	}
}

/**
 * While named deceleration, this function actually returns the acceleration. (i.e.) The value is negative
 * for its intended usage.
 *
 * \param V0 The initial velocity.
 * \param dX The distance over which the deceleration should occur
 * \param time A destination for outputing the computed time.
 *
 * \return The acceleration that would be required to decelerate from V0 to 0 over the given distance.
 */
double JPSimulationEngine::staticTargetDecel(const double V0, const double dX, double &time) const
{

	//eq1: 0=at+V0
	//eq2: dX=0.5at^2+V0t
	//solve by substitution
	time = 2 * dX/V0;
	return - V0/time;
}

/**
 * While named deceleration, this function actually returns the acceleration. (i.e.) The value is negative
 * for its intended usage.
 *
 * \param V0 The initial velocity.
 * \param Vf The final velocity.
 * \param dX The distance over which the deceleration should occur
 * \param time A destination for outputing the computed time.
 *
 * \return The acceleration that would be required to achieve the change in velocity over the given distance.
 */
double JPSimulationEngine::staticTargetDecel(const double V0, const double Vf, const double dX, double &time) const
{
	//eq1: Vf=at+V0
	//eq2: dX=0.5at^2+V0t
	time = 2 * dX/(Vf + V0);
	return (Vf - V0)/time;
}

/**
 * This function is called when the light permits a car to go. It is used to adjust speed when
 * turning.
 * \param turnDir Turn direction \todo
 * \param speed The current speed of the car.
 * \param timeStep The size of the timeStep
 * \return If in the middle of a turn, the lesser of the max acceleration and the acceleration
 * required to achieve 25 FPS. If not in a turn, an arbitrarily high value.
 */
double JPSimulationEngine::computeGoAccel(const int turnDir, const double speed, const double timeStep) const
{
	if(Car::DESIRE_STRAIGHT == turnDir )
		return 1000.0; //Arbitrarily high value
	if(speed < 25.1 && speed > 24.9)
		return 0.0; //stay the same speed

	//accelerate
	double stepAccel = (25 - speed)/timeStep; //prevent over-speed
	return std::min(this->acceleration, stepAccel);
}

double JPSimulationEngine::getIntersectionDecel(Car *car,const int dir, const int ln,
		const double pos, const double speed, const double timeStep) const
{
	double next, action, accel1, dist;
	double lookAhead = 5.0;
	double intStart = - std::abs(_intersectionBounds[dir]); //position of the light
	int intEnd = -intStart;
	//default slow down rate is the car's normal acceleration rate
	double time;
	int turn = car->getTurnDirection();

	//are we more than 5 seconds away or already beyond?
	next = pos + speed * lookAhead; //where we will be in 5 seconds
	if( next < intStart || pos > intEnd)
		return 1000.0; //Return arbitrarily high value as there is no need to slow down

	//if we already entered the intersection lightState doesn't matter
	//but turns can still limit speed
	if(pos > intStart)
		return computeGoAccel(turn, speed, timeStep);

	action = determineLightEffect(car, dir, ln);
	dist = intStart - pos; // how far we can go
	if(CAUTION == action)
	{
		//caution actions are the same as either GO or STOP
		//depending on how long it's been yellow
		int whichYellow = 0;
		double timeLeft;
		const double expTime = 4; //how many seconds before you break
		if(car->getTurnDirection() == Car::DESIRE_LEFT)
			whichYellow = 1;

		timeLeft = expTime - _yellowTime[dir][ln][whichYellow];
		if( timeLeft > dist/speed )
			action = GO;
		else
			action = STOP;
	}

	if(YIELD == action)
	{
		//If yielding check on coming traffic and react accordingly
		if(_iGrid->checkYield(dir, ln, car, speed, dist))
			return computeGoAccel(turn, speed, timeStep);
		else
			action = STOP;
	}

	if(GO == action)
	{
		bool blocked = _iGrid->checkPath(dir, ln);

		if( blocked)
			action = STOP;
		else //if not blocked, then go
			return computeGoAccel(turn, speed, timeStep);
	}

	if(STOP == action)
	{
		//within a foot of the light and stopped? Then stay stopped.
		if (dist < 1 && speed < 0.1)
				return 0.0;

		//be at 0 speed when 0.5 is reached if not already there.
		if( dist < 0.5 )
		{
			accel1 = staticTargetDecel(speed,dist - 0.001, time); //fail safe
		}
		else
			accel1 = staticTargetDecel(speed,dist - 0.5, time);
		return accel1;
	}

	return 0.0;
}

void JPSimulationEngine::processLane(int ln, int direction, double timeStep)
{
	//todo write process lane
	double prevSpeed = -1;
	double prevPos = 0;
	double leng, pos, speed, carAccel, lightAccel, accel, dspeed;
	JPLane *lane = _intersection->getLane(direction,ln);
	double exitLength = _intersection->getTrackedExitLength(direction);
	Car *car;
	const double endInt = std::abs(_intersectionBounds[direction]);
	const double beginInt = - endInt;
	int turn;

	//cycle through the entire lane
	lane->resetToFirstCar();
	while (1)
	{
		car = getNextCar(lane, direction, leng, pos, speed, dspeed);
		if( NULL == car)
			break;

		carAccel = getPrevCarDecel(prevSpeed, prevPos,speed, dspeed, pos, timeStep);
		lightAccel = getIntersectionDecel(car, direction, ln, pos, speed, timeStep);
		accel = std::min(carAccel, lightAccel);

		double newPos = pos;
		turn = car->getTurnDirection();
		//turning? = want to turn + inside intersection bounds
		if( pos < beginInt || Car::DESIRE_STRAIGHT == turn  || pos > endInt)
			this->updateCar(car, direction, speed, newPos, accel, timeStep);
		else
			updateTurnCar(car, direction, speed, newPos, accel, turn, timeStep, ln);

		prevPos = pos - leng; //make it the back of the previous car
		prevSpeed = speed;

		//if the car is outside tracking distance, remove
		if(newPos > exitLength)
			dispose(car, lane);
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
 * \throw JPMissingParameterException if either the intersection, traffic model are not set.
 */
void JPSimulationEngine::checkPrereqs()
{
	if(NULL == _intersection )
		throw JPMissingParameterException(JPMissingParameterException::details::INTERSECTION);
	if(NULL == _trafficModel )
		throw JPMissingParameterException(JPMissingParameterException::details::TRAFFIC_MODEL);
	_intersection->finalize();

	_iGrid = new JPIntersectionGrid(_intersection);
}

/**
 * Checks prerequisite conditions (see \link checkPrereqs() \endlink ) and runs the simulation
 * for initTime to populate the lanes. It then resets the clock to 0. Default init time is two cycles,
 * but it can be set through \link  setInitTime() \endlink value will be rounded up to the nearest whole cylce
 * \throw JPMissingParameterException if either the intersection, traffic light, traffic model are not set.
 */
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
		_offsets[dir] = _intersectionBounds[dir] = _intersection->getLaneOffsetInFeet( (dir+1)  % 4);
		for(ln = 0; ln < _laneCounts[dir]; ln++)
		{
			_yellowTime[dir][ln][0] = -1;
			_yellowTime[dir][ln][1] = -1;
			_turnOpts[dir][ln] = (_intersection->getLane(dir, ln))->getTurnOptions();
		}

		//negate south and west
		int SOUTH = JPIntersection::SOUTH;
		int WEST = JPIntersection::WEST;
		_intersectionBounds[SOUTH] = - _intersectionBounds[SOUTH];
		_intersectionBounds[WEST] = - _intersectionBounds[WEST];
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


void JPSimulationEngine::addCars(int direction, double timeStep)
{
	double effTime = _time + timeStep;

	//handle rates of zero by skipping
	if(_nextCreationTime[direction] < 0)
		return;

	int ln;
//printf("efft: %f\t nct:%f\n", effTime, _nextCreationTime[direction]);
	Car *car;
	while(effTime > _nextCreationTime[direction])
	{

		car = makeCar(direction, ln);
		_intersection->getLane(direction, ln)->addCarAtEnd(car);
		_nextCreationTime[direction] += _trafficModel->getNextTiming(direction);
	}
}

/**
 * This function creates a new car. Initializes is position, speed, rotation, and times times.
 * It adds the car to a lane. Lastly it pushes an object added update.
 *
 * \param direction The direction of the intersection where the car will originate.
 * \param lane A target variable that is set to the lane number where the car is added.
 * \return The new car.
 */
Car *JPSimulationEngine::makeCar(int direction, int &lane)
{
	double theta = 0, x = 0, y = 0;
	Car *car = new Car();

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
 * \param car the new car
 * \param direction The direction of the intersection where the car is being added.
 * \returns The lane number that the car should be added to.
 */
int JPSimulationEngine::determineLane(Car* car, int direction) const
{
	//Valid lanes will be consecutive
	int numValid = 0;
	int startValid = -1;
	int desire;

	//get direction to match against
	switch(car->getTurnDirection())
	{
		case Car::DESIRE_LEFT: desire = JPLane::LEFT; break;
		case Car::DESIRE_RIGHT: desire = JPLane::RIGHT; break;
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
 *  \param lane The lane from which the next car is desired.
 *  \param dir The direction of the lane. (Used for translating x/y into relative position.)
 *  \param leng A target variable for the length of the car.
 *  \param pos A target variable for the position of the car.
 *  \param speed A target variable for the speed of the car
 *  \param dSpeed A target variable for the desired speed of the car.
 *
 *  \return The next car in the lane. NULL if the lane is empty.
 */
Car* JPSimulationEngine::getNextCar(JPLane* lane, int dir, double& leng, double& pos,
	double& speed, double& dSpeed)
{
	Car *car = lane->getNextCar();;

	//If last car exit.
	if(NULL == car)
		return NULL;
	leng = car->getLength();
	speed = car->getSpeed();
	dSpeed = car->getDesiredSpeed() * 5280 /3600;//assuming speed limit +/-
	dSpeed += _intersection->getSpeedLimitsInFPS(dir);

	//set a minimum desired speed of 5 MPH as a fail safe
	if(dSpeed < 5)
		dSpeed = 5;

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

void JPSimulationEngine::updateYellowTimes(const double stepTime)
{
	int dir, ln, c;
	bool caution[2];

	//cycle through directions and lanes
	for(dir = 0; dir < 4; dir++)
		for(ln = 0; ln < _laneCounts[dir]; ln++)
		{
			_light->getState(dir, ln, _time);
			//todo incorporate light states
			caution[0] = false;
			caution[1] = false;

			//update the yellow times
			for(c = 0; c < 2; c++)
			{
				if(! caution[c]) //not yellow, clear
					_yellowTime[dir][ln][c] = -1;
				else if ( _yellowTime[dir][ln][c] >= 0) //still yellow, inc.
					_yellowTime[dir][ln][c] += stepTime;
				else //new yellow, zero
					_yellowTime[dir][ln][c] = 0;
			}
		}
}
