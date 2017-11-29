/*
 * JPSimulationEngine.h
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#ifndef JPSIMULATIONENGINE_H_
#define JPSIMULATIONENGINE_H_
#include "JPConstants.h"
#include "JPLane.h"
#include "JPIntersection.h"
#include "JPIntersectionGrid.h"
#include "JPTrafficModel.h"
#include "JPUpdatableInterface.h"
#include "../src/james/SFCar.h"
#include "DJTrafficLightManager.h"
#include "JPObservableSimulation.h"
#include "../test/JPLightTestStub.h" //todo remove on merge
#include "JPOtherException.h"
/**
 * \defgroup ENG Simulation Engine
 * @{
 */

/**
 * \brief The main computational engine for the simulation.
 *
 * This class is responsible for advancing the state of the simulation. It does this primarily by
 * using one of the two step functions. While not necesary, it is recomend to run init seperately.
 * Usage
 *	\code
 *	//setup
 * JPSimulationEngine *engine = new JPSimulationEngine();
 * engine->setTrafficModel(model);
 * engine->setIntersection(intersection);
 * engine->setTrafficLight(light);
 * engine->init();
 *
 * //running the simulation
 * while(true == stillWantToRun)
 * {
 * 	engine->step(0.1);
 * 	//do something such as draw the cars
 * }
 *
 *	\endcode
 */
class JPSimulationEngine: JPObservableSimulation
{
public:

	/** @{ */
	//control

	/** \brief Advance the simulation by preset time. */
	void step();
	 /** \brief Advance the simulation by sec seconds */
	void step(double sec);
	 /** \brief Terminate the simulation allow for report generation */
	void end();
	/** \brief Initialize the simulation and run for a short time to populate the lanes */
	void init();
	/** @} */


	//configuration /** @{ */
	/** \brief Add the traffic model to the simulation */
	void setTrafficModel(JPTrafficModel *model);
	/** \brief Add the intersection to the simulation */
	void setIntersection(JPIntersection *intersection);
	//** \brief Add the traffic light to the simulation */
	//void setTrafficLight(DJTrafficLightManager *light); //todo swap on merge
	void setTrafficLight(JPLightTestStub *light);

	/** \brief Set how long the initialization phase runs */
	void setInitTime(double secs);
	/** \brief Set the preset interval for advancing the simulation */
	void setStepInterval(double secs);
	virtual ~JPSimulationEngine();

	static JPSimulationEngine* getInstance();
	/** \brief get the calculation interval (step time)*/
	double getStepTime() const;
	/** \brief set the calculation interval (step time)*/
	void setStepTime(double stepTime);
	/** \brief Return the internal elapsed time (seconds) in the simulation */
	double getTime() const { return _time;}

	const JPTrafficModel* getTrafficModel() const { return _trafficModel;}

	//double* getThroughput(int direction, int &laneCount);
	//getWhateverElseWeTracked()

private:
	//Base configuration
	int _laneCounts[4];
	double _initTime;  //default 5 minutes
	double _stepTime; //seconds default 0.1

	//Internal Constants
	const double turnSpeed = 20 * 5280/3600; //20 mph
	const double acceleration = 5.0 * 5280/3600; //ft/s^2 from 5 mph/s
	//const double reactionTime= 0.25; //probably not used

	//internal simulation objects
	//JPUpdatableInterface *_graphic;
	JPIntersection *_intersection;
	JPIntersectionGrid *_iGrid;
	JPTrafficModel *_trafficModel;
	//DJTrafficLightManager *_light; //todo swap on merge
	JPLightTestStub *_light;

	//Running Variables
	double _time;
	bool _initialized;
	bool _updating;
	//long _throughput[4][MAX_LANES_MACRO];
	double _nextCreationTime[4];
	double _yellowTime[4][MAX_LANES_MACRO];
	int _turnOpts[4][MAX_LANES_MACRO]; //local copy
	double _intersectionBounds[4];

	//private members for singleton control
	static JPSimulationEngine *_unique;
	static void destory(); //private method that destroys the instance for testing
	JPSimulationEngine();
	JPSimulationEngine(JPSimulationEngine const&){};  //copy constructor
	//JPSimulationEngine& operator=(JPSimulationEngine const&){}; //assignment operator
	friend class SETestClass;

	//Internal Methods
	double intersectionDeceleration(double pos, double speed, double pcPos, double pcSpeed, SFCar *car);
	//previous car's speed/pos
	//double carDeceleration(SFCar &car, double prevSpeed, double prevPos);

	//returns position
	//double translatePosition(int direction, int lnNum,
	double getPrevCarDecel(const double pSpeed, const double pPos, const double speed,
			const double dSpeed, const double pos, const double timeStep) const;
	void updateCar(SFCar *car,const int dir, double &speed,double &pos,const double accel, const double timeStep);
	void processLane(JPLane *lane, int direction, double stepTime);
	void addCars(int direction, double timeStep);
	void checkPrereqs();
	SFCar *getNextCar(JPLane *lane, int dir, double &leng, double &pos, double &speed, double &dspeed);
	SFCar *makeCar(int direction, int &lane);
	int determineLane(SFCar *car, int direction);

};
/** @} */
#endif /* JPSIMULATIONENGINE_H_ */
