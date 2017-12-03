/*
 * DJTrafficLightManager.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: dakota
 */

 #include "../../inc/JPConstants.h"
 #include "../../inc/DJTrafficLightManager.h"

DJTrafficLightManager::DJTrafficLightManager()
{
    _state = 0;
    _cycleTime = DEFAULT_CYCLE_TIME; //CHANGE HOW THIS IS POPULATED
    // 4 = total possible directions, 6 = max number lanes
    // directions: north = 0, east = 1, south = 2, west = 3
    _lightArray[4][6];
    _masterStateTable[4][6];
    _stateTimeTable[24];
    /* IMPORT TIMINGS FROM UI SETUP
    _redTime = ;
    _yellowTime = ;
    _greenTime = ;
    _leftGreenTime = ;
    _leftCautionTime = ;
    _leftYieldTime = ;
    _lgreenSgreenTime = ;
    _lyellowSgreenTime = ;*/
    // include way to get total number of lights, rate of time,
    // state and manage/update from there. May use 2D array for light sorting?
}

void DJTrafficLightManager::initAllLights(int numLanes, int direction)
{   
    // (MAY NEED TO DEFINE THIS WITH USER SPEC VAR)
    // make complete 4x6 map to populate state table on and compare with
    for(int i=0;i<6;i++) {
        // 0 is always left lane, no matter direction
        if (i==0 || i==1){
            // with 4+ lanes, 2 left turns will be needed (normal and only left)
            if (numLanes > 4 && i==1) {
                _lightArray[direction][i] = LEFT_AND_NORMAL_LIGHT; 
            } else {
                _lightArray[direction][i] = LEFT_TURN_ONLY_LIGHT;
            }
        }
        // otherwise light is normal and populated in map
        else if (i<numLanes){
            _lightArray[direction][i] = NORMAL_LIGHT;
        }
        // if no light is there, populate map with a 0
        else if (i>=numLanes){
            _lightArray[direction][i] = 0;
        }
    }
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
    
    //TODO: alter how this is called later on
    initStateTables();
}

void DJTrafficLightManager::initStateTables()
{
    //int _masterStateTable [4][6];
    //int _stateTimeTable [24];
    // incrementing through 2D map generated in initAllLights function
    // and through _stateTimeTable
    // both keep track of necessary info to determine state 
    double time = 0;
    double timeRate = 1;
    int lightPosition = 0; 
    for(int i=0;i<4;i++) {
        for(int j=0;j<6;j++) {
            if(_lightArray[i][j] != 0) {
                // north and south only to green straight (with no left turn)
                if (i == 0 || i == 2) {
                    if (_lightArray[i][j] == NORMAL_LIGHT) {
                        _masterStateTable[i][j] = GREEN;
                        _stateTimeTable[lightPosition] = DEFAULT_RED_TIME + DEFAULT_YELLOW_TIME;
                    } else {
                        _masterStateTable[i][j] = RED;
                        _stateTimeTable[lightPosition] = DEFAULT_RED_TIME;
                    }
                }
                // set all other directions/lights to red (if set up)
                _masterStateTable[i][j] = RED;
                _stateTimeTable[lightPosition] = DEFAULT_RED_TIME;

            } else {
                _masterStateTable[i][j] = 0;
                _stateTimeTable[lightPosition] = -1;
            }
            lightPosition++;
        }
    }
    // initializes the state tables for the lights to be used
    // to calculate states of individual traffic lights.
    // made with regards to user input from initAllLights
}

int DJTrafficLightManager::getSingleLight(int direction, int lane)
{   
    // light pos is the number (counting from top left to bottom right)
    int lightPos=0;
    for(int i=0;i<4;i++) {
        for(int j=0;j<6;j++) {
            if(i == direction && j == lane){
                if (_lightArray[i][j] == 0) {
                    return -1;
                } else {
                    return lightPos;
                }
            } else {
                lightPos++;
            }
        }
    }
    // get the specific light located at the position
    // given by both direction and lane
    // return light;
    // TODO: change from void function to different type w/lights(int per light?)
    return -1;
}

