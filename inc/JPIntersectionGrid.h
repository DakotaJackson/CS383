/*
 * JPIntersectionGrid.h
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPINTERSECTIONGRID_H_
#define SRC_JAMES_JPINTERSECTIONGRID_H_
#include "../src/james/SFCar.h"
#include "JPIntersection.h"
/**
 * \addtogroup ENG
 * @{
 */

/**
 * \brief A grid representation of the inside of the intersection used for determining cross-directional interference.
 */
class JPIntersectionGrid {
public:
	JPIntersectionGrid();
	virtual ~JPIntersectionGrid();

	/**
	 * \brief check the intersection and return required (de/ac)celeration
	 *
	 * \return 0 if the intersection is clear
	 * 	a positive value of required deceleration if the car must slow down
	 * 	a negative value of the maximum allowable acceleration if the car can speed up but the lane is not entirely clear
	 */
	double checkPath(int direction, int lane, SFCar &car);
	double checkYield(int direction, int lane, SFCar &car);
	void setup(JPIntersection inters);
	void clearRow(int direction, int lane); //reset row at the beginning of processing a new lane
	void addCar(int direction, int lane, SFCar &car);

private:
	SFCar *_NorthSouthGrid[MAX_LANES_MACRO][MAX_LANES_MACRO][2];
	SFCar *_EastWestGrid[MAX_LANES_MACRO][MAX_LANES_MACRO][2];
	SFCar *_firstCars[4][MAX_LANES_MACRO];
	double _offsets[4];
	int _numLanes[4];

	//reference tables
	int _beginX[4];
	int _beginY[4];
	const int _incX[4] = {-1,1,-1,1}; //not set accurately
	const int _incY[4] = {-1,1,-1,1}; //not set accurately
};
/** @} */
#endif /* SRC_JAMES_JPINTERSECTIONGRID_H_ */
