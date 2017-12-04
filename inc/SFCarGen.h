/*
 * SFCarGen.h
 *
 *  Created on: Nov 1, 2017
 *      Author: Sam
 */

#ifndef SRC_SFCARGEN_H_
#define SRC_SFCARGEN_H_

#include <iostream>
#include <cstdlib>

using namespace std;

// These next classes are decorators for car selection
class Car{
    string _car;
    double _desiredSpeed;
    double _length;
public:
    Car(string carType):_car{carType} {}
    void setdesiredSpeed(double speed) { _desiredSpeed = speed; }
    void setLength(double length)   { _length = length;   }
    double getEngine()          { return _desiredSpeed; }
    double getBody()            { return _length;   }

    virtual ~Car() { }
	Car();

	virtual double getDesiredSpeed() const;
	void setDesiredSpeed2(double desiredSpeed);
	virtual double getLength() const;
	void setLength2(double length);
	double getSpeed() const;
	void setSpeed(double desiredSpeed);
	double getTheta() const;
	void setTheta(double theta);
	int getTurnDirection() const;
	void setTurnDirection(int turnDirection);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	void* getImgPtr() const;
	void setImgPtr(void* imgPtr);
	double getTimeInSim() const;
	void setTimeInSim(double timeInSim);
	double getWaitTime() const;
	void setWaitTime(double waitTime);

	static const int DESIRE_STRAIGHT = 1; /** \brief The car wants to go straight */
	static const int DESIRE_RIGHT = 2; /** \brief The car wants to go right */
	static const int DESIRE_LEFT = 4;/** \brief The car wants to go left */


    void show() {
    	cout << "Car Type: " <<_car << endl
    		 << "Desired Speed: " <<_desiredSpeed << endl
    		 << "Length: "<<_length << endl << endl;
    }


private:
    int _randTurnDirection;
    int _randSpeed;
    int _randCar;
	int _turnDirection;
	double _x;
	double _y;
	double _theta;
	double _speed;
	double _waitTime; //optional
	double _timeInSim; //optional
	void *_imgPtr; //optional, for Joe

};

// CarBuilder Abstract Class
// Means all builders should have at least these methods
class CarBuilder{
protected:
    Car *_car;
public:
    virtual void getPartsDone() = 0;
    virtual void buildSpeed() = 0;
    virtual void buildLength() = 0;
    //virtual ~PlaneBuilder(){}
    Car* getCar(){ return _car; }
};

// CarBuilder concrete class
// knows only how to build Simple Car
class SimpleCar: public CarBuilder {
public:
    void getPartsDone() { _car = new Car("Simple Car"); }
    void buildSpeed()  {
        int _randSpeed;
        _randSpeed = (1 + rand() % 3);

    if (_randSpeed == 1){
        _car->setdesiredSpeed(10);
    }
    else if (_randSpeed == 2){
        _car->setdesiredSpeed(-10);
    }
    else if (_randSpeed == 3){
        _car->setdesiredSpeed(0);
    }
}
    void buildLength()    { _car->setLength(15);   }
    //~SimpleCar(){delete _car;}
};

// PlaneBuilder concrete class
// Knows only how to build Jet Plane
class Truck: public CarBuilder {
public:
    void getPartsDone() { _car = new Car("Truck"); }
    void buildSpeed()  {
        int _randSpeed;
        _randSpeed = (1 + rand() % 3);

    if (_randSpeed == 1){
        _car->setdesiredSpeed(10);
    }
    else if (_randSpeed == 2){
        _car->setdesiredSpeed(-10);
    }
    else if (_randSpeed == 3){
        _car->setdesiredSpeed(0);
    }
}
    void buildLength()    { _car->setLength(20);   }
    //~Truck(){delete _car;}
};

class Minivan: public CarBuilder {
public:
    void getPartsDone() { _car = new Car("Minivan"); }
    void buildSpeed()  {
        int _randSpeed;
        _randSpeed = (1 + rand() % 3);

    if (_randSpeed == 1){
        _car->setdesiredSpeed(10);
    }
    else if (_randSpeed == 2){
        _car->setdesiredSpeed(-10);
    }
    else if (_randSpeed == 3){
        _car->setdesiredSpeed(0);
    }
}
    void buildLength()    { _car->setLength(16);   }
    //~Minivan(){delete _car;}
};

class Bus: public CarBuilder {
public:
    void getPartsDone() { _car = new Car("Bus"); }
    void buildSpeed()  {
        int _randSpeed;
        _randSpeed = (1 + rand() % 3);

    if (_randSpeed == 1){
        _car->setdesiredSpeed(10);
    }
    else if (_randSpeed == 2){
        _car->setdesiredSpeed(-10);
    }
    else if (_randSpeed == 3){
        _car->setdesiredSpeed(0);
    }
}
    void buildLength()    { _car->setLength(40);   }
    //~Bus(){delete _car;}
};
// Defines steps and tells to the builder that build in given order.
class Director{
public:
    Car* createCar(CarBuilder *builder) {
        builder->getPartsDone();
        builder->buildSpeed();
        builder->buildLength();
        return builder->getCar();
    }
};

#endif /* SRC_SFCARGEN_H_ */
