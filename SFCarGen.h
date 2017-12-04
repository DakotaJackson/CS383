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

/** NOTE: Builder Class is separate from Decorator Class currently.

    Builder Class is used for variables passed to the simulator, such
        as car length and speed.

    Decorator Class is used for car descriptors, such as car color and
        type of music player.

    TO DO: Figure out how to combo the two classes. **/

/*  The Main Car Class. Used in variable storage and in
        builder and decorator subclasses. */
class Car{

    /*  Decorator and Builder variables and functions. */

    string _car;              // Car Type used in Builder
    double _desiredSpeed;     // Desired Speed used in Builder
    double _length;           // Length used in Builder
    string _color;            // Car color used in Decorator
    string _drive;            // Type of Car Drive (4 Wheel or other) used in Decorator
    string _music;            // Music Player in Car used in Decorator
public:
    Car(string carType):_car{carType} {}                                 // Builder function
    void setdesiredSpeed(double speed) { _desiredSpeed = speed; }        // Builder function
    void setLength(double length)   { _length = length;   }              // Builder function
    void setColor(string color) {_color = color;}                        // Decorator function
    void setDrive(string drive) {_drive = drive;}                        // Decorator function
    void setMusic(string music) {_music = music;}                        // Decorator function
    double getEngine()          { return _desiredSpeed; }                // Builder function
    double getBody()            { return _length;   }                    // Builder function

    virtual ~Car() { }
	Car();

    void carMember();         // Uses builder classes and randomizes car selection

/*  Storage functions and backup functions

    The following functions are primarily used for storing car
    related information and also as backups in case of
    carMethod failure. */

	virtual double getDesiredSpeed() const;                  // Desired Speed backups
	void setDesiredSpeed2(double desiredSpeed);
	virtual double getLength() const;                        // Length backups
	void setLength2(double length);
	double getSpeed() const;                                 // Speed Limit Storage Variable
	void setSpeed(double desiredSpeed);
	double getTheta() const;                                 // Rotation Storage???
	void setTheta(double theta);
	int getTurnDirection() const;                            // Desired Turn Direction Randomizer and Storage
	void setTurnDirection(int turnDirection);
	double getX() const;                                     // Car X-coordinate storage
	void setX(double x);
	double getY() const;                                     // Car Y-coordinate storage
	void setY(double y);
	void* getImgPtr() const;                                 // Car image pointer
	void setImgPtr(void* imgPtr);
	double getTimeInSim() const;                             // Car time in simulation storage
	void setTimeInSim(double timeInSim);
	double getWaitTime() const;                              // Car wait time spent at lights storage
	void setWaitTime(double waitTime);

	static const int DESIRE_STRAIGHT = 1; /** \brief The car wants to go straight */
	static const int DESIRE_RIGHT = 2; /** \brief The car wants to go right */
	static const int DESIRE_LEFT = 4;/** \brief The car wants to go left */

/*  show function.

        This function merely prints the randomized information that was stored in the
        builder class. */

    void show() {
    	cout << "Car Type: " <<_car << endl
    		 << "Desired Speed: " <<_desiredSpeed << endl
    		 << "Length: "<<_length << endl << endl;
    }

/*  Storage Variables */
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

/*  Current Decorator Car Class.

    The main class for the Car Decorator. Might be moved into the Car class. */

class CarAb
{
public:
	virtual void Make() = 0;
	virtual ~CarAb() { }
};

/*  Manages Car Decoration */

class CarDecorator: public CarAb
{
protected:
    Car *_car;  // May need to be moved to public.
public:
	CarDecorator(CarAb& decorator):m_Decorator(decorator)
	{
	}
	virtual void Make()
	{
		m_Decorator.Make();
	}
	private:
	CarAb& m_Decorator;
};

/*  Car Color.

    Randomizes the color of the vehicle. Returns the
    value in string form.

    Current use: none. Merely there for added info, contributes
    nothing to the graphical UI.

    Possible idea for the future is using this value to
    decide spawn color for graphical UI vehicle. */

class ColorDec : public CarDecorator
{
public:
	ColorDec(CarAb& decorator):CarDecorator(decorator)
	{
	}
	virtual void Make()
	{
		CarDecorator::Make();
		int _randColor;
		_randColor = (1 + rand() % 5);

        if (_randColor == 1){
            _car->setColor("Red"); //RED
        }
        else if (_randColor == 2){
            _car->setColor("Blue"); //BLUE
        }
        else if (_randColor == 3){
            _car->setColor("Green"); //GREEN
            }
        else if (_randColor == 4){
            _car->setColor("Yellow"); //YELLOW
        }
        else if (_randColor== 5){
            _car->setColor("Black"); //BLACK
        }
	}
};

/*  Car Drive Type.

    Randomizes the drive type of the vehicle. Returns the
    value in string form.

    Current use: none. Merely there for added info, contributes
    nothing to the graphical UI. */

class DriveDec : public CarDecorator
{

public:
	DriveDec(CarAb& decorator):CarDecorator(decorator)
	{

	}

