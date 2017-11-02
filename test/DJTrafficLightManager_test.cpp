/*
 * DJTrafficLightManager_test.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: dakota
 */

#include "../inc/DJTrafficLightManager.h"
#include "../inc/JPConstants.h"
#include "../inc/JPLane.h"
#include <stdio.h>

// TODO write tests && include/import ...manager.cpp
int lightPerLaneCheck();
int changeStateSuccessCheck();
int noChangeStateCheck();
int findInvalidStateCheck();
int recoveryFromInvalidStateCheck();
int simTimeSpeedChangeCheck();

int main()
{
    int ret;
    ret = consts::testOutput(
        "DJTrafficLightManager: light per lane check",
        lightPerLaneCheck() );

    ret = consts::testOutput(
        "DJTrafficLightManager: change state success check",
        changeStateSuccessCheck() );
    
    ret = consts::testOutput(
        "DJTrafficLightManager: No change state check",
        nochangeStateCheck() );

    ret = consts::testOuptut(
        "DJTrafficLightManager: No invalid states check",
        noInvalidStateCheck() );
    
    ret = consts::testOuptut(
        "DJTrafficLightManager: Recovery from an invalid state check",
        recoveryFromInvalidStateCheck() );
    
    ret = consts::testOutput(
        "DJTrafficLightManager: Simulation time speed change check",
        simTimeSpeedChangeCheck() );
    
    
    // call each function with an expected pass/fail and check for 
    // expected results, using the testOutput function from the JPConstants.h file
    return 0;
}

/**
 * \brief Verify that each lane has a light for each direction.
 */
int lightPerLaneCheck()
{
    // make an arbitrary number of lanes less than the maximum
    // call the function to init them all
    // check that each lane has a light set up per direction
    int tResult = 0;
    int numLanes = 4;
    initAllLights(numLanes)
    for(int i=0; i<numLanes; i++) {
        // each of these t cases tests a direction
        // 2 for any lane shoud be populated
        int t1 = getSingleLight(0, i);
        int t2 = getSingleLight(1, i);
        int t3 = getSingleLight(2, i);
        int t4 = getSingleLight(3, i);
        
        // check for opposite directions (should have lights on both dir)
        if (((t1+t3) >= 0) || ((t2+t4) >= 0)) {
            tResult = 0;
        } else {
            tResult = -1;
        }

    }
    return tResult;
}

/**
 * \brief Verify that the proper response is given for a state-change.
 */
int changeStateSuccessCheck()
{
    // make a cycle time and state time (arbitrary)
    // get the state, store it, wait an appropriate time
    // get the state again and compare
    // test with cases red -> green -> yellow -> red (etc.)
    int tResult = 0;
    initAllLights(2);
    initStateTable(2);
    double time = 0;
    double timeRate = 1;
    int currState = getState(1, time, timeRate);
    int changeState = getState(1, time+10, timeRate);

    if (currState == changeState) {
        tResult = -1;
    }

    return tResult;
}

/**
 * \brief Verify that the proper response is given for a non-change.
 */
int noChangeStateCheck()
{
    // make a cycle time and state time (arbitrary)
    // get the state, store it, wait an appropriate time
    // get the state again and compare, check for no change
    int tResult = 0;
    initAllLights(2);
    initStateTable(2);
    double time = 0;
    double timeRate = 1;
    // there will be a single light at pos 1
    int currState = getState(1, time, timeRate);
    int changeState = getState(1, time+0.1, timeRate);

    if (currState != changeState) {
        tResult = -1;
    }
    
    return tResult;
}

/**
 * \brief Verify that each light won't conflict with another for each direction.
 */
