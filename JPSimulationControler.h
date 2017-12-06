/*
 * SimulationControler.h
 *
 *  Created on: Nov 19, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_SIMULATIONCONTROLER_H_
#define SRC_JAMES_SIMULATIONCONTROLER_H_
#include "JPSimulationEngine.h"
#include <windows.h> //sleep function
//# include <sys/time.h>

/**
 * \defgroup ENG Simulation Engine
 * @{
 */

class JPSimulationControler {
public:
	static JPSimulationControler* getInstance();
	void start();
	void pause();
	void terminate();
	/** \brief return the duration that simulation is supposed to run */
	double getDuration() const;
	/** \brief set the duration that simulation is supposed to run */
	void setDuration(double duration);
	/** \brief hopefully not needed */
	bool isMultiThread() const;
	/** \brief hopefully not needed */
	void setMultiThread(bool multiThread);
	/** \brief returns whether the simulation is paused */
	bool isPaused() const;
	/** \brief returns the amount of time elapsed in the simulation */
	double getSimTime() const;
	/** \brief returns the time scale (e.g. comparison to real time */
	double getTimeScale() const;
	/** \brief set how fast the simulation advances compared to real time */
	void setTimeScale(double timeScale);
	const JPSimulationEngine* getEngine() const;

//	void setTimeScale(double speed);
//	void setDuration();

private:
	JPSimulationControler();
	virtual ~JPSimulationControler();
	/** return the time in seconds since simulation epoch */
	double getTime();
	void run();
	/** sleep until time seconds past controller start */
	void sleepTill(double time);

	JPSimulationEngine *_engine;
	static JPSimulationControler *_unique;
	bool _paused;
	bool _multiThread; //internally mutlithread
	double _duration;  //not used at present
	double _timeScale; //default 1.0 = realtime
	double _simTime;

	//FILETIME fileTime;
	//GetSystemTimeAsFileTime(&fileTime);
	FILETIME _simEpoch;

};
/** @} */
#endif /* SRC_JAMES_SIMULATIONCONTROLER_H_ */