	virtual void Make()
	{
		CarDecorator::Make();
		int _randDrive;
		_randDrive = (1 + rand() % 3);

        if (_randDrive == 1){
            _car->setDrive("4-Wheel Drive"); //RED
        }
        else if (_randDrive == 2){
             _car->setDrive("2-Wheel Front Drive"); //RED
        }
        else if (_randDrive== 3){
             _car->setDrive("2-Wheel Rear Drive"); //RED
            }
	}
};

/*  Car Music Player.

    Randomizes the music player of the vehicle. Returns the
    value in string form.

    Current use: none. Merely there for added info, contributes
    nothing to the graphical UI. */

class MusicDec : public CarDecorator
{
public:
	MusicDec(CarAb& decorator):CarDecorator(decorator)
    {
	}

	virtual void Make()
	{
		CarDecorator::Make();
		int _randMusic;
		_randMusic = (1 + rand() % 6);

        if (_randMusic == 1){
            _car->setMusic("Cassette Player");
        }
        else if (_randMusic == 2){
            _car->setMusic("CD Player");
        }
        else if (_randMusic == 3){
            _car->setMusic("Combo Player");
            }
        else if (_randMusic == 4){
            _car->setMusic("USB Compatible Combo Player");
        }
        else if (_randMusic== 5){
            _car->setMusic("SIRIUS RADIO Player");
        }
        else if (_randMusic== 6){
            _car->setMusic("Bluetooth Player");
        }

	}

};

/*  Car Builder Main Class

    Declares basic functions of the car building process.
    Also helps combine the information. */

class CarBuilder{
public:
    Car *_car;
    virtual void getPartsDone() = 0;
    virtual void buildSpeed() = 0;
    virtual void buildLength() = 0;
    //virtual ~PlaneBuilder(){}
    Car* getCar(){ return _car; }
};



/*  Car Builder Concrete Class.

        Only knows how to build a car.

        Length is average car length.

        Desired speed is randomized. Values are as follows:
            10 = Desires to speed by value of 10 over the speed limit
            0 = Desires to follow the speed limit
            -10 = Desires to drive under the speed limit by 10
            */
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

/*  Truck Builder Concrete Class.

        Only knows how to build a truck.

        Length is average truck length.

        Desired speed is randomized. Values are as follows:
            10 = Desires to speed by value of 10 over the speed limit
            0 = Desires to follow the speed limit
            -10 = Desires to drive under the speed limit by 10
            */
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

/*  Minivan Builder Concrete Class.

        Only knows how to build a minivan.

        Length is average minivan length.

        Desired speed is randomized. Values are as follows:
            10 = Desires to speed by value of 10 over the speed limit
            0 = Desires to follow the speed limit
            -10 = Desires to drive under the speed limit by 10
            */
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

/*  Bus Builder Concrete Class.

        Only knows how to build a bus.

        Length is average bus length.

        Desired speed is randomized. Values are as follows:
            10 = Desires to speed by value of 10 over the speed limit
            0 = Desires to follow the speed limit
            -10 = Desires to drive under the speed limit by 10
            */

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

/* Defines steps and tells to the builder that build in given order. Uses
        the vehicle type passed into it. */
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
