/*
 * JPSimulationEngine.h
 *
 *  Created on: Sep 27, 2017
 *      Author: james
 */

#ifndef JPSIMULATIONENGINE_H_
#define JPSIMULATIONENGINE_H_
#define _USE_MATH_DEFINES //I want pi!

#include "JPConstants.h"
#include "JPLane.h"
#include "JPIntersection.h"
#include "JPIntersectionGrid.h"
#include "JPTrafficModel.h"
#include "JPUpdatableInterface.h"
#include "SFCar.h"
#include "DJTrafficLightManager.h"
#include "JPObservableSimulation.h"
#include "JPLightTestStub.h"
#include "JPOtherException.h"
#include "JPTrafficLightAdapter.h"
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

	/** \brief Get the instance of the simulation engine */
	static JPSimulationEngine* getInstance();
	/** \brief get the calculation interval (step time)*/
	double getStepTime() const;
	/** \brief set the calculation interval (step time)*/
	void setStepTime(double stepTime);
	/** \brief Return the internal elapsed time (seconds) in the simulation */
	double getTime() const { return _time;}

	/** \brief Return the traffic model used in the simulation */
	const JPTrafficModel* getTrafficModel() const { return _trafficModel;}

	//public so iGrid can use it
	/** \brief Retrieve the next car from the lane, and set a few variables. */
	SFCar *getNextCar(JPLane *lane, int dir, double &leng, double &pos, double &speed, double &dspeed);

private:
	//Base configuration
	int _laneCounts[4];
	double _initTime;  //default 5 minutes
	double _stepTime; //seconds default 0.1

	//Internal Constants
	const double turnSpeed = 25; //Feet per second
	const double acceleration = 5.0 * 5280/3600; //ft/s^2 from 5 mph/s default if car doesn't have a value

	//internal simulation objects
	JPIntersection *_intersection;
	JPIntersectionGrid *_iGrid;
	JPTrafficModel *_trafficModel;
	JPTrafficLightAdapter *_light;

	//Running Variables
	double _time;
	bool _initialized;
	bool _updating;
	double _nextCreationTime[4]; //when will the next car be created
	double _yellowTime[4][MAX_LANES_MACRO][2]; //0 = R/S, 1 L
	int _turnOpts[4][MAX_LANES_MACRO]; //local copy
	double _intersectionBounds[4];
	double _offsets[4];

	//private members for singleton control
	static JPSimulationEngine *_unique;
	static void destory(); //private method that destroys the instance for testing
	JPSimulationEngine();
	JPSimulationEngine(JPSimulationEngine const&){};  //copy constructor
	//JPSimulationEngine& operator=(JPSimulationEngine const&){}; //assignment operator
	friend class SETestClass;

	//Internal Methods
	/** \brief Verify that all required components have been added to the simulation. */
	void checkPrereqs();
	/** \brief Iterate over a lane processing each car in sequence starting from the forward-most */
	void processLane(int ln, int direction, double stepTime);

	//functions for adding and removing from the model
	/** Add cars to the simulation and schedule the next arrival */
	void addCars(int direction, double timeStep);
	/** \brief Generate and initialize car. */
	SFCar *makeCar(int direction, int &lane);
	/** \brief Determine which lane to put the car in. */
	int determineLane(SFCar *car, int direction) const;
	/** \brief Push an update that the car is being removed from the simulation and free the Car's memory */
	void dispose(SFCar *car, JPLane *lane);

	//position translation/read/write functions
	/** \brief Update a car object by computing and setting the new speed and position */
	void updateCar(SFCar *car,const int dir, double speed,double &pos,const double accel, const double timeStep);
	/** \brief Update a turning car object by computing and setting the new speed and position */
	void updateTurnCar(SFCar *car,const int dir, double speed,double &pos,const double accel, const int turn, const double timeStep, const int lane);
	/** \brief perform computations for exiting a turn */
	void exitTurn(SFCar *car, int dir, const double excess,const int turn, const int lane);
	//light functions
	/** \brief compute the command the light will give to the car */
	int determineLightEffect(SFCar *car, const int dir, const int ln) const;
	/** \brief Update tracking of how long each light has been yellow */
	void updateYellowTimes(const double stepTime);

	//deceleration/acceleration functions
	/** \brief Determine the amount of deceleration required or acceleration possible without coming within 5 feet of the next car.*/
	double getPrevCarDecel(const double pSpeed, const double pPos, const double speed,
			const double dSpeed, const double pos, const double timeStep) const;
	/** \brief Compute the deceleration required based on the state of the intersection (e.g. blocked, red light etc. */
	double getIntersectionDecel(SFCar *car,const int dir, const int ln, const double pos,
			const double speed, const double timeStep) const;
	/** \brief Calculate the time and deceleration to match pace between two cars while closing the gap. */
	double movingTargetDecel(const double V0, const double Vt, const double dX, double &time) const;
	/** \brief Calculate time and acceleration for deceleration from speed V0 to 0.  */
	double staticTargetDecel(const double V0, const double dX, double &time) const;
	/** \brief Calculate time and acceleration for deceleration from speed V0 to Vf.  */
	double staticTargetDecel(const double V0, const double Vf, const double dX, double &time) const;
	/** \brief Calculate the allowable acceleration based on a light effect of GO */
	double computeGoAccel(const int turnDir, const double speed, const double timeStep) const;

	/** \brief a list of possible effects (i.e. commands) that a light may have on a car */
	enum lightEffect {
		GO, ///The car may go. A basic green light.
		CAUTION, /// The car should try to slow down if it is too far. A typical yellow light between green and red.
		YIELD, ///The car must yield to traffic. This could be from a left yield signal or it could be returned for a car turning right at a red light.
		STOP ///The car must stop. A red light in the context of going straight or turning left.
	};

	//local redeffs for shorthand
	const int NORTH = JPIntersection::NORTH;
	const int SOUTH = JPIntersection::SOUTH;
	const int EAST = JPIntersection::EAST;
	const int WEST = JPIntersection::WEST;
	const int LANE_WIDTH = JPIntersection::LANE_WIDTH;

};
/** @} */
#endif /* JPSIMULATIONENGINE_H_ */
