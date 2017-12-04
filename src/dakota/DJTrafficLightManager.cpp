#include "../../inc/DJTrafficLightManager.h"
#include "../../JPConstants.h"
#include <stdio.h>
using namespace std;

// USING STATE PATTERN (without classes, but same idea)
DJTrafficLightManager* DJTrafficLightManager::tLightManager = NULL;

DJTrafficLightManager::DJTrafficLightManager()
{
    // TODO: Depreciate single light array and use _dirAndLaneLightArray w/lightPos at 2dlight coords 
    // STATIC BINDING EXAMPLES
    _singleLightArray[24];
    _masterStateTimingTable[10];
    _masterStateTable[24][10];
    _dirAndLaneLightArray[4][6];
    _useDefaults = true;
    _cycleTime = 60.0;
    _timeRate = 1.0;
}

DJTrafficLightManager* DJTrafficLightManager::GetInstance()
{
    // ensure only single instance of the traffic light manager 
    if (tLightManager == NULL) {
        tLightManager = new DJTrafficLightManager();
    }
    return tLightManager;
}

void DJTrafficLightManager::InitManager(int lanes[4][6], int stateTable[9][6], double cycleTime, double timeRate) {
    // if default is checked in ui, first position in 2d array will be -1
    if (lanes[0][0] != -1) {
            _useDefaults = false;
            _cycleTime = cycleTime;
            _timeRate = timeRate;
    } else {
            for(int v=0;v<4;v++) {
                for(int b=0;b<6;b++) {
                    // ensures that doubleLightArray can be accessed in other functions and persists
                    _dirAndLaneLightArray[v][b] = lanes[v][b];
                }
            }
    } // END 2D LIGHT ARRAY POPULATION

    if (_useDefaults) {
        _cycleTime = 60.0; // ensure cycle time is properly set at default
        _timeRate = 1.0; // ensure sim time is properly set at default
        // hardcode state times for default states (into default table)
        int defaultTempMasterStateTimingTable[10] = {14,14,2,14,14,2,-1,-1,-1,-1};
        // only 8 lanes in default, set up in singleLightArray
        for(int i=0;i<24;i++) {
            if (i<8) {
                _singleLightArray[i] = 0; // Means something there, not init yet
            } else {
                _singleLightArray[i] = -1; // Means nothing there (only 8 lanes default)
            }
            if (i<10) {
                // default table copied into table used for rest of module
                _masterStateTimingTable[i] = defaultTempMasterStateTimingTable[i];
            }
        }
        // hard code default 2D light array (0 = not there, 1 = light present)
        int defaultTempdirAndLaneLightArray[4][6] = {
            {1,1,0,0,0,0},  // N(SB)
            {1,1,0,0,0,0},  // E(WB)
            {1,1,0,0,0,0},  // S(NB)
            {1,1,0,0,0,0}}; // W(EB)
            
        // use for loop to set all states
        // to save space, will hard code with ints.
        // RED=1,YELLOW=2,GREEN=4,LEFT_GREEN=8,LEFT_YIELD=16,LEFT_CAUTION=32
        int defaultTempStateTable[8][6] = {
            {4,4,2,1,1,1}, // N Right(SB)
            {16,1,1,1,1,1}, // N Left(SB)
            {1,1,1,4,4,2}, // E Right(WB)
            {1,1,1,16,1,1}, // E Left(WB)
            {4,4,2,1,1,1}, //S Right(NB) 
            {1,16,1,1,1,1}, // S Left(NB)
            {1,1,1,4,4,2}, // SW Right(EB)
            {1,1,1,1,16,1}}; // SW Left(EB)

        for(int x=0;x<24;x++) {
            for(int y=0;y<10;y++) {
                // only want values defined for default
                if(x<8 && y<6) {
                    if(y==0 && x==0) {
                        //initialize positions at first state
                        _singleLightArray[0] = consts::GREEN; //N Right(SB)
                        _singleLightArray[1] = consts::LEFT_YIELD; //N Left(SB)
                        _singleLightArray[2] = consts::RED; //E Right(WB)
                        _singleLightArray[3] = consts::RED; //E Left(WB)
                        _singleLightArray[4] = consts::GREEN; //S Right(NB) 
                        _singleLightArray[5] = consts::RED; //S Left(NB)
                        _singleLightArray[6] = consts::RED; //W Right(EB)
                        _singleLightArray[7] = consts::RED; //W Left(EB)
                    }
                    // set the master table to default as defined above
                    _masterStateTable[x][y] = defaultTempStateTable[x][y];
                } else {
                    // otherwise nothing is there 
                    _masterStateTable[x][y] = -1;
                }
                if(x<4 && y<6) {
                    // copy over default array to normal array in use everywhere
                    _dirAndLaneLightArray[x][y] = defaultTempdirAndLaneLightArray[x][y];
                }
            }
        } // end of initializing tables for default set up
    } else {
        printf("Using user defined state table");
        _cycleTime = getCycleTime();

        for(int r=0;r<25;r++) {
            for(int c=0;c<10;c++) {
                if(r==0) {
                    // TODO: REMOVE AFTER TESTING
                    if(c<6) {
                        _masterStateTimingTable[c] = stateTable[r][c];
                    } else {
                        _masterStateTimingTable[c] = -1;
                    }
                } else { // END STATE TABLE TIMING POPULATION
                    // TODO: REMOVE AFTER TESTING
                    if(c<6) {
                        _masterStateTable[r-1][c] = stateTable[r][c];
                    } else {
                        _masterStateTable[r-1][c] = -1; 
                    }
                } // END STATE TABLE POPULATION
            } // end of using 2D STATE TABLE population methods
        }

        int lightPos = 0;
        for(int rr=0;rr<4;rr++) {
            for(int cc=0;cc<6;cc++) {
                if(_dirAndLaneLightArray[rr][cc] != -1 && _dirAndLaneLightArray[rr][cc] != 0) { // get initial state
                    _singleLightArray[lightPos] = _masterStateTable[lightPos][0];
                } else {
                    _singleLightArray[lightPos] = -1; // nothing there
                }
                lightPos++;
            }
        } // end of using 2D SINGLE LIGHT ARRAY population methods 
    } // END OF NON-DEFAULT POPULATION
}

