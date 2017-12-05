/*
 * JPIntersection_test.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: james
 */
#include "JPIntersectionExceptions.h"
#include "JPIntersection.h"
#include "JPConstants.h"
#include "JPLane.h"

#define JPEXCEPTION_REPLACE_ME JPMalformedIntersectionException

//checks of constants
int directionIterationCheck();
int directionOppositeCheck();
int directionAndBoundOppositeCheck();

//error checks
int addingConfigOrderCheck();
int laneCollidesWithOncomingLaneCheck();
int twoLanesTurningToOneCheck();
int laneOffsetCheck();
int turningLaneCrossingStraightLaneCheck();
int laneNumberOutOfBoundsCheck();
int directionOutOfBoundsCheck();
int addingAfterFinalized();


//functionality
int addLanesCheck();
int gettersAndSettersTest();
int main()
{
	int ret = 0;

	//the following functions verify the constants are setup correctly
	ret = consts::testOuptut(
			"JPIntersection: constants: Direction Iteration Check",
			directionIterationCheck());

	ret = consts::testOuptut(
			"JPIntersection: constants: Direction Opposite Check",
			directionOppositeCheck());

	ret = consts::testOuptut(
			"JPIntersection: constants: Direction And Bound Opposite Check",
			directionAndBoundOppositeCheck());

	//the following functions test to make sure exceptions are thrown when they shoudl be
	ret = consts::testOuptut(
			"JPIntersection: Lane Collides With Oncoming Lane Error",
			laneCollidesWithOncomingLaneCheck() );

	ret = consts::testOuptut(
			"JPIntersection: Two Lanes Turning to One Error",
			twoLanesTurningToOneCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Lane Offset Mismatch Error",
				laneOffsetCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Turning Lane Crossing Straight Lane Error",
				turningLaneCrossingStraightLaneCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Lane Number Out of Bounds Error",
				laneNumberOutOfBoundsCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Lane Direction Out of Bounds Error",
				directionOutOfBoundsCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Configuration Order Errors",
				addingConfigOrderCheck() );
	//this method verifies that lanes are correctly added and retrieved
	ret = consts::testOuptut(
				"JPIntersection: Adding Lanes Test",
				addLanesCheck() );
	//make sure the getters and setters work properly
	ret = consts::testOuptut(
				"JPIntersection: Getters and Setters Test",
				gettersAndSettersTest() );

	//	printf("%d\n", ret);
	/*blank
	ret = consts::testOuptut(
			"JPSimulationEngine: ",
			);
*/

	if( 100 == ret ) { printf("This is just here to suppress non-use warnings"); }
	return 0;
}

/**
 * Verify that all directions can be iterated over.
 */
int directionIterationCheck()
{
	//flags that make sure each one was hit
	bool northMet = 0;
	bool southMet = 0;
	bool eastMet = 0;
	bool westMet = 0;

	int i;
	int previous = -5;
	//iterate over over the directions
	for(i =0; i < 4; i++)
	{
		//ensure each directions previous is correct
		//and flag that each direction is met
		if(JPIntersection::NORTH == i)
		{
			northMet = 1;
			if( previous != -5 && previous != JPIntersection::WEST)
				return 1;
			previous = i;
		}
		else if(JPIntersection::EAST == i)
		{
			eastMet = 1;
			if( previous != -5 && previous != JPIntersection::NORTH)
				return 1;
			previous = i;
		}
		else if(JPIntersection::SOUTH == i)
		{
			southMet = 1;
			if( previous != -5 && previous != JPIntersection::EAST)
				return 1;
			previous = i;
		}
		else if(JPIntersection::WEST == i)
		{
			westMet = 1;
			if( previous != -5 && previous != JPIntersection::SOUTH)
				return 1;
			previous = i;
		}
	}

	if(! (northMet && southMet && eastMet && westMet) )
		return 1;

	return 0;
}

/**
 * \brief Verify that (direction + 2) % 4 yields the opposite direction.
 */