int DJTrafficLightManager::getState(int direction, int lane, double time, double timeRate)
{
    int singleLight = getSingleLight(direction, lane);
    if (singleLight == -1) {
        //ERRRORRR
    } else {
        // ensures current cycle time is correct
        double cycleTime = getCycleTime(time, timeRate);
        // gets relative time in the cycle
        double relativeCycleTime = time%cycleTime;
        int currState = findLightInStateTable(singleLight);
        int currLightType = findLightTypeInLightArray(singleLight);
        if (currState == -2 || currLightType == -2) {
            //ERRRORRR
        } else {
            // different sets of rules for different types of lights
            // new state found by calculation, then the time current time in state
            // of that light is updated (in each calculate function),
            // to reflect the change in time. Llastly, the newly found
            // state is returned to the caller (can be same as before)
            if (currLightType == NORMAL_LIGHT) {
                int newNormState = calculateNormalLightState(singleLight, relativeCycleTime, cycleTime);
                return newNormState;
            }
            if (currLightType == LEFT_TURN_ONLY_LIGHT) {
                int newLTurnState = calculateLeftTurnOnlyLightState(singleLight, relativeCycleTime, cycleTime);
                return newLTurnState;
            }
            if (currLightType == LEFT_AND_NORMAL_LIGHT) {
                int newLandNormState = calculateLeftAndNormLightState(singleLight, relativeCycleTime, cycleTime);
                return newLandNormState;
            }
        }
    }

    // takes the given light and finds its state given the
    // time and timeRate, using a calculation
    // return state (bitfield combo for given light)
    // light constants in JPConstants.h
    // TODO: define exact equation for this
    return 0;
}

int DJTrafficLightManager::findLightInStateTable(int singleLight)
{
    int statePos = 0;
    for (int i=0;i<4;i++) {
        for (int j=0;j<6;j++) {
            if (statePos == singleLight) {
                return _masterStateTable[i][j];
            } else {
                statePos++;
            }
        }
    }
    // to catch error
    return -2;
}

