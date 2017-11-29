#ifndef SRC_DJTRAFFICLIGHT_MANAGER_H_
#define SRC_DJTRAFFICLIGHT_MANAGER_H_

typedef enum {

}
class DJTrafficLightManager
{
public:
    // all possibilities of a state for a light
    #define RED = 1;
    #define YELLOW = 2;
    #define GREEN = 4;
    #define LEFT_GREEN = 8;
    #define BOTH_GREEN = 12;
    #define LEFT_BLINK_YELLOW = 16;
    // all possibilities of a type of light
    #define NORMAL_LIGHT = 1;
    #define LEFT_TURN_ONLY_LIGHT = 2;
    #define LEFT_AND_NORMAL_LIGHT = 3;
    // set default timings of lights (In seconds)
    #define DEFAULT_CYCLE_TIME = 60; // 1 min
    #define DEFAULT_RED_TIME = 29;
    #define DEFAULT_YELLOW_TIME = 2; 
    #define DEFAULT_GREEN_TIME = 29; 
    #define DEFAULT_LEFT_GREEN_TIME = 15; // .5 second under half total cycle of normal green/yellow 
    #define DEFAULT_LEFT_BLINK_YELLOW_TIME = 16; // .5 second over half total cycle of normal green/yellow

 
    DJTrafficLightManager(int laneNum, int dirNum);

    void initAllLights(int numLanes, int direction);
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
    void initStateTable(int numLanes, int direction);
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
    int lightArray[4][6];
    int masterStateTable[4][6];     
};

#endif SRC_DJTRAFFICLIGHT_MANAGER_H_