int directionOppositeCheck()
{
	//printf("EASTBOUND : %d\n",JPIntersection::EASTBOUND );
	//printf("EASTBOUND : %d\n", (JPIntersection::EASTBOUND + 2)%4);
	//printf("WESTBOUND : %d\n",JPIntersection::WESTBOUND);
	if( (JPIntersection::SOUTHBOUND + 2)% 4 != JPIntersection::NORTHBOUND)
		return 1;
	if( (JPIntersection::NORTHBOUND + 2)% 4 != JPIntersection::SOUTHBOUND)
		return 2;
	if( (JPIntersection::EASTBOUND + 2)% 4 != JPIntersection::WESTBOUND)
		return 3;
	if( (JPIntersection::WESTBOUND + 2)% 4 != JPIntersection::EASTBOUND)
		return 4;
	return 0;
}

/**
 * \brief Verify that SOUTHBOUND and NORTH etc are synonyms
 */
int directionAndBoundOppositeCheck()
{
	if(JPIntersection::SOUTHBOUND != JPIntersection::NORTH)
		return 1;
	if(JPIntersection::NORTHBOUND != JPIntersection::SOUTH)
		return 1;
	if(JPIntersection::EASTBOUND != JPIntersection::WEST)
		return 1;
	if(JPIntersection::WESTBOUND != JPIntersection::EAST)
		return 1;
	return 0;
}

/**
 * \brief Verify a separate bit is used for each lane direction.
 *
 * Lanes can permit multiple directions. Using a bit field to specify
 * directions requires that each constant occupy a separate bit.
 * To verify this, a cumulative field is used. It is initialized to
 * one of the constants. A new bit is set if and only if or-ing it with
 * the field is different. This does not ensure that only a new bit was set.
 * To achieve this it is and-ed with the sumfileld, and the result is verfied to be zero.
 * This check is performed for each successive
 * constant in the set, then that constant is added to the field.
 */

int addingConfigOrderCheck()
{
	JPIntersection *inter = new JPIntersection();
	//add lanes early
	try
	{
		inter->addLane(JPIntersection::NORTH,0,JPLane::STRAIGHT,0,0);
		printf("Made it here77\n");
		return 1;
	}
	catch(JPConfigurationOrderException &e)
	{
		if(e.getDetail() != JPConfigurationOrderException::CONFIG_LANES_BEFORE_OFFSET)
			return 2;
	}

	//set offset after lanes have been added
	inter->setLaneOffsets(1,1,1,1);
	inter->addLane(JPIntersection::NORTH,0,JPLane::STRAIGHT,0,0);
	try
	{
		inter->setLaneOffset(0,1);
		return 3;
	}
	catch(JPConfigurationOrderException &e)
	{
		if(e.getDetail() != JPConfigurationOrderException::CONFIG_OFFSET_AFTER_LANES)
			return 4;
	}
	try
	{
		inter->setLaneOffsets(1,1,1,1);
		return 5;
	}
	catch(JPConfigurationOrderException &e)
	{
		if(e.getDetail() != JPConfigurationOrderException::CONFIG_OFFSET_AFTER_LANES)
			return 6;
	}

	//test for finalizing with missing lanes
	inter->addLane(JPIntersection::NORTH,1,JPLane::STRAIGHT,0,0);
	inter->addLane(JPIntersection::SOUTH,1,JPLane::STRAIGHT,0,0); //missing lane 0
	inter->addLane(JPIntersection::EAST,0,JPLane::STRAIGHT,0,0);
	inter->addLane(JPIntersection::EAST,1,JPLane::STRAIGHT,0,0);
	inter->addLane(JPIntersection::WEST,0,JPLane::STRAIGHT,0,0);
	inter->addLane(JPIntersection::WEST,1,JPLane::STRAIGHT,0,0);
	try
	{
		inter->finalize();
		return 7;
	}
	catch(JPConfigurationOrderException &e)
	{
		if(e.getDetail() != JPConfigurationOrderException::FINALIZE_MISSING_LANES)
			return 8;
	}

	//test changes after finalized
	inter->addLane(JPIntersection::SOUTH,0,JPLane::STRAIGHT,0,0); //add the missing lane
	inter->finalize();
	try
	{
		inter->addLane(JPIntersection::SOUTH,0,JPLane::STRAIGHT,0,0); //add the missing lane
		return 9;
	}
	catch(JPConfigurationOrderException &e)
	{
		if(e.getDetail() != JPConfigurationOrderException::CONFIG_FINALIZED)
			return 10;
	}

	delete inter;
	return 0;
}


