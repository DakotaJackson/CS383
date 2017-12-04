#ifndef JJallTest_H
#define JJallTest_H

class JJallTest
{

public:
    JJallTest();
    virtual ~JJallTest();


    //lanes
    int testMaxLanes();
    int testMinLanes();
    int testLanePosition();
    int testTurnArrow();
    int testLaneCenter();

    //screen
    int testScreenResMax();
    int testScreenResMin();

    //cars
    int testCarPositionMax();
    int testCarPositionMin();
    int testCarAngleMax();
    int testCarAngleMin();
    int testCarAngleNeg();

    //lights
    int testLightPosMin();
    int testLightPosMax();
    int testLightCycleBounds();

};

#endif // JJallTest_H
