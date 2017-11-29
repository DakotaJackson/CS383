/*
 * IntersectionGrid_test.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: james
 */

#include "../inc/JPIntersectionGrid.h"
#include "../inc/JPConstants.h"
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
	ret = consts::testOuptut("Intersection Grid: 1x1 Grid Test", g1x1Test() );
	ret = consts::testOuptut("Intersection Grid: 2x2 Grid Test", g2x2Test() );
	ret = consts::testOuptut("Intersection Grid: 3x3 Grid Test", g3x3Test() );
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

inline int g3x3Test()
{
	return 1;
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
