/*
 * SimulationControler.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: james
 */

#include "../../inc/JPSimulationControler.h"
//#include <time.h> //timespec, nanosleep (the nix/cygwin way not mingw)
#include <windows.h> //sleep function
#include <sys/time.h> //timeval, gettimeofday
#include <math.h> //modf

JPSimulationControler *JPSimulationControler::_unique;

JPSimulationControler::JPSimulationControler()
{
	_duration = 5 * 60; //default 5 minutes
	_multiThread = false; //hopefully I will not have to handle threads in this clas
	_paused = true; //not running till we tell it to
	_simTime = 0;
	_timeScale = 1.0; //realtime
	_engine = JPSimulationEngine::getInstance();
	gettimeofday(&_simEpoch, NULL);
}

JPSimulationControler* JPSimulationControler::getInstance()
{
	if(! _unique)
		_unique = new JPSimulationControler();

	return _unique;
}

void JPSimulationControler::start()
{
	//a seperate private method is used in case we need multithreading later
	run();
}

void JPSimulationControler::run()
{
	//todo build start
	_paused = false;
	//double initialSimTime;
	double initialRealTime = -1;
	double initialStepTime = -1;
	double initialSpeed = _timeScale;
	//double currentRealTime;
	double stepTime; //how long is a step
	double target;
	long steps = 0;

	//cycle until paused or duration is reached
	while( (! _paused) &&
			(_duration < 0 || _simTime < _duration) )
	{
		//if either timeScale or time step changed, re-baseline
		stepTime = _engine->getStepTime();
		if(initialSpeed != _timeScale || initialStepTime != stepTime )
		{
			initialRealTime = getTime();
			steps = 0;
		}

		//advance the simulation
		_engine->step();
		steps++;
		_simTime += stepTime;

		//calculate when the next update should occur
		target = steps * stepTime * _timeScale +  initialRealTime;
		sleepTill(target);
	}
}

void JPSimulationControler::pause()
{
	//todo pause (maybe done)
	_paused = true;
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
/** \param duration The amount of time the simulation should run. -1 if it should run infinitely */
void JPSimulationControler::setDuration(double duration) { _duration = duration; }
const JPSimulationEngine* JPSimulationControler::getEngine() const{ return _engine; }
double JPSimulationControler::getDuration() const { return _duration; }
bool JPSimulationControler::isMultiThread() const { return _multiThread; }
bool JPSimulationControler::isPaused() const { return _paused; }
double JPSimulationControler::getSimTime() const { return _simTime; }
/** This is the proportion of simulated to real time. (i.e.) 1.0 is real time, < 1.0 is faster than real time, > 1.0 is greater than real time. The default is 1.0 */
double JPSimulationControler::getTimeScale() const { return _timeScale; }
/** \copydetails JPSimulationControler::getTimeScale() */
void JPSimulationControler::setTimeScale(double timeScale) {
	_timeScale = timeScale;
}


double JPSimulationControler::getTime()
{
	struct timeval now;
	gettimeofday(&now, NULL);

	//whole seconds
	double time = now.tv_sec - _simEpoch.tv_sec;

	//add in microseconds
	if( now.tv_usec > _simEpoch.tv_usec)
		time += (now.tv_usec - _simEpoch.tv_usec) / 1.0e6;
	else
		time += (_simEpoch.tv_usec- now.tv_usec) / 1.0e6;

	return time;
}

void JPSimulationControler::sleepTill(double time)
{
	//calculate how long to sleep
	double seconds = time - getTime();
	if( seconds < 0)
		return; //we are behind schedule

	long milisec = (long)(seconds * 1000);
	Sleep(milisec);

	/* Works in cygwin and linux, but not mingw
	//double ipart, fpart;
	//construct a timespec
	struct timespec delay;
	fpart = modf(seconds, &ipart);
	delay.tv_sec = (int)ipart;
	delay.tv_nsec = (long)(fpart * 1e9);

	//sleep
	struct timespec dontcare;
	nanosleep(&delay, &dontcare);
	*/
}
