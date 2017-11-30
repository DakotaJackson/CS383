#include "SFCarGen.h"
#include <iostream>
#include <string.h>

using namespace std;
// This is the test

void testOne();
void testTwo();
void testThree();

int main()
{
    //testOne();
    //testTwo();
    testThree();

    return 0;
}

void testOne(){
    double desiredSpeed = 0;
    double length = 0;
    int turnDirection = 0;

    ICar car;
    car.setDesiredSpeed(desiredSpeed);
    car.getDesiredSpeed();
    for (int i = 0; i<5; i++)
    {
        car.setDesiredSpeed(desiredSpeed);
        desiredSpeed = car.getDesiredSpeed();
        cout << "Desired speed related to limit: " << car.getDesiredSpeed() << endl;
        cout << "Please input speed limit: ";
        car.setSpeed(desiredSpeed);
        car.getSpeed();
        cout << "Actual speed related to limit: " <<car.getSpeed() << endl;
        car.setLength(length);
        car.getLength();
        cout << "Car Length: " << car.getLength() << endl;
        car.setTurnDirection(turnDirection);
        car.getTurnDirection();
        cout << "Turn Direction: (1-straight, 2-right, 4-left)" << car.getTurnDirection() << endl;
    }
}

void testTwo(){
    double desiredSpeed = 0;
    double length = 0;
    int turnDirection = 0;

    ICar car;
    car.setDesiredSpeed(desiredSpeed);
    car.getDesiredSpeed();
    for (int i = 0; i<5; i++)
    {
        car.setDesiredSpeed(desiredSpeed);
        desiredSpeed = car.getDesiredSpeed();
        cout << "Desired speed related to limit: " << car.getDesiredSpeed() << endl;
        car.setLength(length);
        car.getLength();
        cout << "Car Length: " << car.getLength() << endl;
        car.setTurnDirection(turnDirection);
        car.getTurnDirection();
        cout << "Turn Direction: (1-straight, 2-right, 4-left)" << car.getTurnDirection() << endl;
    }
}

void testThree(){

    for (int i = 0; i<5; i++){
        Director dir;
        SimpleCar sb;
        Truck tb;
        Minivan mvb;
        Bus buss;

        Car *scar = dir.createCar(&sb);
        Car *truck = dir.createCar(&tb);
        Car *mvan = dir.createCar(&mvb);
        Car *bus = dir.createCar(&buss);

        scar->show();
        truck->show();
        mvan->show();
        bus->show();

        delete scar;
        delete truck;
        delete mvan;
        delete bus;
    }

}
