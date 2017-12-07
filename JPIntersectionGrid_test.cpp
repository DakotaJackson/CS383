/*
 * IntersectionGrid_test.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#include "JPIntersectionGrid.h"
#include "JPConstants.h"
#include "JPCarTestStub.h"
#include <stdio.h>

//gird position tests
int g1x1Test();
int g2x2Test();
int g3x3Test();
int g4x4Test();
int g5x5Test();
int g6x6Test();

int g1x2Test();
int g2x3Test();
int g3x2Test();
int g3x4Test();
int g3x5Test();
int g2x4Test();

int clear6x6test();

int twoCarsOneBlockTest();
int blockOverlapTest();
int accelerationTest();
int decelerationTest();
int yieldTest();


int main()
{
	int ret;
	ret = consts::testOuptut("Intersection Grid: 3x3 Grid Test", g3x3Test() );
	printf("ret: %d\n", ret);
/*
	ret = consts::testOuptut("Intersection Grid: 4x4 Grid Test", g4x4Test() );
	ret = consts::testOuptut("Intersection Grid: 5x5 Grid Test", g5x5Test() );
	ret = consts::testOuptut("Intersection Grid: 6x6 Grid Test", g6x6Test() );

	ret = consts::testOuptut("Intersection Grid: 1x2 Grid Test", g6x6Test() );
	ret = consts::testOuptut("Intersection Grid: 2x3 Grid Test", g6x6Test() );
	ret = consts::testOuptut("Intersection Grid: 3x2 Grid Test", g6x6Test() );
	ret = consts::testOuptut("Intersection Grid: 3x4 Grid Test", g6x6Test() );
	ret = consts::testOuptut("Intersection Grid: 3x5 Grid Test", g6x6Test() );
	ret = consts::testOuptut("Intersection Grid: 2x4 Grid Test", g6x6Test() );

	ret = consts::testOuptut("Intersection Grid: Clear 6x6 Test", clear6x6test() );

	ret = consts::testOuptut("Intersection Grid: Two Cars One Block Test", twoCarsOneBlockTest() );
	ret = consts::testOuptut("Intersection Grid: Block Overlap Test", blockOverlapTest());
	ret = consts::testOuptut("Intersection Grid: Acceleration Test", accelerationTest() );
	ret = consts::testOuptut("Intersection Grid: Deceleration Test", decelerationTest() );
	ret = consts::testOuptut("Intersection Grid: Yield Test", yieldTest());
*/
	if(175 == ret) printf("I still don't care!\n");
	return 0;
}

inline int g1x1Test()
{
	// 1 ft car placed in single grid position
	// check only the correct lane is blocked
	// clear entire intersection
	//repeat for all gird positions
	//repeat for both EASTWEST and NORTHSOUTH
	return 1;
}

inline int g2x2Test()
{
	//same as 1x1 but with a 2x2...
	return 1;
}

JPIntersectionGrid *setup3x3(Car *cars[], JPIntersection **intersection)
{
	JPIntersection *inter = new JPIntersection();
	*intersection = inter;

	int dir, ln;
	for(dir = 0; dir < 4; dir++)
	{
		inter->setLaneOffset(dir,3);
		inter->setTrackedLaneLength(dir, 300);
	}

	//north / south bound
	int nCars = 0;
	cars[nCars++] = new JPCarTestStub(10.0, -25, 30.5, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, -15, 30.5, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, -5, 30.5, 0, 0);

	//east (west bound)
	cars[nCars++] = new JPCarTestStub(10.0, 30.5, 25, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, 30.5, 15, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, 30.5, 5, 0, 0);

	//south (north bound)
	cars[nCars++] = new JPCarTestStub(10.0, 25, -30.5, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, 15, -30.5, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, 5, -30.5, 0, 0);

	//west (east bound)
	cars[nCars++] = new JPCarTestStub(10.0, -30.5, -25, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, -30.5, -15, 0, 0);
	cars[nCars++] = new JPCarTestStub(10.0, -30.5, -5, 0, 0);


	int carNm = 0;
	JPLane *lane;
	for(dir = 0; dir < 4; dir++)
		for(ln = 0; ln < 3; ln++)
		{
			inter->addLane(dir, ln, JPLane::STRAIGHT,0,0);
			inter->getLane(dir, ln)->addCarAtEnd(cars[carNm]);
			carNm++;
		}
	JPIntersectionGrid *grid = new JPIntersectionGrid(inter);
	return grid;
}
void printCar(Car *car)
{
	double x = car->getX();
	double y = car->getY();
	double theta = car->getTheta();
	double insim = car->getTimeInSim();
	double wait = car->getWaitTime();
	double speed = car->getSpeed();
	int turn = car->getTurnDirection();
	char trn = 'S';

	if( Car::DESIRE_RIGHT == turn )
		trn = 'R';
	else if( Car::DESIRE_LEFT == turn )
		trn = 'L';

	printf("X:%3.2f Y:%3.2f Th: %2.0f %c Sp:%2.1f St:%3.1f Wt:%3.1f ptr:%p\n",
			x, y, theta, trn, speed, insim, wait, car);
}

