/*
 * SFCarGen.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Sam
 */

#include "SFCarGen.h"
//#include <stdio.h>
#include <cstdlib>
#include <iostream>

int rand();

ICar::ICar() {
	// TODO Auto-generated constructor stub
	_desiredSpeed = 0;//+/- or % speed limit?
	_length = 15;

	// For Speed chosen randomly, 3 choices
	_randSpeed = (1 + rand() % 3);

	// For Car type chosen randomly, 4 choices
	_randCar = (1 + rand() % 4);

	// For Turn Direction chosen randomly, 3 choices
	_randTurnDirection = (1 + rand() % 3);

	_turnDirection = DESIRE_STRAIGHT;

}

double ICar::getDesiredSpeed() const {
	return _desiredSpeed;
}

void ICar::setDesiredSpeed(double desiredSpeed) {
    if (_randSpeed == 1){
        ICar* pCar = new SimpleCar();
//        pCar->Make();

        ICar* pSimpleCar = new SpeedyDriver(*pCar);
  //      pSimpleCar->Make();
//        Icar speedCar;
//       desiredSpeed = speedCar.desiredSpeed();
//        desiredSpeed = pSimpleCar->desiredSpeed();
    }
    else if (_randSpeed == 2){
        ICar* pCar = new SimpleCar();
 //       pCar->Make();

        ICar* pSimpleCar = new GrannieDriver(*pCar);
 //       pSimpleCar->Make();

//       desiredSpeed = pSimpleCar->desiredSpeed();
    }
    else if (_randSpeed == 3){
        ICar* pCar = new SimpleCar();
//        pCar->Make();

        ICar* pSimpleCar = new AverageDriver(*pCar);
 //       pSimpleCar->Make();

//        desiredSpeed = pSimpleCar->desiredSpeed();
    }

	_desiredSpeed = desiredSpeed;
}

double ICar::getLength() const {
	return _length;
}

void ICar::setLength(double length) {
    if (_randCar == 1){
        ICar* pCar = new SimpleCar();
  //      pCar->Make();

        ICar* pSimpleCar = new ShortLength(*pCar);
  //      pSimpleCar->Make();

//        length = pSimpleCar->length();
    }
    else if (_randCar == 2){
        ICar* pCar = new SimpleCar();
   //     pCar->Make();

        ICar* pSimpleCar = new MedLength(*pCar);
   //     pSimpleCar->Make();

//        length = pSimpleCar->length();
    }
    else if (_randCar == 3){
        ICar* pCar = new SimpleCar();
    //    pCar->Make();

        ICar* pSimpleCar = new LongLength(*pCar);
     //   pSimpleCar->Make();

//        length = pSimpleCar->length();
    }
    else if (_randCar == 3){
        ICar* pCar = new SimpleCar();
      //  pCar->Make();

        ICar* pSimpleCar = new SuperLongLength(*pCar);
       // pSimpleCar->Make();

 //       length = pSimpleCar->length();
    }
	_length = length;
}

double ICar::getSpeed() const {
	return _speed;
}

void ICar::setSpeed(double speed) {
	_speed = speed;
}

//WHAT IS THETA? ASK JAMES
//double SFCar::getTheta() const {
//	return _theta;
//}

//void SFCar::setTheta(double theta) {
//	_theta = theta;
//}

int ICar::getTurnDirection() const {
	return _turnDirection;
}

void ICar::setTurnDirection(int turnDirection) {
    if (_randTurnDirection == 1){
        turnDirection = DESIRE_STRAIGHT; //chose this randomly
	}
	else if (_randTurnDirection == 2){
        turnDirection = DESIRE_RIGHT; //chose this randomly
	}
	else if (_randTurnDirection == 3){
        turnDirection = DESIRE_LEFT; //chose this randomly
	}
	_turnDirection = turnDirection;
}

double ICar::getX() const {
	return _x;
}

void ICar::setX(double x) {
	_x = x;
}

double ICar::getY() const {
	return _y;
}

void ICar::setY(double y) {
	_y = y;
}

void* ICar::getImgPtr() const {
	return _imgPtr;
}

void ICar::setImgPtr(void* imgPtr) {
	_imgPtr = imgPtr;
}

double ICar::getTimeInSim() const {
	return _timeInSim;
}

void ICar::setTimeInSim(double timeInSim) {
	_timeInSim = timeInSim;
}

double ICar::getWaitTime() const {
	return _waitTime;
}

void ICar::setWaitTime(double waitTime) {
	_waitTime = waitTime;
}

