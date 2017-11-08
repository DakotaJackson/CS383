/*
 * JPIntersection.h
 *
 *  Created on: Oct 21, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPINTERSECTION_H_
#define SRC_JAMES_JPINTERSECTION_H_
#include "JPLane.h"
#include "JPIntersectionExceptions.h"

/**
 * \addtogroup ENG
 * @{
 */

/**
 * \brief A class that serves as a container and validator for an intersection.
 *
 * Usage: Setup
 * Consider the following intersection.
 * \image html Intersection1.png "A sample intersection"
 * Here there are three soutbound lanes. The first can go either right or straight and the second can only go straight. The third is a left turn lane that is signal based. Drivers must wait for a green turn arrow or a flashing yellow turn arrow and a break in traffic. The northbound lanes are a mirror image of the southbound lanes.
 * There are two eastbound lanes the first can go either right or straight. The second is a left turn only. Here drivers must wait for break in traffic.
 * \code{cpp}
 * JPIntersection *intersection;
 * intersection = new JPIntersection();
 *
 *	//setup the intersection details
 *	//track cars for a half mile before center if the intersection
 *	intersection->setTrackedLaneLengths(2640, 2640, 2640, 2640);
 *	intersection->setTrackedExitDistance(600,600); //track cars for 200 yards past the center of the intersection
 *
 * //This intersection is aligned so that the NORTH/SOUTH lanes are offset by 2.5
 * //lane widths and EAST/WEST lanes are offset by 2 lane widths.
 * //i.e. the the northwest corner is 2.5 lane widths
 * //to the left of the center and 2 lane widths, above the center.
 *	//alternatively setLaneOffsets(int direction, double distance) can be used
 *	intersection->setLaneOffsets(2.5,2.5,2,2);
 *
 *	intersection->setSpeedLimits(35,35);
 *
 *	//add the individual lanes
 *	//addLane(int direction, int position, int turnOptions, int leftTarget, int rightTarget);
 *	intersection->addLane(JPIntersection::SOUTHBOUND, 0, JPLane::RIGHT + JPLane::STRAIGHT , 0, 0); //Lane in the first position can go either straight or right into the first westbound lane
 *	intersection->addLane(JPIntersection::SOUTHBOUND, 1, JPLane::STRAIGHT, 0, 0); //Lane in the second position can only go straight. Right and left targets will be ignored
 *	intersection->addLane(JPIntersection::SOUTHBOUND, 2, JPLane::LEFT, 1,0); // Lane only turns left and requires a signal. Left turns will enter the second eastbound lane
 *
 *	intersection->addLane(JPIntersection::WESTBOUND, 0, JPLane::RIGHT + JPLane::STRAIGHT , 0, 0); //Lane in the first position can go either straight or right into the first northbound lane
 *	intersection->addLane(JPIntersection::WESTBOUND, 1, JPLane::LEFT, 1, 0); // Lane only turns left and requires a signal. Left turns will enter the second eastbound lane
 *
 *	intersection->addLane(JPIntersection::NORTHBOUND, 0, JPLane::RIGHT + JPLane::STRAIGHT , 0, 0); //Lane in the first position can go either straight or right into the first eastbound lane
 *	intersection->addLane(JPIntersection::NORTHBOUND, 1, JPLane::STRAIGHT, 0, 0); //Lane in the second position can only go straight. Right and left targets will be ignored
 *	intersection->addLane(JPIntersection::NORTHBOUND, 2, JPLane::LEFT, 1,0); // Lane only turns left and requires a signal. Left turns will enter the second westbound lane
 *
*	intersection->addLane(JPIntersection::EASTBOUND, 0, JPLane::RIGHT + JPLane::STRAIGHT , 0, 0); //Lane in the first position can go either straight or right into the first southbound lane
 *	intersection->addLane(JPIntersection::EASTBOUND, 1, JPLane::LEFT, 1, 0); // Lane only turns left and requires a signal. Left turns will enter the second westbound lane
 * \endcode
 *
 * Usage: Accessing lanes.
 *\code{cpp}
 * Intersection *intersection;
 * //initialize or acquire intersection object...
 * int direction, laneNum;
 * int laneCounts[4];
 * JPLane *lane;
 *
 * intersection->getLaneCounts(laneCounts);
 * for(direction = 0; direction < 4; direction++)
 * {
 * 	for(laneNum = 0; laneNum < laneCounts[direction]; laneNum++)
 * 	{
 * 		lane = intersection->getLane(direction, laneNum);
 * 		//use lane
 * 	}
 * }
 * \endcode
 *
 *  The directions are GUARANTEED to be the consecutive
 *  numbers between 0 and 3 in a circular direction.
 *  It also follows that the opposite direction is always computable
 *  by adding two and computing the modulus.
 *  For example: SOUTHBOUND := (NORTHBOUND + 2) % 4.
 */
