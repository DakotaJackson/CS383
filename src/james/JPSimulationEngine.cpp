/*
 * SimulationEngine.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#include "../../inc/JPSimulationEngine.h"

JPSimulationEngine::JPSimulationEngine()
{
	// TODO Auto-generated constructor stub
	_duration = 0.0;
	_initTime = -1; //flag for needing to be set
	_timeScale = 1.0;
	_time = 0.0;
	_paused = 1;
	_stepTime = 0.1; //default step time is 0.1 seconds
	_initialized = false;

	int i;
	for(i = 0; i<4;  i++)
		_laneCounts[i] = 0;

	//set null pointers to the needed parameters
	_graphic = 0;
	_intersection = 0;
	_iGrid = 0;
	_trafficModel = 0;
	_light = 0;
}

JPSimulationEngine::~JPSimulationEngine()
{
	// TODO Auto-generated destructor stub
}

void JPSimulationEngine::start()
{

}

void JPSimulationEngine::pause()
{
}

void JPSimulationEngine::step(){ step(_stepTime); }

/**
 * \brief Advance the state of the simulation by sec seconds.
 *
 * This function causes the simulation engine to perform the calculations
 * and modification necessary to advance the simulation. For example if step(0.1)
 * is called, all cars in the simulation will be moved to their positions 0.1
 * seconds from now. It also advances the simulation's internal clock.
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
			processLane(_intersection->getLane(dir,laneNum));
	_time += sec;
}

/*
double* JPSimulationEngine::getThroughput(int direction, int &laneCount)
{
	double *throughput;
	throughput = new double[consts::MAX_LANES];
	return throughput;
}
*/
void JPSimulationEngine::run()
{

}

double JPSimulationEngine::intersectionDeceleration(double pos, double speed,
		double pcPos, double pcSpeed, SFCar* car)
{
	return 0.0;
}

void JPSimulationEngine::end()
{
}

void JPSimulationEngine::setVisualization(JPUpdatableInterface* interface)
{
	//todo impilment visualization
}

void JPSimulationEngine::setTrafficModel(JPTrafficModel* model){ _trafficModel = model; }
void JPSimulationEngine::setIntersection(JPIntersection* intersection){ _intersection = intersection; }
void JPSimulationEngine::setTrafficLight(DJTrafficLightManager* light){ _light = light; }
void JPSimulationEngine::setStepInterval(double secs){ _stepTime = secs; }
void JPSimulationEngine::setInitTime(double secs) { _initTime = secs; }

void JPSimulationEngine::processLane(JPLane* lane)
{
	//todo write process lane
	double prevSpeed = -1;
}

void JPSimulationEngine::checkPrereqs()
{
	//todo check that the intersection is finalized
	//todo check that all of the inputs are set.
	//todo setup _iGrid
}
void JPSimulationEngine::init()
{
	checkPrereqs();
	_initialized = true; //prevent infinite recursion

	//initialize car creation and yellow times
	int dir = 0;
	for(dir = 0; dir < 4; dir++)
	{
		_nextCreationTime[dir] =  _trafficModel->getNextTiming(dir);
		_yellowTime[dir] = -1;
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
void JPSimulationEngine::addCars(int direction, JPLane lane, double timeStep)
{
	double effTime = _time + timeStep;

	//handle rates of zero by skipping
	if(_nextCreationTime[direction] < 0)
		return;

	while(effTime < _nextCreationTime[direction])
	{
		//todo new Car(_trafficModel->getNextTurnDirection(direction))
		_nextCreationTime[direction] += _trafficModel->getNextTiming(direction);
	}

}