int laneCollidesWithOncomingLaneCheck()
{
	try
	{
		//bad news if you made it here
		return -1;
	}
	catch(JPEXCEPTION_REPLACE_ME & e)
	{
		//some checks on output
		return 0;
	}

}

int twoLanesTurningToOneCheck()
{
	try
	{
		//bad news if you made it here
		return -1;
	}
	catch(JPEXCEPTION_REPLACE_ME & e)
	{
		//some checks on output
		return 0;
	}
}

inline int laneOffsetCheck()
{
	JPIntersection inter;
	int dir;

	//test the direction specific function
	for(dir = 0; dir < 4; dir++)
	{
		try
		{
			inter.setLaneOffset(dir, 0.999);
			return dir;
		}
		catch(JPLaneOffsetException &e){}
	}

	//test each direction in the all directions function
	dir++;
	try
	{
		inter.setLaneOffsets(0.999,1,1,1);
		return dir;
	}
	catch(JPLaneOffsetException &e){}
	dir++;
	try
	{
		inter.setLaneOffsets(1,0.999,1,1);
		return dir;
	}
	catch(JPLaneOffsetException &e){}
	dir++;
	try
	{
		inter.setLaneOffsets(1,1,0.999,1);
		return dir;
	}
	catch(JPLaneOffsetException &e){}
	dir++;
	try
	{
		inter.setLaneOffsets(1,1,1,0.999);
		return dir;
	}
	catch(JPLaneOffsetException &e){}

	//make sure all >=1 does not cause an error
	dir++;
	try
	{
		inter.setLaneOffsets(1,1,1,1);
	}
	catch(JPLaneOffsetException &e)
	{
		return dir;
	}

	return 0;
}

inline int turningLaneCrossingStraightLaneCheck()
{
	try
	{
		//bad news if you made it here
		return -1;
	}
	catch(JPEXCEPTION_REPLACE_ME & e)
	{
		//some checks on output
		return 0;
	}

}

inline int laneNumberOutOfBoundsCheck()
{
	JPIntersection inter;
	inter.setLaneOffsets(2,2,2,2);

	//try adding a lane that's exceeds max lanes
	try
	{
		inter.addLane(JPIntersection::NORTH,JPIntersection::MAX_LANES, JPLane::STRAIGHT, 0, 0);
		return 1;
	}
	catch(JPLaneNumberOutOfBoundsException &e){}

	//try adding a lane less than 0
	try
	{
		inter.addLane(JPIntersection::NORTH,-1, JPLane::STRAIGHT, 0, 0);
		return 2;
	}
	catch(JPLaneNumberOutOfBoundsException &e){}

	//fill up the intersection
	inter.addLane(JPIntersection::NORTH,0, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::NORTH,1, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::SOUTH,0, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::SOUTH,1, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::EAST,0, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::EAST,1, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::WEST,0, JPLane::STRAIGHT, 0, 0);
	inter.addLane(JPIntersection::WEST,1, JPLane::STRAIGHT, 0, 0);
	inter.finalize();

	//try getting a lane above what was added
	try
	{
		inter.getLane(JPIntersection::NORTH, 2);
		return 3;
	}
	catch(JPLaneNumberOutOfBoundsException &e){}

	//try getting a lane less than 0
	try
	{
		inter.getLane(JPIntersection::NORTH, -1);
		return 4;
	}
	catch(JPLaneNumberOutOfBoundsException &e){}

	return 0;
}

/**
 * \brief Direction out of bounds check subfunction.
 *
 * This function verifies the direction out of bounds exception for an individual function passed via a function pointer.
 * \param ret An error code accumulator. This value is automatically incremented to ease tracking down failures.
 * \param jpi The instance of JPIntersection that this will be run on.
 * \param pt2func Function pointer for the particular function.
 */
//the original, different name for copy docs, accepts one int, returns double
int doobPtrCheckBase(int &ret, JPIntersection &jpi, double  (JPIntersection::*pt2func)(int))
 {
	 //attempt with direction of -1
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(-1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(4);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 ret++;
			 (jpi.*pt2func)(dir);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return ret;
		 }
	 }
	 return 0;
 }

