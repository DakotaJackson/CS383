#ifndef SRC_DJTRAFFICLIGHT_MANAGER_H_
#define SRC_DJTRAFFICLIGHT_MANAGER_H_

class DJTrafficLightManager
{
public:
    DJTrafficLightManager(int laneNum, int dirNum);

    void initAllLights(int numLanes);
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
    void initStateTable(int numLanes);
    // initializes the state table for the lights to be used
    // to calculate states of individual traffic lights.
    // made with regards to user input from initAllLights
    void getSingleLight(int direction, int lane, double time);
    // get the specific light located at the position
    // given by both direction and lane
    // return light;
    // TODO: change from void function to different type w/lights(int per light?)
    int getState(int singleLight, double time, double timeRate);
    // takes the given light and finds its state given the
    // time and timeRate, using a calculation
    // return state (bitfield combo for given light)
    // light constants in JPConstants.h
    // TODO: define exact equation for this
    double getCycleTime(double time, double timeRate);
    // take user-defined cycle time (time for a complete cycle through the light)
    // and modulus it (tentatively) by timeRate 
    // TODO: define exact equation for this
    // return cycleTime(double)
    int manageState(int singleLight, double time, double timeRate);  
    // keeps track of and updates each light
    // does not return anything, but is vital to
    // manage the states and ensure no lights have
    // incorrect states.
    void recoverFromBadState(int errCode);
    // takes in the traffic light with a bad state
    // will update it's state to reflect a good change
    // based on conditions externally set
    void setState(int singleLight, int tState);
    // for testing, allows a light state to be set to anything
    // useful when testing manageState function, will do nothing
    // until that is set up

private:
    int state;
    int duration;
    double stateTime;
};

#endif SRC_DJTRAFFICLIGHT_MANAGER_H_