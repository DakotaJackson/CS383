/*
 * JPTrafficModel.h
 *
 *  Created on: Oct 11, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_TRAFFICMODEL_H_
#define SRC_JAMES_TRAFFICMODEL_H_
#include <random>
#include "../inc/JPTrafficModelExceptions.h"
/**
 * \addtogroup ENG
 * @{
 */

/**
 * \brief Generates entry timing and direction of new cars.
 *
 * This class is used to determine when new cars are added to the model, and what direction they will go.
 * For each direction the rate in cars per hour is specified as is the probability  for eache direction.
 * The probabilities are relative so they do not need to add up to 100.
 *
 * Setup is as follows:
 * \code{cpp}
 * JPTrafficModel = *model;
 * model = new JPTrafficModel;
 * model->setProbability(JPIntersection::NORTH, 20, 20, 60);
 * model->setProbability(JPIntersection::SOUTH, 15, 20, 60);
 * model->setProbability(JPIntersection::EAST, 20, 15, 60);
 * model->setProbability(JPIntersection::WEST, 20, 20, 70);
 * model->setTrafficRate(JPIntersection::NORTH, 720); //1 car per 5 seconds
 * model->setTrafficRate(JPIntersection::SOUTH, 720); //1 car per 5 seconds
 * model->setTrafficRate(JPIntersection::EAST, 720); //1 car per 5 seconds
 * model->setTrafficRate(JPIntersection::WEST, 720); //1 car per 5 seconds
 * \endcode
 */
class JPTrafficModel {
public:
	JPTrafficModel();
	/**
	 * \brief Set the relative probability that a car entering from the given direction
	 * will want to turn right, turn left or go straight
	 *
	 * \param direction The direction the car is going or side of the intersection being entered (e.g. JPIntersection::NORTH or JPIntersection::SOUTH)
	 * \param left The relative probability of a car wanting to turn left
	 * \param right The relative probability of a car wanting to turn right
	 * \param straight The relative probability of a car wanting to go straight
	 *
	 * Because the probabilities are relative, they do not need to add up to 100
	 */
	void setProbability(int direction, double left, double right, double straight);

	/**
	 * \brief Sets the rate that cars will be introduced for the given direction.
	 *
	 * \param direction The direction the car is going or side of the intersection being entered (e.g. JPIntersection::NORTH or JPIntersection::SOUTH)
	 * \param rate The rate at which cars enter in cars per hour.
	 */
	void setTrafficRate(int direction, double rate);

	/**
	 * \brief Returns the time till the next car and sets its turn direction.
	 *
	 * \param direction The direction the car is going or side of the intersection being entered (e.g. JPIntersection::NORTH or JPIntersection::SOUTH)
	 * \return The amount of time until the next car enters a lane going the given direction unless the rate is 0. If the rate is 0 it returns -1.
	 */
	double getNextTiming(int direction);

	/**
		 * \brief Returns the desired turn direction for the next car to be created based on its original direction.
		 *
		 * \param direction The direction the car is going or side of the intersection being entered (e.g. JPIntersection::NORTH or JPIntersection::SOUTH)
		 * \return The desired turn direction. One of SFCar::DESIRE_RIGHT, SFCar::DESIRE_STRAIGHT, or SFCar::DESIRE_LEFT
		 */
	int getNextTurnDirection(int direction);
	virtual ~JPTrafficModel();

private:
	double _rate[4];
	/** \brief A cumulative distribution function of the turn directions  for each interesection direction. */
	double _turnCDF[4][3];
	/** \brief maps indices of the CDF to turn directions */
	int _directionMappings[3];

	//random number generator stuff
	std::default_random_engine *gen; //An input stream for the RNGs
	std::poisson_distribution<long> *poisson[4]; //four Poisson distributions, one for each direction
	std::uniform_real_distribution<double> *uniform; //A single uniform distribution
};
/** @} */
#endif /* SRC_JAMES_TRAFFICMODEL_H_ */
