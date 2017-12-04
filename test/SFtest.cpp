#include "SFCarGen.h"
#include <iostream>
#include <string.h>

using namespace std;

// This is the test

void testOne();
void testTwo();
void testThree();
void testFour();

int main()
{
    //testOne();
    //testTwo();
    //testThree();
    testFour();

    return 0;
}

/* This function tests the backup functions with speed limit input. */
void testOne(){
    double desiredSpeed = 0;
    double length = 0;
    int turnDirection = 0;

    Car carOb;
    carOb.setDesiredSpeed2(desiredSpeed);
    carOb.getDesiredSpeed();
    for (int i = 0; i<5; i++)
    {

        carOb.setDesiredSpeed2(desiredSpeed);
        desiredSpeed = carOb.getDesiredSpeed();
        cout << "Desired speed related to limit: " << carOb.getDesiredSpeed() << endl;
        cout << "Please input speed limit: ";
        carOb.setSpeed(desiredSpeed);
        carOb.getSpeed();
        cout << "Actual speed related to limit: " <<carOb.getSpeed() << endl;
        carOb.setLength2(length);
        carOb.getLength();
        cout << "Car Length: " << carOb.getLength() << endl;
        carOb.setTurnDirection(turnDirection);
        carOb.getTurnDirection();
        cout << "Turn Direction: (1-straight, 2-right, 4-left)" << carOb.getTurnDirection() << endl;
    }
}

/* This function tests the backup functions without speed limit input. */
void testTwo(){
    double desiredSpeed = 0;
    double length = 0;
    int turnDirection = 0;

    Car carOb;
    carOb.setDesiredSpeed2(desiredSpeed);
    carOb.getDesiredSpeed();
    for (int i = 0; i<5; i++)
    {
        carOb.setDesiredSpeed2(desiredSpeed);
        desiredSpeed = carOb.getDesiredSpeed();
        cout << "Desired speed related to limit: " << carOb.getDesiredSpeed() << endl;
        carOb.setLength2(length);
        carOb.getLength();
        cout << "Car Length: " << carOb.getLength() << endl;
        carOb.setTurnDirection(turnDirection);
        carOb.getTurnDirection();
        cout << "Turn Direction: (1-straight, 2-right, 4-left)" << carOb.getTurnDirection() << endl;
    }
}

/* This function tests the Builder classes. */
void testThree(){

    for (int i = 0; i<5; i++){
        Director dir;  // Creation of objects for each Builder class
        SimpleCar sb;
        Truck tb;
        Minivan mvb;
        Bus buss;

        Car *scar = dir.createCar(&sb);  // Calls the director class and passes in information obtained in Car Builder Class
        Car *truck = dir.createCar(&tb);  // Calls the director class and passes in information obtained in Truck Builder Class
        Car *mvan = dir.createCar(&mvb);  // Calls the director class and passes in information obtained in Minivan Builder Class
        Car *bus = dir.createCar(&buss);  // Calls the director class and passes in information obtained in Bus Builder Class

        scar->show();  // Calls the show function and passes in information consolidated by director class
        truck->show();
        mvan->show();
        bus->show();

        delete scar;  // Deletes the objects
        delete truck;
        delete mvan;
        delete bus;
    }

}

/* This function tests carMember function. */
void testFour(){
    Car member;

    for (int i = 0; i<5; i++){  // Loop is used to ensure randomization.
        member.carMember();
    }

}

// Estimated: 6 hours meeting time
// Actual: 4 hours meeting time
//
// Estimated: 12 hours research time
// Actual: 10 hours
//
// Estimated Programming: 6 hours
// Actual Programming: 10 hours
//
// Total Estimated: 24 hours
// Total Actual: 24 hours
