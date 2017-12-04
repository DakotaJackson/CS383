/*
 * SFCar.h
 *	Dummy header for compilability
 *  Created on: Oct 21, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_SFCAR_H_
#define SRC_JAMES_SFCAR_H_

class SFCar
{
public:
	SFCar();
	virtual ~SFCar();
	virtual double getDesiredSpeed() const;
	virtual double getLength() const;
	double getSpeed() const;
	void setSpeed(double speed);
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

private:
	int _turnDirection;
	double _length;
	double _x;
	double _y;
	double _theta;
	double _speed;
	double _desiredSpeed;
	double _waitTime; //optional
	double _timeInSim; //optional
	void *_imgPtr; //optional, for Joe

};

#endif /* SRC_JAMES_SFCAR_H_ */