/**
 *
 * \copydoc doobPtrCheckBase()
 * \param p1 The double paramer that should be passed to the function.
 */
//accepts double, returns void (used twice)
int doobPtrCheck(int &ret, JPIntersection &jpi, void  (JPIntersection::*pt2func)(int,double), double p1)
 {
	 //attempt with direction of -1
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(-1,p1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(4,p1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 ret++;
			 (jpi.*pt2func)(dir, p1);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return ret;
		 }
	 }
	 return 0;
 }

/**
 *
 * \copydoc doobPtrCheckBase()
 * \param p1 The double paramer that should be passed to the function.
 */
int doobPtrCheck(int &ret, JPIntersection &jpi, JPLane*  (JPIntersection::*pt2func)(int,int), int p1)
 {
	 //attempt with direction of -1
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(-1,p1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(4,p1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 ret++;
			 (jpi.*pt2func)(dir, p1);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return ret;
		 }
	 }
	 return 0;
 }

/**
 *
 * \copydoc doobPtrCheckBase()
 */
int doobPtrCheck(int &ret, JPIntersection &jpi, int  (JPIntersection::*pt2func)(int) )
 {
	 //attempt with direction of -1
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(-1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 ret++;
		 (jpi.*pt2func)(4);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 ret++;
			 (jpi.*pt2func)(dir);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return ret;
		 }
	 }
	 return 0;
 }

/**
 * \brief Direction out of bounds check subfunction.
 *
 * This function verifies the direction out of bounds exception for an individual function passed via a function pointer.
 * \param ret An error code accumulator. This value is automatically incremented to ease tracking down failures.
 * \param pt2func Function pointer for the particular function.
 */
//static function accepts int, returns void. It get's is own doc since it doesn't need an instance
int doobPtrCheck(int &ret, void (*pt2func)(int) )
 {
	 //attempt with direction of -1
	 try
	 {
		 ret++;
		 (*pt2func)(-1);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 ret++;
		 (*pt2func)(4);
		 return ret;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 ret++;
			 (*pt2func)(dir);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return ret;
		 }
	 }
	 return 0;
 }
/**
  * \brief Check each function that accepts a direction to ensure the direction out of bounds is received when and only when it should be.
  *
  * This function calls a group of sub functions each of which accept a pointer to the function they are
  * validating. They also accept an accumulator
  * r for quickly locating the source of failure, the intersection instance, and lastly any parameters that
  * will need to be passed to the function.
  */
