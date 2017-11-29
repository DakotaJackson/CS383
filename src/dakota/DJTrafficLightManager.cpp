/*
 * DJTrafficLightManager.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: dakota
 */

 #include "../../inc/JPConstants.h"

DJTrafficLightManager::DJTrafficLightManager()
{
    _state = 0;
    // 4 = total possible directions, 6 = max number lanes
    // directions: north = 0, east = 1, south = 2, west = 3
    _lightArray = [4][6];
    _masterStateTable = [4][6];
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
                lightArray[direction][i] = LEFT_AND_NORMAL_LIGHT; 
            } else {
                lightArray[direction][i] = LEFT_TURN_ONLY_LIGHT;
            }
        }
        // otherwise light is normal and populated in map
        else if (i<numLanes){
            lightArray[direction][i] = NORMAL_LIGHT;
        }
        // if no light is there, populate map with a 0
        else if (i>=numLanes){
            lightArray[direction][i] = 0;
        }
    }
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
    
    //TODO: alter how this is called later on
    initStateTable(lightArray);
}

void DJTrafficLightManager::initStateTable(int lightArray[][])
{
    //int masterStateTable [4][6];
    // incrementing through 2D map generated in initAllLights function
    double time = 0;
    double timeRate = 1; 
    for(int i=0;i<4;i++) {
        for(int j=0;j<6;j++) {
            if(lightArray[i][j] != 0) {
                // north and south only to green straight (with no left turn)
                if (i == 0 || i == 2) {
                    if (lightArray[i][j] == NORMAL_LIGHT) {
                        masterStateTable[i][j] = GREEN;
                    } else {
                        masterStateTable[i][j] = RED;
                    }
                }
                // set all other directions/lights to red (if set up)
                masterStateTable[i][j] = RED;
            } else {
                masterStateTable[i][j] = 0;
            }
        }
    }
    // initializes the state table for the lights to be used
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
                return lightPos;
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

int DJTrafficLightManager::getState(int singleLight, double time, double timeRate)
{
    if (singleLight == -1) {
        //ERRRORRR
    } else {
        double cycleTime = getCycleTime(time, timeRate);
    }

    // takes the given light and finds its state given the
    // time and timeRate, using a calculation
    // return state (bitfield combo for given light)
    // light constants in JPConstants.h
    // TODO: define exact equation for this
    return 0;
}

double DJTrafficLightManager::getCycleTime(double time, double timeRate)
{
    double cycleTime = CYCLE_TIME%timeRate;
    // take user-defined cycle time (time for a complete cycle through the light)
    // and modulus it (tentatively) by timeRate 
    // TODO: define exact equation for this
    // return cycleTime(double)
    return 0.0;
}

int DJTrafficLightManager::manageState(int singleLight, double time, double timeRate)
{
    // keeps track of and updates each light
    // does not return anything, but is vital to
    // manage the states and ensure no lights have
    // incorrect states, will return errCode of 0=good or 1-4=bad.
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
    // useful when testing manageState function, will do nothing
    // until that is set up
}
DJTrafficLightManager::~DJTrafficLightManager()
{
    // handle destructor
}