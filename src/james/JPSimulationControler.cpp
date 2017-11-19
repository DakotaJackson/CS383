/*
 * SimulationControler.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: james
 */

#include "../../inc/JPSimulationControler.h"

JPSimulationControler *JPSimulationControler::_unique;

JPSimulationControler::JPSimulationControler()
{
	_duration = 5 * 60; //default 5 minutes
	_multiThread = false; //hopefully I will not have to handle threads in this clas
	_paused = true; //not running till we tell it to
	_simTime = 0;
	_timeScale = 1.0; //realtime
	_engine = JPSimulationEngine::getInstance();
}

JPSimulationControler* JPSimulationControler::getInstance()
{
	if(! _unique)
		_unique = new JPSimulationControler();

	return _unique;
}

void JPSimulationControler::start()
{
	//todo build start
}

void JPSimulationControler::pause()
{
	//todo pause
}

void JPSimulationControler::terminate()
{
	//todo build terminate
}

JPSimulationControler::~JPSimulationControler()
{
	// TODO Auto-generated destructor stub
}


void JPSimulationControler::setMultiThread(bool multiThread) {
	_multiThread = multiThread;
}

void JPSimulationControler::setDuration(double duration) { _duration = duration; }
const JPSimulationEngine* JPSimulationControler::getEngine() const{ return _engine; }
double JPSimulationControler::getDuration() const { return _duration; }
bool JPSimulationControler::isMultiThread() const { return _multiThread; }
bool JPSimulationControler::isPaused() const { return _paused; }
double JPSimulationControler::getSimTime() const { return _simTime; }
/** This is the proportion of simulated to real time. (i.e.) 1.0 is real time, < 1.0 is faster than real time, > 1.0 is greater than real time. The default is 1.0 */
double JPSimulationControler::getTimeScale() const { return _timeScale; }
/** \copydetail JPSimulationControler::getTimeScale() */
void JPSimulationControler::setTimeScale(double timeScale){	_timeScale = timeScale; }

