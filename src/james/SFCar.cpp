/*
 * SFCar.cpp
 *	Dummy class for compilability
 *  Created on: Oct 21, 2017
 *      Author: james
 */

#include "SFCar.h"

SFCar::SFCar() {
	// TODO Auto-generated constructor stub
	_desiredSpeed = 0;//+/- or % speed limit?
	_length = 15;
	_turnDirection = DESIRE_STRAIGHT; //chose this randomly

}

SFCar::~SFCar() {
	// TODO Auto-generated destructor stub
}

double SFCar::getDesiredSpeed() const {
	return _desiredSpeed;
}

double SFCar::getLength() const {
	return _length;
}

double SFCar::getSpeed() const {
	return _speed;
}

void SFCar::setSpeed(double speed) {
	_speed = speed;
}

double SFCar::getTheta() const {
	return _theta;
}

void SFCar::setTheta(double theta) {
	_theta = theta;
}

int SFCar::getTurnDirection() const {
	return _turnDirection;
}

void SFCar::setTurnDirection(int turnDirection) {
	_turnDirection = turnDirection;
}

double SFCar::getX() const {
	return _x;
}

void SFCar::setX(double x) {
	_x = x;
}

double SFCar::getY() const {
	return _y;
}

void SFCar::setY(double y) {
	_y = y;
}

void* SFCar::getImgPtr() const {
	return _imgPtr;
}

void SFCar::setImgPtr(void* imgPtr) {
	_imgPtr = imgPtr;
}

double SFCar::getTimeInSim() const {
	return _timeInSim;
}

void SFCar::setTimeInSim(double timeInSim) {
	_timeInSim = timeInSim;
}

double SFCar::getWaitTime() const {
	return _waitTime;
}

void SFCar::setWaitTime(double waitTime) {
	_waitTime = waitTime;
}
