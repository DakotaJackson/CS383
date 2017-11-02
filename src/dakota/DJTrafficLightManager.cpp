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
    // include way to get total number of lights, rate of time,
    // state and manage/update from there. May use 2D array for light sorting?
}

void DJTrafficLightManager::initAllLights(int numLanes)
{
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
}

void DJTrafficLightManager::initStateTable(int numLanes)
{
    // initializes the state table for the lights to be used
    // to calculate states of individual traffic lights.
    // made with regards to user input from initAllLights
}

int DJTrafficLightManager::getSingleLight(int direction, int lane)
{
    // get the specific light located at the position
    // given by both direction and lane
    // return light;
    // TODO: change from void function to different type w/lights(int per light?)
    return 0;
}

int DJTrafficLightManager::getState(int singleLight, double time, double timeRate)
{
    // takes the given light and finds its state given the
    // time and timeRate, using a calculation
    // return state (bitfield combo for given light)
    // light constants in JPConstants.h
    // TODO: define exact equation for this
    return 0;
}

double DJTrafficLightManager::getCycleTime(double time, double timeRate)
{
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