void printIntersection(JPIntersection *inter)
{
	int dir, ln;
	JPLane *lane;
	Car *car;
	for(dir = 0; dir < 4; dir++)
	{
//if(3 != dir) continue;
		printf("Direction: %d\n", dir);
		for(ln = 0; ln < inter->getLaneCount(dir); ln++)
		{
			lane = inter->getLane(dir,ln);
			lane->resetToFirstCar();
			while(0 != (car = lane->getNextCar()) )
			   printCar(car);
		}
	}
}

int g3x3Test()
{
	bool c = true; //clear
	bool b = false; //blocked

	// directional increment [dir]{X,Y} (really should be struct X, Y
	//whether X or is changed and which direction it is changed in

	int dirInc[][2] = {
	{0, -1},
	{-1,0},
	{0, 1},
	{1,0} };

	//each row corresponds to 1 car movement
	bool results[] = {
			//start state
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 1 north
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 2 north
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 3 north
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,


			//moving ln 1 east
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 2 east
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 3 east
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,


			//moving ln 1 south
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 2 south
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 3 south
			c, c, c,		b, b, b,		c, c, c, 	b, b, b,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,


			//moving ln 1 west
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 2 west
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,

			//moving ln 2 south
			b, b, b,		c, c, c,		b, b, b, 	c, c, c,
			c, c, c,		c, c, c,		c, c, c, 	c, c, c,
	};

	double movements[] = {
			1, //enter lane
			70, //tail clear lane (length + 2 x offset)
	};
	int numMoves = 2;

	//define cars
	//JPCarTestStub(double leng, double X, double Y, double speed, double dspeed);
	Car *cars[12];
	JPIntersection *inter;
	JPIntersectionGrid *grid = setup3x3(cars, &inter);
	int oDir, oLn, moveNum, iDir, iLn, resNum;
	Car *car;
	resNum = 0;

	//check start state
	for(iDir = 0; iDir <4; iDir++)
		for(iLn = 0; iLn < 3; iLn++)
		{
			printf("resNum: %d\n", resNum);
			if(results[resNum] != grid->checkPath(iDir, iLn))
			{
				printIntersection(inter);
				return (1 + resNum);
			}
			resNum++;
		}

	bool res;
	bool xFail = false;
	//check after each movement
	for(oDir = 0; oDir <4; oDir++)
		for(oLn = 0; oLn < 3; oLn++)
			for( moveNum = 0; moveNum < numMoves; moveNum++)
			{
				//move the car
				car = cars[oDir * 3 + oLn];
				car->setX(car->getX() + dirInc[oDir][0] * movements[moveNum]);
				car->setY(car->getY() + dirInc[oDir][1] * movements[moveNum]);

				for(iDir = 0; iDir <4; iDir++)
					for(iLn = 0; iLn < 3; iLn++)
					{
						res = grid->checkPath(iDir, iLn);
						if(results[resNum] != res)
						{
							//at this point if it is clear and shouldn't be, that's a minor
							if( results[resNum]) //if it should be clear, and was not return
							//printIntersection(inter);
								return (1 + resNum);
							xFail = true;
						}
						resNum++;
					}

			}
	if(xFail)
		return -1;

	return 0;
}

inline int g4x4Test()
{
	return 1;
}

inline int g5x5Test()
{
	return 1;
}

inline int g6x6Test()
{
	return 1;
}

inline int g1x2Test()
{
	return 1;
}

inline int g2x3Test()
{
	return 1;
}

inline int g3x2Test()
{
	return 1;
}

inline int g3x4Test()
{
	return 1;
}

inline int g3x5Test()
{
	return 1;
}

inline int g2x4Test()
{
	return 1;
}

inline int clear6x6test()
{
	//fill a row
	//use the clear command
	//verify all lanes not blocked
	//repeat for all rows
	//repeat for all cols
	return 1;
}

inline int twoCarsOneBlockTest()
{
	//verify two cars can be added to a single block (a forward and a rear)
	return 1;
}

inline int blockOverlapTest()
{
	//add a car that spans accross two blocks
	//verify both lanes blocked
	return 1;
}

inline int accelerationTest()
{
	//position an oncomming car such that acceleration is possible
	return 1;
}

inline int decelerationTest()
{
	//position an oncomming car so that deceleration is necesary
	return 1;
}

inline int yieldTest()
{
	//test yeild detection
	return 1;
}
