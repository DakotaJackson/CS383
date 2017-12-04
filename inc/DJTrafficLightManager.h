/*
 * DJTrafficLightManager.h 
 * 
 *  Created on: Oct 21, 2017
 *      Author: dakota
 */

#ifndef SRC_DJTRAFFICLIGHT_MANAGER_SINGLETON_H_
#define SRC_DJTRAFFICLIGHT_MANAGER_SINGLETON_H_

/**
 * \brief Contains all the necessary functionality for running the
 *  traffic light portion of the simulation. It uses a singleton, since ONLY 1
 *  instance of this is needed (more will cause problems). Only functions
 *  called outside of here should be the getCycleTime and getState functions for use 
 *  in general simulation.
 */
class DJTrafficLightManager {
public:
    // GetInstance takes max 4 dir 6 lanes to init with
    static DJTrafficLightManager* GetInstance();
    // TODO: Change state table to use 25/10 after ui support added
    /**
     * \brief initialize all lights and states for program
     * \param lanes 2D array of all lights
     * \param stateTable contains all timings of states per light and all cycle timings
     * \param cycleTime for calculating internal state time later
     * \param timeRate directly impacts what the standard cycleTime will be
    */
    void InitManager(int lanes[4][6], int stateTable[9][6], double cycleTime, double timeRate); // Takes all inputs and inits everything

    /**
     * \brief gathers state of a specific light based on the time given
     * \param direction 0-3, for N,E,S,W respectively
     * \param lane 0-(numLanes-1) for direction, for finding single light in 2D array
     * \param time overall time in simulation, modulus w/cycleTime to get relative time in cycle
     * \return either a single constant or combination of constants as defined in JPConstants.h  
    */
    int getState(double time, int direction, int lane);
    
    /**
     * \brief returns the current cycle time for the rest of the program to use
    */
    double getCycleTime();
    ~DJTrafficLightManager(); // Destructor
private:
    DJTrafficLightManager(); // Constructor
    static DJTrafficLightManager* tLightManager;
    int getSingleLightPosition(int direction, int lane);
    int _singleLightArray[24]; // keeps track of individual(numbered) light
    int _masterStateTimingTable[10]; // max 10 states
    int _masterStateTable[24][10]; // max 24 lights possible, max 10 states possible
    int _dirAndLaneLightArray[4][6]; // used to find position when given direction and lane
    bool _useDefaults; // flag to indicate whether or not defaults need to be used
    double _cycleTime; // used to find current state in cycle and return externally
    double _timeRate; // used to find how fast sim is running, used for finding cycle time
};

#endif /* SRC_DJTRAFFICLIGHT_MANAGER_H_ */