class JPIntersection {
public:
	//CONSTANT MEMBERS FOR INTERCLASS COMMUNICATION
	/**
	* \brief The maximum number of lanes supported. Presently 6.
	*
	* This is used in addition to the const value for instances where it is necessary to hard code the value such as
	* statically defined allocated arrays.
	 */
	#define MAX_LANES_MACRO 6

	/**
	 * \brief The maximum number of lanes supported. Presently 6.
	 *
	 * This is synonymous with the value in MAX_LANES_MACRO.
	 */
	static const int MAX_LANES = MAX_LANES_MACRO;

	/**
	 * \brief The width of the lane in feet (10).
	 */
	static const int LANE_WIDTH = 10;

	/*
	 *  \brief The maximum tracked length of
	 */
	static const int MAX_LANE_LENG = 2 * 5280;

		/**
		 * \brief The north position.
		 *
		 * This identifier is used to designate lanes that begin in the
		 * physically north position of the intersection. Synonymous with
		 * SOUTHBOUND.
		 */
	static const int NORTH = 0;

		/**
		 * \brief The east position.
		 *
		 * This identifier is used to designate lanes that begin in the
		 * physically north position of the intersection. Synonymous with
		 * WESTBOUND.
		 */
	static const int EAST = 1;

		/**
		 * \brief The south position.
		 *
		 * This identifier is used to designate lanes that begin in the
		 * physically north position of the intersection. Synonymous with
		 * NORTHBOUND.
		 */
	static const int SOUTH = 2;

		/**
		 * \brief The west position.
		 *
		 * This identifier is used to designate lanes that begin in the
		 * physically north position of the intersection. Synonymous with
		 * EASTBOUND.
		 */
	static const int WEST = 3;

		/**
		 * \brief Designates a lane where traffic travels in the south direction.
		 *
		 * Synonymous with NORTH.
		 */
	static const int SOUTHBOUND = NORTH;

		/**
		 * \brief Designates a lane where traffic travels in the west direction.
		 *
		 * Synonymous with JPIntersection::EAST.
		 */
	static const int WESTBOUND = EAST;


		/**
		 * \brief Designates a lane where traffic travels in the north direction.
		 *
		 * Synonymous with JPIntersection::SOUTH.
		 */
	static const int NORTHBOUND = SOUTH;

		/**
		 * \brief Designates a lane where traffic travels in the east direction.
		 *
		 * Synonymous with JPIntersection::WEST.
		 */
	static const int EASTBOUND = WEST;

	JPIntersection();

	/** \brief Set the offset (in lanes) of the rightmost lane. */
	void setLaneOffsets(double north, double south, double east, double west);
	/** \brief Set the offset (in lanes) of the rightmost lane. */
	void setLaneOffset(int direction, double offset);
	/** \brief Set the distance (in feet) that simulation tracks cars before the center of the intersection */
	void setTrackedLaneLengths(double north, double south, double east, double west);
	void setTrackedLaneLength(int direction, double distance);
	void setTrackedExitLengths(double northSouth, double eastWest);
	/** \brief Set speed limits in miles per hour */
	void setSpeedLimits(double northSouth, double eastWest);
	/** \brief Add a lane to the intersection in the specified position and direction */
	void addLane(int direction, int position, int turnOptions, int leftTarget, int rightTarget);