int directionOutOfBoundsCheck()
{
	/*
	//int, double:void
	 * setLaneOffset -
	 * setTrackedLaneLength -

	 * //int, int
	 * getLane -
	 *
	 * /int
	 * validateDirection :void -
	 * getLaneCount:int -
	 *
	 * getLaneOffset:double -
	 * getLaneOffsetInFeet -
	 * getSpeedLimits -
	 * getSpeedLimitsInFPS -
	 * getTrackedExitLength -
	 *
	 * individual
	 * addLane
	 */
	JPIntersection inter;
	int r = 0; //error return code

	if( doobPtrCheck(r, &JPIntersection::validateDirection) )
		return r; //1-6

	if( doobPtrCheck(r, inter, &JPIntersection::setLaneOffset, 1.0) )
		return r;//12

	if( doobPtrCheck(r, inter, &JPIntersection::setTrackedLaneLength, 150.0) )
		return r; //18

	if( doobPtrCheckBase(r, inter, &JPIntersection::getLaneOffset) )
		return r; //24

	if( doobPtrCheckBase(r, inter, &JPIntersection::getLaneOffsetInFeet) )
		return r;

	if( doobPtrCheckBase(r, inter, &JPIntersection::getSpeedLimits) )
		return r;

	if( doobPtrCheckBase(r, inter, &JPIntersection::getSpeedLimitsInFPS) )
		return r;

	if( doobPtrCheckBase(r, inter, &JPIntersection::getTrackedExitLength) )
		return r;

	if( doobPtrCheck(r, inter, &JPIntersection::getLaneCount) )
		return r;

	//make sure there are actually lanes defined to return (otherwise get LaneNumberOutofBoundsException)
	inter.addLane(JPIntersection::NORTH, 0, JPLane::STRAIGHT, 0,0); //adding to accommodate getlane
	inter.addLane(JPIntersection::SOUTH, 0, JPLane::STRAIGHT, 0,0); //adding to accommodate getlane
	inter.addLane(JPIntersection::EAST, 0, JPLane::STRAIGHT, 0,0); //adding to accommodate getlane
	inter.addLane(JPIntersection::WEST, 0, JPLane::STRAIGHT, 0,0); //adding to accommodate getlane
	if( doobPtrCheck(r, inter, &JPIntersection::getLane, 0) )
		return r;

	//last but not least, addLane. It's ugly so why bother with pointers.
	 //attempt with direction of -1
	 try
	 {
		 r++;
		 inter.addLane(-1,JPIntersection::NORTH, JPLane::STRAIGHT, 0,0);
		 return r;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //attempt with direction of 4
	 try
	 {
		 r++;
		 inter.addLane(4,JPIntersection::NORTH, JPLane::STRAIGHT, 0,0);
		 return r;
	 }
	 catch(JPDirectionOutOfBoundsException &e) {}

	 //make sure all 4 directions work
	 int dir;
	 for(dir = 0; dir < 4; dir++)
	 {
		 try
		 {
			 r++;
			 inter.addLane(dir,JPIntersection::NORTH, JPLane::STRAIGHT, 0,0);
		 }
		 catch(JPDirectionOutOfBoundsException &e)
		 {
			 return r;
		 }
	 }

	 return 0;
}

inline int addingAfterFinalized()
{
	try
	{
		//bad news if you made it here
		return -1;
	}
	catch(JPEXCEPTION_REPLACE_ME & e)
	{
		//some checks on output
		return 0;
	}
}

inline int addLanesCheck()
{
	int i,j,k;
	int max = JPIntersection::MAX_LANES;
	JPLane **lanes = new JPLane*[max * 4];
	JPIntersection inter = JPIntersection();
	inter.setLaneOffsets(max,max,max,max); //ensure no overlap

	//printf("Assignment\n");
	//assign those 24 lanes to unique positions
	for(i = 0; i < 4; i++)
		for(j = 0; j < JPIntersection::MAX_LANES; j++)
			inter.addLane(i,j,JPLane::STRAIGHT, 0, 0);

	//printf("Retrieval\n");
	//retrieve the 24 lanes
	k = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < JPIntersection::MAX_LANES; j++)
			lanes[k++] = inter.getLane(i,j);

	//printf("Comparison\n");
	//make sure you get back 24 unique addresses
	for(i = 0; i < max * 4; i++)
	{
		//printf("[%d]:\t%d\n", i, lanes[i]);
		for(j = i + 1; j < max * 4; j++)
		{
			if( lanes[j] == lanes[i])
				return 1;

			//attempt to access the object this should cause a
			//segfault if it doesn't point to the right spot
			lanes[i]->addCarAtEnd(new Car);
		}
	}

	//check to make sure the getLaneCount works
	int laneCounts[4];
	inter.getLaneCounts(laneCounts);
	for(i = 0; i < 4; i++)
		if(laneCounts[i] != JPIntersection::MAX_LANES)
		{
			printf("[%d]: %d, %d\n",i, laneCounts[i], inter.getLaneCount(i));
			//return 2;
		}

	return 0;
}

