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

using namespace std;

int rand();

Car::Car() {
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

double Car::getDesiredSpeed() const {
	return _desiredSpeed;
}

void Car::setDesiredSpeed2(double desiredSpeed) {

   	_randSpeed = (1 + rand() % 3);

    if (_randSpeed == 1){
        _desiredSpeed = 10;
    }
    else if (_randSpeed == 2){
        _desiredSpeed = -10;
    }
    else if (_randSpeed == 3){
        _desiredSpeed = 0;
    }
}

double Car::getLength() const {
	return _length;
}

void Car::setLength2(double length) {
    _randCar = (1 + rand() % 4);
    if (_randCar == 1){
        _length = 15;
    }
    else if (_randCar == 2){
        _length = 16;
    }
    else if (_randCar == 3){
        _length = 20;
    }
    else if (_randCar == 4){
        _length = 40;
    }
}

double Car::getSpeed() const {
	return _speed;
}

void Car::setSpeed(double desiredSpeed) {
    Car car;
    car.setDesiredSpeed2(desiredSpeed);
    car.getDesiredSpeed();
    double speed;
    try {
        cin >> speed;   //only in for testing?

        if (speed < 0){
            throw 1;
        }
    }
    catch(int c) {
        cout << "Speed Limit Cannot Be Negative. Try again.";
        cin >> speed;
    }
	_speed = speed + desiredSpeed;
}


double Car::getTheta() const {
	return _theta;
}

void Car::setTheta(double theta) {
	_theta = theta;
}

int Car::getTurnDirection() const {
	return _turnDirection;
}

void Car::setTurnDirection(int turnDirection) {
    _randTurnDirection = (1 + rand() % 3);
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

double Car::getX() const {
	return _x;
}

void Car::setX(double x) {
	_x = x;
}

double Car::getY() const {
	return _y;
}

void Car::setY(double y) {
	_y = y;
}

void* Car::getImgPtr() const {
	return _imgPtr;
}

void Car::setImgPtr(void* imgPtr) {
	_imgPtr = imgPtr;
}

double Car::getTimeInSim() const {
	return _timeInSim;
}

void Car::setTimeInSim(double timeInSim) {
	_timeInSim = timeInSim;
}

double Car::getWaitTime() const {
	return _waitTime;
}

void Car::setWaitTime(double waitTime) {
	_waitTime = waitTime;
}