int DJTrafficLightManager::findLightTypeInLightArray(int singleLight)
{
    int currLightPos = 0;
    for (int i=0;i<4;i++) {
        for (int j=0;j<6;j++) {
            if (currLightPos == singleLight) {
                return _lightArray[i][j];
            } else {
                currLightPos++;
            }
        }
    }
    // to catch error
    return -2;
}
int DJTrafficLightManager::calculateNormalLightState(int singleLight, double relativeCycleTime, double cycleTime)
{
    int foundState = 0;
    double currTimeInCycle = _stateTimeTable[singleLight];
    double newTimeInCycle = (currTimeInCycle + relativeCycleTime)%cycleTime;
    // normal default red
    if (newTimeInCycle >= 0.0 && newTimeInCycle < DEFAULT_RED_TIME) {
        foundState = RED;
    }
    // normal default yellow
    if (newTimeInCycle >= DEFAULT_RED_TIME && newTimeInCycle < DEFAULT_RED_TIME+DEFAULT_YELLOW_TIME){
        foundState = YELLOW;
    }
    // normal default green
    if (newTimeInCycle >= DEFAULT_RED_TIME+DEFAULT_YELLOW_TIME && newTimeInCycle < cycleTime){
        foundState = GREEN;
    }
    if (foundState == 0) {
        return -1;
    } else {
        updateState(singleLight, newTimeInCycle);
        return foundState;
    }
}
int DJTrafficLightManager::calculateLeftTurnOnlyLightState(int singleLight, double relativeCycleTime, double cycleTime)
{
    int foundState = 0;
    double currTimeInCycle = _stateTimeTable[singleLight];
    double newTimeInCycle = (currTimeInCycle + relativeCycleTime)%cycleTime;
    // normal case (other lane stopped, will have green arrow)
    if (newTimeInCycle >= 0.0 && newTimeInCycle < DEFAULT_RED_TIME) {
        foundState = RED;
    }
    if (newTimeInCycle >= DEFAULT_RED_TIME && newTimeInCycle < DEFAULT_RED_TIME+DEFAULT_LEFT_CAUTION_TIME){
        foundState = LEFT_CAUTION;
    }
    if  (newTimeInCycle >= DEFAULT_RED_TIME+DEFAULT_LEFT_CAUTION_TIME && newTimeInCycle < cycleTime){
        foundState = LEFT_GREEN;
    }
    // need to check for case where 2 left turns blinking yellow (not default)
    // if other side has blinking yellow and [other condition], then proceed
    // WILLBE: foundState = LEFT_YIELD
    
    if (foundState == 0) {
        return -1;
    } else {
        updateState(singleLight, newTimeInCycle);
        return foundState;
    }
}
int DJTrafficLightManager::calculateLeftAndNormLightState(int singleLight, double relativeCycleTime, double cycleTime)
{
    int foundState = 0;
    double currTimeInCycle = _stateTimeTable[singleLight];
    double newTimeInCycle = (currTimeInCycle + relativeCycleTime)%cycleTime;
    if (newTimeInCycle >= 0.0 && newTimeInCycle < DEFAULT_RED_TIME) {
        foundState = RED;
    }
    if (newTimeInCycle >= DEFAULT_RED_TIME && newTimeInCycle < DEFAULT_RED_TIME+DEFAULT_YELLOW_TIME){
        foundState = YELLOW;
    }
    if  (newTimeInCycle >= DEFAULT_RED_TIME+DEFAULT_YELLOW_TIME && newTimeInCycle < cycleTime){
        if (newTimeInCycle < DEFAULT_RED_TIME+DEFAULT_YELLOW_TIME+DEFAULT_LGREEN_SGREEN_TIME){
            foundState = GREEN + LEFT_GREEN; // = LEFTBLINKSOLIDGREEN
        } else {
            foundState = GREEN + LEFT_CAUTION; // = LEFTBLINKSOLIDGREEN
        }
    }
    // must ensure that when using a blink or solid green
    // that the other lane must be red (maybe use a check for it?)
    if (foundState == 0) {
        return -1;
    } else {
        updateState(singleLight, newTimeInCycle);
        return foundState;
    }

}

double DJTrafficLightManager::getCycleTime(double time, double timeRate)
{
    // Time rate will usually be between 0 and 1, which will lengthen the
    //  cycle time proportionally to how slow the sim is going
    double cycleTime = DEFAULT_CYCLE_TIME/timeRate;
    // Returns 60 seconds for default *CHANGE LATER*
    return DEFAULT_CYCLE_TIME;
    // take user-defined cycle time (time for a complete cycle through the light)
}

void DJTrafficLightManager::updateState(int singleLight, double newTimeInCycle)
{
    _stateTimeTable[singleLight] = newTimeInCycle;
    // keeps track of and updates each light
    // does not return anything, but is vital to
    // manage the states and ensure no lights have
    // incorrect states, will return errCode of 0=good or 1-4=bad.
}

int DJTrafficLightManager::checkForBadState() 
{
    // take all state table arrays and loop through, checking for
    // all possible errors. Then calls the recoverFromBadState function
    // with the error code
}

void DJTrafficLightManager::recoverFromBadState(int errCode)
{
    // takes in the error code from a bad state,
    // will update state as needed to reflect a good change
    // based on conditions externally set
}

// FOR TESTING
void DJTrafficLightManager::setState(int singleLight, int tState)
{
    // for testing, allows a light state to be set to anything
    // useful when testing checkForBadState function, will do nothing
    // until that is set up
}
DJTrafficLightManager::~DJTrafficLightManager()
{
    // handle destructor
}