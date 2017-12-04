/*
 * JPLane.h
 *
 *  Created on: Oct 20, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPLANE_H_
#define SRC_JAMES_JPLANE_H_
#include <stdexcept>
//change this when I have a real class to work with
#include "SFCar.h"

//using namespace::std;
#include "LinkedList.cpp"

/**
 * \addtogroup ENG
 * @{
 */

/**
 * \brief A lane object that serves as an iterable container for cars.
 *
 * A lane is a linked list of cars that may be iterated over for computation or rendering.
 * The list is primarily operated as a queue with a few special functions for early
 * removal and addition. Throughout this documentation, the beginning of the lane
 * refers the first i.e. forward most car. So when iterating over the lane a given
 * car will be moved before the car that is physically behind it.
 *
 * This class is NOT THREAD SAFE. Due to the use of the iterator, only one thread
 * should access an instance of this class at a given time.
 *
 * Usage:
 * \code{cpp}
 * SFCar *car;
 * lane->resetToFirstCar();
 * while(0 != (car = lane->getNextCar()) )
 * {
 * 	//do stuff with car
 * }
 * \endcode
 */
class JPLane
{
public:

	/**
	* \brief Designates  a lane that permits going straight.
	*
	* Lane turn directions can be added. Initializing a lane with (JPIntersection::STRAIGHT + JPIntersection::RIGHT)
	* will allow cars in that lane to go either straight or right.
	*/
	static const int STRAIGHT = 1;

	/**
	 * \brief Designates a lane that permits right turns.
	 *
	 * Lane turn directions can be added. Initializing a lane with (JPIntersection::STRAIGHT + JPIntersection::RIGHT)
	 * will allow cars in that lane to go either straight or right.
	 */
	static const int RIGHT = 2;

	/**
	 * \brief Designates a lane that permits left turns.
	 *
	 * Lane turn directions can be added. Initializing a lane with (JPIntersection::STRAIGHT + JPIntersection::RIGHT)
	 * will allow cars in that lane to go either straight or right.
	 */
	static const int LEFT = 4;

	/**
	 * Create a lane with turnOptions
	 */
	JPLane(int turnOptions, int leftTarget, int rightTarget);

	/**
	 * \brief resets the iterator back to the first car.
	 *
	 * This will cause the getNextCar() method to restart at the beginning of the
	 * lane. The next call to getNextCar() will return the first car.
	 */
	int resetToFirstCar();

	/**
	 * \brief Returns the next car in the lane.
	 *
	 * If this is the first call since resetToFirstCar the first car will be returned.
	 * \return Zero if there are no more cars in the lane, otherwise the next.
	 */
	SFCar *getNextCar();


	/**
	 * \brief Remove the last car to be returned from the lane.
	 *
	 * This is used for early removal of cars that change lanes.
	 */
	void removeCurrentCar();

	/**
	 * \brief Remove the first car in the lane.
	 *
	 * This is when the first car has reached the tracked boundary and we no longer
	 * care about it.
	 */
	SFCar *removeFirstCar();  //throw (std::runtime_error);

	/**
	 * \brief Add a car at specific physical position within the lane.
	 *
	 * This is used to move a car into its new lane when turning.
	 * \param car the car to be added.
	 * \param position the position in feet
	 */
	void addCarAtPos(SFCar *car, double position);

	/**
	 * \brief Add a car at the end of the lane.
	 *
	 * \param car the car to be added.
	 */
	void addCarAtEnd(SFCar *car);

	/*//dropping
	 * \brief Flag the current car in the iteration as the first rendered.
	 *
	 * This is used while the simulation engine is iterating over the lane and
	 * processing it. When the engine reaches the first car that is within the
	 * visualization's field of view, it flags that car with this method.
	 */
	//void flagCarAsFirstRendered();

	virtual ~JPLane();
	bool isEmpty() const;

	/** \brief Return the number of cars in the lane */
	int getSize() const;

	/** \brief Return the destination lane number for cars that turn left */
	int getLeftTarget() const;

	/** \brief Return the destination lane number for cars that turn right */
	int getRightTarget() const;

	/** \brief return the turn configuration for this lane. */
	int getTurnOptions() const;

private:
	int _turnOptions;
	int _leftTarget;
	int _rightTarget;
	//bool _firstFlag;
	int _position;
	SFCar *_lastCar;

	LinkedList<SFCar*> *_list;
	Iterator<SFCar*> *_iter;

	//bool _renderFlagged; //dropping this
};
/** @} */
#endif /* SRC_JAMES_JPLANE_H_ */
