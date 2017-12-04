/*
 * JPIntersectionGrid.h
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPINTERSECTIONGRID_H_
#define SRC_JAMES_JPINTERSECTIONGRID_H_
#define _USE_MATH_DEFINES //I want pi!
#include "../src/james/SFCar.h"
#include "JPIntersection.h"
/**
 * \addtogroup ENG
 * @{
 */

/**
 * \brief A grid representation of the inside of the intersection used for determining cross-directional interference.
 */
class JPIntersectionGrid
{
public:
	JPIntersectionGrid(JPIntersection *inter);
	virtual ~JPIntersectionGrid();

	/**\brief Check the intersection and return whether it is clear. */
	bool checkPath(const int direction, const int lane) const;
	bool checkYield(const int direction, const int lane, SFCar *car, const double speed, const double distance) const;
	/** \brief Depricated */
	void setFirstCar(const int direction, const int lane, SFCar *car);
private:
	SFCar *_firstCars[4][MAX_LANES_MACRO];
	double _offsets[4];
	double _bounds[4];
	int _numLanes[4];
	JPIntersection *_inter;
//	SFCar* getNextCar(JPLane* lane, int dir, double& leng, double& pos,

	bool checkLeftYield(const int direction, const int lane, const int tLane, const double clearTime) const;
	bool checkRightYield(const int direction, const int lane, const int tLane, const double clearTime) const;

	/** \brief Compute the arc distance for the turn */
	double getMaxArcDistance(const int direction, const int lane, const int tLane, const int turnDir) const;

	/** \brief Compute obstructions to Northbound/Soutbond traffic from the EAST */
	bool obstructedAboveX(const double x) const;
	/** \brief Compute obstructions to Northbound/Soutbond traffic from the WEST */
	bool obstructedBelowX(const double x) const;
	/** \brief Compute obstructions to Eastbound/Westbound traffic from the NORTH */
	bool obstructedAboveY(const double x) const;
	/** \brief Compute obstructions to Eastbound/Westbound traffic from the SOUTH */
	bool obstructedBelowY(const double x) const;

	//shorthand constants
	const int NORTH = JPIntersection::NORTH;
	const int SOUTH = JPIntersection::SOUTH;
	const int EAST = JPIntersection::EAST;
	const int WEST= JPIntersection::WEST;
	const double LANE_WIDTH = JPIntersection::LANE_WIDTH;

};
/** @} */
#include "JPSimulationEngine.h"
#endif /* SRC_JAMES_JPINTERSECTIONGRID_H_ */
