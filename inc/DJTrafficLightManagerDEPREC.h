#ifndef SRC_DJTRAFFICLIGHT_MANAGER_H_
#define SRC_DJTRAFFICLIGHT_MANAGER_H_

class DJTrafficLightManager
{
public:
    int getState(double time, int direction, int lane);
    double getCycleTime();
    // where singleton made, call functions with DJTrafficlightManager::TrafficLights().SomeFunc();
    static DJTrafficLightManager &TrafficLights() {
        // only ran once, makes single instance of traffic lights
        static DJTrafficLightManager *trafficLights = new DJTrafficLightManager;
        return *trafficLights;
    }
private:
    DJTrafficLightManager(){} // default constructor 

    ~DJTrafficLightManager(){} // deconstructor

/*
    // all possibilities of a state for a light (using jpconstants.h)
    //#define RED = 1;
    // #define YELLOW = 2;
    // #define GREEN = 4;
    // #define LEFT_GREEN = 8;
    // ?#define BOTH_GREEN = 12;
    // #define LEFT_BLINK_YELLOW = 16; == LEFT_YIELD
    // all possibilities of a type of light(NOT NEEDED, WILL DELETE LATER)
    static const int NORMAL_LIGHT = 1;
    static const int LEFT_TURN_ONLY_LIGHT = 2;
    static const int LEFT_AND_NORMAL_LIGHT = 3;

    // set default timings of lights (In seconds)
    static const double DEFAULT_CYCLE_TIME = 60.0; // 1 min [following is how seconds are distributed]
    static const double DEFAULT_RED_TIME = 29.0; // 0-28 sec
    static const double DEFAULT_YELLOW_TIME = 2.0; // 29,30 sec
    static const double DEFAULT_GREEN_TIME = 29.0; // 31-59 sec (can't ever be 60sec)
    static const double DEFAULT_LEFT_GREEN_TIME = 29.0; // (31-59 sec)same as normal green timing (aka no changes mid-cycle)
    static const double DEFAULT_LEFT_CAUTION_TIME = 2.0; // (29,30 sec)same as normal yellow timing (aka no changes mid-cycle)
    static const double DEFAULT_LEFT_YIELD_TIME = 31.0; // (29-59 sec)green + yellow (2 lights with 2+/- dir can go left w/neither green)
    static const double DEFAULT_LGREEN_SGREEN_TIME = 14 // (31-44 sec)little less than half default green time = rightofway left and straight 
    static const double DEFAULT_LBLINK_SGREEN_TIME = 15 // (45-59 sec)little more than half default green time = caution left and green straight

    DJTrafficLightManager(int laneNum, int dirNum);

    void initAllLights(int numLanes, int direction);
    // take total number of lines and find a way to 
    // map them on a per-lane/direction basis, along with
    // initializing them with proper values, user config-able
    void initStateTables();
    // initializes the state table for the lights to be used
    // to calculate states of individual traffic lights.
    // made with regards to user input from initAllLights
    void getSingleLight(int direction, int lane);
    // get the specific light located at the position
    // given by both direction and lane
    // return light;
    // TODO: change from void function to different type w/lights(int per light?)
    int getState(int direction, int lane, double time, double timeRate);
    // takes the given light and finds its state given the
    // time and timeRate, using a calculation
    // return state (bitfield combo for given light)
    // light constants in JPConstants.h
    // TODO: define exact equation for this
    int findLightInStateTable(int singleLight);
    // takes numeric value from single light and returns the state 
    // that that position in the state table is at
    int findLightTypeInLightArray(int singleLight);
    // does same as findLightInStateTable, but returns the 
    // type of light rather than the state
    int calculateNormalLightState(int singleLight, double relativeCycleTime, double cycleTime);
    // takes rules of a normal light into consideration
    // when calculating new state
    int calculateLeftTurnOnlyLightState(int singleLight, double relativeCycleTime, double cycleTime);
    // takes rules of a left turn only light into consideration
    // when calculating new state
    int calculateLeftAndNormLightState(int singleLight, double relativeCycleTime, double cycleTime);
    // takes rules of a left plus normal light into consideration
    // when calculating new state
    double getCycleTime(double time, double timeRate);
    // take user-defined cycle time (time for a complete cycle through the light)
    // and modulus it (tentatively) by timeRate 
    // TODO: define exact equation for this
    // return cycleTime(double)
    void updateState(int singleLight, double newTimeInCycle);  
    // keeps track of and updates each light
    // does not return anything, but is vital to
    // manage the states and timings
    int checkForBadState();
    // checks for every instance of a bad state
    // if one is found, it returns an error code, which then
    // is used to call the recoverFromBadState function
    void recoverFromBadState(int errCode);
    // takes the traffic light array and state tables
    // and forces a reset, depending on the error code given
    // it will also take other external factors into consideration
    void setState(int singleLight, int tState);
    // for testing, allows a light state to be set to anything
    // useful when testing checkForBadState function, will do nothing
    // until that is set up

private:
    int _state;
    double _cycleTime;
    int _lightArray[4][6];
    int _masterStateTable[4][6];
    double _stateTimeTable[24];
    double _redTime;
    double _yellowTime;
    double _greenTime;
    double _leftGreenTime;
    double _leftCautionTime;
    double _leftYieldTime;
    double _lgreenSgreenTime;
    double _lyellowSgreenTime;     
};*/

#endif //SRC_DJTRAFFICLIGHT_MANAGER_H_