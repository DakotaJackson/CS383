#ifndef TRAFFIC_CONSTANTS_HEADER
#define TRAFFIC_CONSTANTS_HEADER
#include <stdio.h>
#include <cmath>

/**
 *  \brief Originally meant to be a holder for constants used to communicate between classes/modules.
 *  This caused confusion and constants have (mostly?) migrated to members of their applicable class.
 *  Now it serves as a holder for some useful functions for testing that I felt the rest of the group
 *  might want to use.
 *
 */
namespace consts
{
	//NORTH(BOUND), SOUTH(BOUND), etc have been moved to class JPIntersection

	//These could be taken over by Samantha or I could retain them as members of
	//the SimEngine Class. Their actual values don't matter as long as they are unique.
	//However they may be useful for animating blinkers or something.
	const int DESIRE_STRAIGHT = 1;
	const int DESIRE_RIGHT = 2;
	const int DESIRE_LEFT = 4;

	//Traffic light colors have been taken over by Dakota. Or not? Temporarily back here.
	/** The light is red */
	const int RED = 1;
	/** The light is yellow */
	const int YELLOW = 2;
	/** The light is green */
	const int GREEN = 4;
	/** The left arrow is green */
	const int LEFT_GREEN = 8;
	/** The left arrow is flashing yellow */
	const int LEFT_YIELD = 16;
	/** The left arrow is solid yellow */
	const int LEFT_CAUTION = 32;

	/**
	 * \brief a simple portable test report function.
	 *
	 * \param name The name or description of the test.
	 * \param testFailed Zero for pass non zero for failure
	 * \return Returns the value of testPassed for easy use inline.
	 */
	inline int testOuptut(const char *name, const int testFailed)
	{
		// "\033[32mtext[\033[0m" change 32 to 31 for red. Not working on MSYS
		if(-1 == testFailed)
			printf("    %-65s[xFail ]\n", name);
		else if(0 == testFailed)
			printf("    %-65s[Passed]\n", name);
		else
			printf("    %-65s[Failed]\n", name);
		return testFailed;
	}

	/**
	 * \brief Compare near equality for doubles
	 */
	inline bool deq(double d1, double d2)
	{
		//prevent spurious failures when one is exactly 0 and the other is not
		if( std::abs(d1) < 0.00000001 && std::abs(d2) < 0.00000001 )
			return true;

		double avg = (d1+d2)/2;
		double dif = std::abs(d1-d2);
		if( dif/avg < 0.00001)
			return true;
		else
			return false;
	}

	/**
	 * \brief Return the percent error.
	 *
	 * \return The error as a percent (i.e. upto 100.0)
	 */
	inline double percentError(double target, double measured )
	{
		double error = (target - measured)/target;
		return std::abs(100.0 * error );
	}

	inline double computeStdDev(double vals[], double mean, int numVals)
	{
		double sum = 0;
		int i;
		//printf("Mean: %f\n", mean);
		for(i = 0; i < numVals; i++)
		{
			//printf("[%d]: %f\t %f\n", i, vals[i], pow(vals[i] - mean, 2));
			sum += pow(vals[i] - mean, 2);
		}
		double dev = sqrt( sum / (numVals-1));
		//printf("\t%f\n", dev * dev);
		return dev;
	}
}
#endif
