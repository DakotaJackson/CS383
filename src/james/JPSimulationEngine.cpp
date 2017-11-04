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
	_initTime = 300.0;
	_timeScale = 1.0;
	_time = 0.0;
	_paused = 1;

	int i;
	for(i = 0; i<4;  i++)
		_laneCounts[i] = 0;

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

void JPSimulationEngine::step(double sec)
{
	if( ! _initialized)
		init();

	//todo cycle through directions and lanes
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

void JPSimulationEngine::init()
{
	_initialized = true; //prevent infinite recursion
	//todo initialize next car time
	_time = 0;
	//todo raise initTime to the next highest cycle time
	//todo step through 95% of init time 2 sec/step
	//todo step through rest of init time at 0.1 sec/step
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
		_nextCreationTime[direction] =_trafficModel->getNextTiming(direction);
	}

}
