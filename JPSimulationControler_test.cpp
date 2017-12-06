/*
 * SimulationControler_test.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: james
 */

#include "JPSimulationControler.h"
#include <stdio.h>
//every update check time and check car position
//evolution
//2 seconds at 0.1 sec/step
//pause 2 seconds
//start again change timeStep
//change speed
//stop at duration

JPTrafficModel *getNullTrafficModel()
{
	JPTrafficModel *model = new JPTrafficModel();
	for(int dir = 0; dir < 4; dir++)
	{
		model->setProbability(dir,0,0,100);
		model->setTrafficRate(dir,0);
	}
	return model;
}
void setup()
{
	JPSimulationEngine *eng = JPSimulationEngine::getInstance();
	JPIntersection *inter = new JPIntersection();
	int dir;
	for(dir = 0; dir < 4; dir++)
	{
		inter->setLaneOffset(dir,2);
		inter->setTrackedLaneLength(dir, 300);
	}

	for(dir = 0; dir < 4; dir++)
	{
		inter->addLane(dir,0,JPLane::RIGHT + JPLane::STRAIGHT,1,0);
		inter->addLane(dir,1,JPLane::LEFT,1,0);
	}
	eng->setIntersection(inter);
	eng->setTrafficLight(new JPLightTestStub(JPLightTestStub::GREEN_EW));
	eng->setTrafficModel(getNullTrafficModel());


}
int main()
{
	setup();
	//printf("Setup Done!\n");
	JPSimulationControler *con =  JPSimulationControler::getInstance();
	con->setDuration(5); //run for seconds
	con->start();
}