int findInvalidStateCheck()
{   
    // get the state of each light at an intersection
    // check for the following rules
    // 1.no two green lights at right angles
    // 2.no turn left green with green in exact opposite direction
    // 3.no two red lights at right angles(for more than a brief instant)
    // 4.no solid green with two green arrows
    int tResult = 0;
    int laneNum = 2;
    double dummyTime = 1;
    double dummyTRate = 1;
    initAllLights(2);
    initStateTable(2);
    for(int i=0;i<4;i++) {
        int l1 = getSingleLight(0, i);
        int l2 = getSingleLight(1, i);
        int l3 = getSingleLight(2, i);
        int l4 = getSingleLight(3, i);
        // to test all 4 cases:
        for(int j=0;j<=4;j++) {
            int s1 = getState(l1, dummyTime, dummyTRate);
            int s2 = getState(l2, dummyTime, dummyTRate);
            int s3 = getState(l3, dummyTime, dummyTRate);
            int s4 = getState(l4, dummyTime, dummyTRate);
            // 2 green light case
            if (j == 0){

                int badState = GREEN;
                setState(l1, GREEN)
                setState(l2, badState);
                setState(l3, badState);
                int errCode = manageState(l1, dummyTime, dummyTRate);
                // handle output of what manage state returns
                if (errCode != 1) {
                    tResult = -1;
                    return tResult;
                } else {
                    tResult = 0;
                    setState(l1, s1);
                    setState(l2, s2);
                    setState(l3, s3);
                }
            }
            // left turn green case
            if (j == 1) {
                int badState = LEFT_GREEN;
                setState(l1, LEFT_GREEN);
                setState(l2, badState);
                setState(l3, badState);
                int errCode = manageState(l1, dummyTime, dummyTRate);
                if (errCode != 2) {
                    tResult = -1;
                    return tResult;
                } else {
                    tResult = 0;
                    setState(l1, s1);
                    setState(l2, s2);
                    setState(l3, s3);
                }
            }
            // 2 red light case
            if (j == 2) {
                int badState = RED;
                setState(l1, RED);
                setState(l2, badState);
                setState(l3, badState);
                int errCode = manageState(l1, dummyTime, dummyTRate);
                if (errCode != 3) {
                    tResult = -1;
                    return tResult;
                } else {
                    tResult = 0;
                    setState(l1, s1);
                    setState(l2, s2);
                    setState(l3, s3);
                }
            }
            // 2 green arrow with solid green case
            if (j == 3) {
                int badState = GREEN;
                setState(l1, LEFT_GREEN);
                setState(l2, badState);
                setState(l3, LEFT_GREEN);
                int errCode = manageState(l1, dummyTime, dummyTRate);
                if (errCode != 4) {
                    tResult = -1;
                    return tResult;
                } else {
                    tResult = 0;
                    setState(l1, s1);
                    setState(l2, s2);
                    setState(l3, s3);
                }
            }
            // all states good check
            if (j == 4) {
                int errCode1 = manageState(l1, dummyTime, dummyTRate);
                int errCode2 = manageState(l2, dummyTime, dummyTRate);
                int errCode3 = manageState(l3, dummyTime, dummyTRate);
                int errCode4 = manageState(l4, dummyTime, dummyTRate);
                int errCodeTotal = errCode1+errCode2+errCode3+errCode4;
                if (errCodeTotal != 0) {
                    // will return different error type on different fail type
                    tResult = 1;
                    return tResult;
                } else {
                    tResult = 0;
                }
            }
        } // end 'j' for loop
    } // end 'i' for loop

    return tResult;
}

/**
 * \brief Verify that system can recover from an invalid state.
 */
int recoveryFromInvalidStateCheck()
{
    // pretend the check for invalid state function returns an invalid state
    // go through and identify the problem (w/function error code)
    // fix in one of 4 ways (will solve problems from noInvalidStateCheck function)
    int tResult = 0;
    double dummyTime = 1;
    double dummyTRate = 1;
    int errCode = 0;
    for(int i=1;i<4;i++){
       recoverFromBadState(i);
       errCode = manageState(1, dummyTime, dummyTRate); 
       if (errCode != 0) {
           tResult = -1;
           return tResult;
       }
    }
    return tResult;
}

/**
 * \brief Verify that changing rate of time will correctly change cycle times.
 */
int simTimeSpeedChangeCheck()
{   
    // get two different multiples of the time speed, state time, and cycle time
    // check what is returned from each getCycleTime() call and
    // calculate to a proportionate scale of each other
    int tResult = 0;
    double simTime = 1;
    double timeRateInit = 1.0;
    double timeRateChange = 0.5;
    int t1 = getCycleTime(simTime, timeRateInit);
    int t2 = getCycleTime(simTime, timeRateChange);
    // fail to update time correctly (computation err?) tResult 1, diff message than below
    if (t1/2 != t2) {
        tResult = 1;
    }
    // hard fail (no update) returns -1 overriding old tResult
    if (t1 >= t2) {
        tResult = -1;
    }
    return tResult;
}