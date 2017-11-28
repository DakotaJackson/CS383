/*
 * JPIntersectionExceptions.h
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */
#include <exception>
/* QuickList
 * JPMalformedIntersectionException
 * JPConfigurationOrderException w/ numbers
 * JPMultipleIntersectionsException
 * JPTwoLanesToOneException
 * JPLaneCollidesWithOncomingLane
 * JPTurningLaneCrossingStraightLane
 * JPLaneNumberOutOfBounds
 * JPDirectionOutOfBounds
 */

/**
 * \defgroup EXC Exceptions
 * @{
 */


//to add: IntersectionException super class, cannotFinalizeException, maybe laneAlreadyExistsException
#ifndef SRC_JAMES_MALFORMEDINTERSECTIONEXCEPTION_H_
#define SRC_JAMES_MALFORMEDINTERSECTIONEXCEPTION_H_

/**
 * \brief A base class of intersection related exceptions.
 */
class JPIntersectionException: public std::exception
{
public:
	JPIntersectionException();
	virtual ~JPIntersectionException() throw();
	virtual const char* what() const throw();
};

/** \brief Configuration steps were performed out of order */
class JPConfigurationOrderException : public JPIntersectionException
{
public:
	JPConfigurationOrderException();
	JPConfigurationOrderException(int which);
	int getDetail();
	virtual ~JPConfigurationOrderException() throw();
	virtual const char* what() const throw();
	/** \brief The configuration has already been finalized. */
	static const int CONFIG_FINALIZED = 1;
	/** \brief Offset cannot be set after you have begun adding lanes. */
	static const int CONFIG_OFFSET_AFTER_LANES = 2;
	/** \brief Lanes cannot be added without first setting the offsets. */
	static const int CONFIG_LANES_BEFORE_OFFSET = 3;
	//** \brief Speed Limits must be set before attempting to finalize. */
	//static const int FINALIZE_MISSING_SPEED_LIMITS = 4;
	/** \brief Cannot finalize because lanes are missing. */
	static const int FINALIZE_MISSING_LANES = 5;
	//** \brief Cannot finalize because lane lengths are missing. */
	//static const int FINALIZE_MISSING_LANE_LENGTHS = 6;
	//static const int CONFIG_FINALIZED = 1; /** \brief  */

private:
	int _detail;
};

/** \brief The intersection has been configured improperly */
class JPMalformedIntersectionException: public JPIntersectionException
{
public:
	JPMalformedIntersectionException();
	JPMalformedIntersectionException(int direction);
	JPMalformedIntersectionException(int direction, int lane);
	virtual ~JPMalformedIntersectionException() throw();
	int getOriginationLane();
	int getDirection();
	virtual const char* what() const throw();

private:
	int _lane;
	int _direction;
};

/**
 * \brief Two turn lanes are trying to turn into the same lane.
 */
class JPTwoLanesToOneException: public JPMalformedIntersectionException
{
public:
	JPTwoLanesToOneException(int direction, int thisLane, int targetLane, int collidingLane );
	virtual const char* what() const throw();

	/**
	 * \brief Returns the lane that both lanes in the current direction are trying to turn into.
	 */
	int getTargetLane();

	/**
	 * \brief Returns the other lane from the same directions that this lane is trying to turn into.
	 */
	int getCollidingLane();

private:
	int _targetLane;
	int _collidingLane;
};

/**
 * \brief Added lane will collide with an oncomming lane
 */
class JPLaneCollidesWithOncomingLaneException: public JPMalformedIntersectionException
{
public:
	JPLaneCollidesWithOncomingLaneException(int direction, int thisLane, int collidingLane );
	virtual const char* what() const throw();
	/**
	 * \brief Returns the other lane from the same directions that this lane is trying to turn into.
	 */
	int getCollidingLane();
private:
	int _collidingLane;
};

/**
 * \brief A turning lane will cross a straight lane.
 *
 *  Thrown when A) the added lane is a right turn lane and there is a lane to the right that permits straight, B) if the added lane is a left turn lane and there is a lane to the left that permits straight, or C) the added lane permits straight and there is either a right turn lane to the left or a left turn lane to the right
 */
class JPTurningLaneCrossingStraightLaneException: public JPMalformedIntersectionException
{
public:
	JPTurningLaneCrossingStraightLaneException(int direction, int thisLane);
	virtual const char* what() const throw();
};

/**
 * \brief Lane offset is less than 1
 */
class JPLaneOffsetException: public JPMalformedIntersectionException
{
public:
	JPLaneOffsetException();
	virtual const char* what() const throw();
};

/**
 * \brief This exception is thrown when no lane exists for the specified lane number.
 */
class JPLaneNumberOutOfBoundsException: public JPMalformedIntersectionException
{
public:
	JPLaneNumberOutOfBoundsException(int lane);
	virtual const char* what() const throw();
};

/**
 * \brief The specified direction is not valid.
 *
 * Direction must be one of ( JPIntersection::NORTH, JPIntersection::SOUTH, JPIntersection::EAST, JPIntersection::WEST, JPIntersection::NORTHBOUND, JPIntersection::SOUTHBOUND, JPIntersection::EASTBOUND, or JPIntersection::WESTBOUND)
 */
class JPDirectionOutOfBoundsException: public JPMalformedIntersectionException
{
public:
	JPDirectionOutOfBoundsException(int direction);
	virtual const char* what() const throw();
};

/** @} */

#endif /* SRC_JAMES_MALFORMEDINTERSECTIONEXCEPTION_H_ */