inline int gettersAndSettersTest()
{
	JPIntersection inter = JPIntersection();

	//test set multiple offsets with both gets
	inter.setLaneOffsets(6,5,4,3); //ensure no overlap
	if(6 != inter.getLaneOffset(JPIntersection::NORTH) ) return 1;
	if(5 != inter.getLaneOffset(JPIntersection::SOUTH) ) return 2;
	if(4 != inter.getLaneOffset(JPIntersection::EAST) ) return 3;
	if(3 != inter.getLaneOffset(JPIntersection::WEST) ) return 4;
	if(60 != inter.getLaneOffsetInFeet(JPIntersection::NORTH) ) return 5;
	if(50 != inter.getLaneOffsetInFeet(JPIntersection::SOUTH) ) return 6;
	if(40 != inter.getLaneOffsetInFeet(JPIntersection::EAST) ) return 7;
	if(30 != inter.getLaneOffsetInFeet(JPIntersection::WEST) ) return 8;

	//test individual offsets
	inter.setLaneOffset(JPIntersection::NORTH, 2);
	if(2 != inter.getLaneOffset(JPIntersection::NORTH) ) return 1;
	inter.setLaneOffset(JPIntersection::NORTH, 6);

	inter.setLaneOffset(JPIntersection::SOUTH, 2);
	if(2 != inter.getLaneOffset(JPIntersection::SOUTH) ) return 1;
	inter.setLaneOffset(JPIntersection::SOUTH, 6);

	inter.setLaneOffset(JPIntersection::EAST, 2);
	if(2 != inter.getLaneOffset(JPIntersection::EAST) ) return 1;
	inter.setLaneOffset(JPIntersection::EAST, 6);

	inter.setLaneOffset(JPIntersection::WEST, 2);
	if(2 != inter.getLaneOffset(JPIntersection::WEST) ) return 1;
	inter.setLaneOffset(JPIntersection::WEST, 6);

	//test exit lengths
	//defaults
	if( 600 != inter.getTrackedExitLength(0) ) return 9;
	if( 600 != inter.getTrackedExitLength(1) ) return 10;
	//Manual settings
	inter.setTrackedExitLengths(700, 800);
	if( 700 != inter.getTrackedExitLength(0) ) return 11;
	if( 800 != inter.getTrackedExitLength(1) ) return 12;

	//lane lengths(multi)
	inter.setTrackedLaneLengths(650,550,450,350); //ensure no overlap
	if(650 != inter.getTrackedLaneLength(JPIntersection::NORTH) ) return 13;
	if(550 != inter.getTrackedLaneLength(JPIntersection::SOUTH) ) return 14;
	if(450 != inter.getTrackedLaneLength(JPIntersection::EAST) ) return 15;
	if(350 != inter.getTrackedLaneLength(JPIntersection::WEST) ) return 16;

	//lane lengths individual
	inter.setTrackedLaneLength(JPIntersection::NORTH, 625);
	inter.setTrackedLaneLength(JPIntersection::SOUTH, 525);
	inter.setTrackedLaneLength(JPIntersection::EAST, 425);
	inter.setTrackedLaneLength(JPIntersection::WEST, 325);
	if(625 != inter.getTrackedLaneLength(JPIntersection::NORTH) ) return 17;
	if(525 != inter.getTrackedLaneLength(JPIntersection::SOUTH) ) return 18;
	if(425 != inter.getTrackedLaneLength(JPIntersection::EAST) ) return 19;
	if(325 != inter.getTrackedLaneLength(JPIntersection::WEST) ) return 20;

	//lane length min and max
	inter.setTrackedLaneLength(JPIntersection::NORTH, JPIntersection::MIN_LANE_LENG - 0.1);
	inter.setTrackedLaneLength(JPIntersection::SOUTH, 1 + JPIntersection::MAX_LANE_LENG);
	if(JPIntersection::MIN_LANE_LENG > inter.getTrackedLaneLength(JPIntersection::NORTH) ) return 21;
	if(JPIntersection::MAX_LANE_LENG < inter.getTrackedLaneLength(JPIntersection::SOUTH) ) return 22;

	//speed limits defaults, then sets, then FPS
	if(35 != inter.getSpeedLimits(JPIntersection::NORTH)) return 23;
	if(35 != inter.getSpeedLimits(JPIntersection::EAST)) return 24;
	inter.setSpeedLimits(36,37);
	if(36 != inter.getSpeedLimits(JPIntersection::NORTH)) return 25;
	if(37 != inter.getSpeedLimits(JPIntersection::EAST)) return 26;
	if(36 != inter.getSpeedLimits(JPIntersection::SOUTH)) return 27;
	if(37 != inter.getSpeedLimits(JPIntersection::WEST)) return 28;
	if( ! consts::deq(36*5280.0/3600, inter.getSpeedLimitsInFPS(JPIntersection::NORTH)) ) return 29;

	//printf("SOUTH:%f\n", inter.getSpeedLimits(JPIntersection::NORTH));
	//printf("SOUTH:%f\n", inter.getLaneOffset(JPIntersection::SOUTH));

	return 0;
}