int DJTrafficLightManager::getState(double time, int direction, int lane) {
    double relativeTime = fmod(time, _cycleTime);
    int lightPos = 0;
    int cumulativeTime = 0;
    // t will be the current state num
    for(int t=0;t<10;t++) {
        cumulativeTime = cumulativeTime + _masterStateTimingTable[t];
        if(_masterStateTimingTable[t] != -1) {
            if(relativeTime < cumulativeTime) {
                // found state (keeps adding incriments until it falls in place)
                // same for both default and user defined case
                lightPos = getSingleLightPosition(direction, lane);
                // update state of light in single array to new position, then return state it was set to
                _singleLightArray[lightPos] = _masterStateTable[lightPos][t];
                return(_singleLightArray[lightPos]);
            }
        } else {
            // error in finding the state
            return -1;
        }
    }
    // shouldn't ever make it here. Return an error 
    return -1;
}

int DJTrafficLightManager::getSingleLightPosition(int direction, int lane) {
    if(_useDefaults) {
        // use hard-coded responses for default, as they will always be known
        if(direction==0) {
            if(lane==0) {
                return 0;
            } else {
                return 1;
            }
        }
        if(direction==1){
             if(lane==0) {
                return 2;
            } else {
                return 3;
            }
        }
        if(direction==2){
             if(lane==0) {
                return 4;
            } else {
                return 5;
            }
        }
        if(direction==3){
             if(lane==0) {
                return 6;
            } else {
                return 7;
            }
        }
    } else {
        // non default. light position will be associated with the number in the 2D light array
        //  counting from top left to bottom right.
        int lightPos = 0;
        for(int q=0;q<4;q++) {
            for(int w=0;w<6;w++) {
                if(q==direction && w==lane) {
                    return lightPos;
                }
                lightPos++;
            }
        }
    }
    // shouldn't ever get here, return -1 (error)
    return -1;
}

double DJTrafficLightManager::getCycleTime() {
    printf("Using user defined cycle time");
    _cycleTime = _cycleTime * _timeRate;
    return _cycleTime;
}
