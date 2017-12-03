#ifndef SRC_DJTRAFFICLIGHT_MANAGER_SINGLETON_H_
#define SRC_DJTRAFFICLIGHT_MANAGER_SINGLETON_H_

// USING SINGLETON PATTERN
class DJTrafficLightManager {
public:
    // GetInstance takes max 4 dir 6 lanes to init with
    static DJTrafficLightManager* GetInstance();
    // TODO: Change state table to use 25/10
    void InitManager(int lanes[4][6], int stateTable[9][6], double cycleTime, double timeRate); // Takes all inputs and inits everything
    int getState(double time, int direction, int lane);
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