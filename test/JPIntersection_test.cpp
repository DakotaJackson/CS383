/*
 * JPIntersection_test.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: james
 */
#include "../inc/JPIntersectionExceptions.h"
#include "../inc/JPIntersection.h"
#include "../inc/JPConstants.h"
#include "../inc/JPLane.h"

#define JPEXCEPTION_REPLACE_ME JPMalformedIntersectionException

//checks of constants
int directionIterationCheck();
int directionOppositeCheck();
int directionAndBoundOppositeCheck();

//error checks
int addingAfterFinalizedCheck();
int multipleIntersectionCheck();
int laneCollidesWithOncomingLaneCheck();
int twoLanesTurningToOneCheck();
int laneOffsetMismatchCheck();
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
				laneOffsetMismatchCheck() );

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
				"JPIntersection: Missing Lanes Error",
				multipleIntersectionCheck() );

	ret = consts::testOuptut(
				"JPIntersection: Adding After Finalized Error",
				addingAfterFinalizedCheck() );

	//this method verifies that lanes are correctly added and retrieved
	ret = consts::testOuptut(
				"JPIntersection: Adding Lanes Test",
				addLanesCheck() );
	//make sure the getters and setters work properly
	ret = consts::testOuptut(
				"JPIntersection: Getters and Setters Test",
				gettersAndSettersTest() );
printf("%d\n",ret);

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

inline int addingAfterFinalizedCheck()
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

inline int multipleIntersectionCheck()
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

inline int laneCollidesWithOncomingLaneCheck()
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

inline int twoLanesTurningToOneCheck()
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

inline int laneOffsetMismatchCheck()
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

inline int directionOutOfBoundsCheck()
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
			lanes[i]->addCarAtEnd(new SFCar);
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
	inter.setTrackedLaneLength(JPIntersection::NORTH, 149);
	inter.setTrackedLaneLength(JPIntersection::SOUTH, 1 + JPIntersection::MAX_LANE_LENG);
	if(149 == inter.getTrackedLaneLength(JPIntersection::NORTH) ) return 21;
	if(1 + JPIntersection::MAX_LANE_LENG == inter.getTrackedLaneLength(JPIntersection::SOUTH) ) return 22;

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
