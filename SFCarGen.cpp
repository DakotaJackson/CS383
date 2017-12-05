
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
#include <complex>

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

/*  Backup Desired Speed Function.

    These two functions are just in case the Builder pattern
    malfunctions in some way. These will not be used if carMethod
    works properly. */

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
/*  Backup Length Function.

    These two functions are just in case the Builder pattern
    malfunctions in some way. These will not be used if carMethod
    works properly. */

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
/*  Speed Limit.

    setSpeed is used to set the speed limit. In testing,
    speed limit is provided
    within this program module. */

double Car::getSpeed() const {
	return _speed;
}

void Car::setSpeed(double desiredSpeed) {
   /* Car car;
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
    } */ // uncomment for testing and change line below to _speed = speed + desiredSpeed
	_speed = desiredSpeed;
}

/* Theta.

    Current angle of the car??? */

double Car::getTheta() const {
	return _theta;
}

void Car::setTheta(double theta) {
	_theta = theta;
}

/*  Turn Direction Decision Randomizer.

    Initializes a variable which chooses a random number.
    Based on the number chosen, the vehicle will decide where
    it wants to go on the road from 3 possible options.

    TO DO (possible in future): U-turn */

int Car::getTurnDirection() const {
	return _turnDirection;
}

void Car::setTurnDirection(int turnDirection) {
    /*_randTurnDirection = (1 + rand() % 3);
    if (_randTurnDirection == 1){
        turnDirection = DESIRE_STRAIGHT; //chose this randomly
	}
	else if (_randTurnDirection == 2){
        turnDirection = DESIRE_RIGHT; //chose this randomly
	}
	else if (_randTurnDirection == 3){
        turnDirection = DESIRE_LEFT; //chose this randomly
	}*/  // uncomment this for testing
	_turnDirection = turnDirection;
}

/*  Storage Variables.

    Initializes variables x and y, which are used
    to store the new coordinates of a car. These are
    then called by the graphical UI, which updates the image to
    its' new position on the road. */

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

/*  Storage Variables.

    Initializes a variable which stores the pointer for the
    image in the graphical UI. Another function returns
    the pointer. */

void* Car::getImgPtr() const {
	return _imgPtr;
}

void Car::setImgPtr(void* imgPtr) {
	_imgPtr = imgPtr;
}
/*  Storage Variables.

    Initializes a variable which stores time spent
    in the simulator period. Then another function returns the
    variable stored. */

double Car::getTimeInSim() const {
	return _timeInSim;
}

void Car::setTimeInSim(double timeInSim) {
	_timeInSim = timeInSim;
}
/*  Storage Variables.

    Initializes a variable which stores time spent
    waiting at a light. Then another function returns the
    variable stored. */

double Car::getWaitTime() const {
	return _waitTime;
}

void Car::setWaitTime(double waitTime) {
	_waitTime = waitTime;
}

/* Randomizes the Car called. Uses the Builders in SFCarGen.h

    Initializes a variable which creates a random number between
    1 and 8. Only 4 car types currently exist, but by doubling
    possible numbers the hopeful result is further variety in
    random generation. */

Car* Car::carMember() {
        int _randCar;
        _randCar = (1 + rand() % 8);

        Director dir;
        SimpleCar sb; //Car
        Minivan mvb; //Minivan
        Truck tb; //Truck
        Bus buss; //Bus

        if ((_randCar == 1) | (_randCar == 5)){
            Car *scar = dir.createCar(&sb); // calls the director class and passes desired vehicle type Car
            //scar->show();  // Passes information obtained into show
            return scar;
            }

        else if ((_randCar == 2) | (_randCar == 6)){
            Car *truck = dir.createCar(&tb); // calls the director class and passes desired vehicle type Truck
           //truck->show();  // Passes information obtained into show
            return truck;
            }

        else if ((_randCar == 3) | (_randCar == 7)){
            Car *mvan = dir.createCar(&mvb); // calls the director class and passes desired vehicle type Minivan
            //mvan->show();  // Passes information obtained into show
            return mvan;
            }

        else if ((_randCar == 4) | (_randCar == 8)){
            Car *bus = dir.createCar(&buss); // calls the director class and passes desired vehicle type Bus
            //bus->show();  // Passes information obtained into show
            return bus;
            }
    return NULL;
}
