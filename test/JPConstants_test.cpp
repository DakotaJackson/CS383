//DEPRECATED
#include "JPConstants.h"

#include <stdio.h>

int lightColorsBitFieldCheck();

//int testReportOuptut(char *name, int testStatus);
/**
 * \brief Main function to test assertions of the constants file.
 *
 * The constants file makes several guarantees that must be upheld for the program to work properly.
 * The following assertions are tested.
*/

int main()
{
	return 0;
}


/**
 * \brief Verify a separate bit is used for each light color.
 *
 * Because of 5 lamp lights, the traffic light permits multiple
 * simultaneous outputs.
 *  Using a bit field to specify
 * directions requires that each constant occupy a separate bit.
 * To verify this, a cumulative field is used. It is initialized to
 * one of the constants. A bit is new if and only if or-ing it with
 * the field is different. This check is performed for each successive
 * constant in the set, then that constant is added to the field.
 */
int lightColorsBitFieldCheck()
{
	/*
	int sumField = consts::RED;

	//check against Green
	if( (sumField | consts::GREEN) == sumField)
		return 1;
	sumField += consts::GREEN;

	//check against YELLOW
	if( (sumField | consts::YELLOW) == sumField)
		return 1;
	sumField += consts::YELLOW;

	//check against LEFT_GREEN
	if( (sumField | consts::LEFT_GREEN) == sumField)
		return 1;
	sumField += consts::LEFT_GREEN;

	//check against LEFT_BLINK_YELLOW
	if( (sumField | consts::LEFT_BLINK_YELLOW) == sumField)
		return 1;
	sumField += consts::LEFT_BLINK_YELLOW;


	//check against LEFT_BLINK_YELLOW
	if( (sumField | consts::LEFT_SOLID_YELLOW) == sumField)
		return 1;

	return 0;
	*/
}