	/** \brief Return the speed limit in MPH */
	double getSpeedLimits(int direction);
	/** \brief Return the speed limit in ft/s */
	double getSpeedLimitsInFPS(int direction);
	/** \brief Finalize the configuration preventing further changes. */
	void finalize();



	/**
	 * \brief Return the offset of the lanes for the given direction.
	 *
	 * \param direction The direction as specified by JPIntersection::NORTH, JPIntersection::SOUTHBOUND, etc.
	 * \return The offset in lanes for the given direction.
	 */
	double getLaneOffset(int direction);

	/**
	 * \brief Return the offset of the lanes for the given direction.
	 *
	 * \param direction The direction as specified by JPIntersection::NORTH, JPIntersection::SOUTHBOUND, etc.
	 * \return The offset in feet for the given direction.
	 */
	double getLaneOffsetInFeet(int direction);

	/**
	 * \brief Set the counts array with the number of lanes in each direction.
	 *
	 * \param counts A destination array with at least four elements.
	 */
	void getLaneCounts(int counts[]);


	/**
	 * \brief Return the number of lanes for the given direction.
	 *
	 * \param direction The direction as specified by JPIntersection::NORTH, JPIntersection::SOUTHBOUND, etc.
	 */
	int getLaneCount(int direction);

	/**
	 * \brief Return the distance in feet cars will be tracked before entering the intersection.
	 *
	 */
	double getTrackedLaneLength(int direction);

	/**
	 * \brief Return the distance in feet cars should be tracked after exiting the intersection. The default is 300 feet.
	 *
	 */
	double getTrackedExitLength(int direction);

	/**
	 * \brief Get the lane object corresponding to the specified direction and position.
	 *
	 * \param direction The direction as specified by JPIntersection::NORTH, JPIntersection::SOUTHBOUND, etc.
	 * \param position The lane number from 0 to (getLaneCount(direction)-1)
	 *
	 * \return The lane object for the specified location.
	 */
	JPLane *getLane(int direction, int position);

	virtual ~JPIntersection();

	inline static void valdiateDirection(int direction)
	{
		if( direction < 0 || direction > 3)
			throw JPDirectionOutOfBoundsException(direction);
	}

private:
	//direction specific variables
	int _laneCounts[4];
	double _laneOffsets[4];
	double _laneLengths[4];
	double _laneExit[2]; //north and south
	double _speedLimits[2];

	bool _finalized;
	JPLane *_lanes[4][MAX_LANES_MACRO];

};

//old deprecated stuff that I designed away but may want later
/*
 * \brief Designates a lane that permits left turns without a left turn signal.
 *
 * Left turns have two distinct situations. The first is a left turn lane without an
 * explicit left turn signal. Here when the light is green, the driver waits for a break in
 * oncoming traffic before turning. The second situation is where the lane has an explicit
 * left turn signal either a three lamp with left arrows or a 5 lamp. This constant describes
 * first situation. It is mutually exclusive with JPIntersection::LEFT_ON_SIGNAL_ONLY.
 *
 * Lane turn directions can be added Initializing a lane with (JPIntersection::STRAIGHT + JPIntersection::RIGHT)
 * will allow cars in that lane to go either straight or right.
 */
//static const int LEFT_NO_SIGNAL = 4;

/*
 * \brief Left for lanes which may only turn left on a left arrow.
 *
 * Left turns have two distinct situations. The first is a left turn lane without an
 * explicit left turn signal. Here when the light is green, the driver waits for a break in
 * oncoming traffic before turning. The second situation is where the lane has an explicit
 * left turn signal either a three lamp with left arrows or a 5 lamp. This constant describes
 * second situation. It is mutually exclusive with JPIntersection::LEFT_NO_SIGNAL.
 *
 * Lane turn directions can be added Initializing a lane with (JPIntersection::STRAIGHT + JPIntersection::RIGHT)
 * will allow cars in that lane to go either straight or right.
 */
//static const int LEFT_ON_SIGNAL_ONLY = 8;

/** @} */
#endif /* SRC_JAMES_JPINTERSECTION_H_ */
