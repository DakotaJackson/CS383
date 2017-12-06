/*
 * JPLane.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: james
 */

#include "JPLane.h"
#include <stdexcept>
//# include "LinkedList.h

JPLane::JPLane(int turnOptions, int leftTarget, int rightTarget)
{
	_turnOptions = turnOptions;
	_leftTarget = leftTarget;
	_rightTarget = rightTarget;
	_position = 0;

	//LinkedList<Car>* list;
	_list = new LinkedList<Car*>();

	_iter = 0;
}

int JPLane::resetToFirstCar()
{
	int size = _list->getSize();
	if (0 == size)
		return 0;

	//destroy existing iterator
	if (0 != _iter)
		delete _iter;

	//reset position
	_position = 0;

	//set iterator
	_iter = new Iterator<Car*>( _list->begin() );
	return size;
}

Car* JPLane::getNextCar()
{
	//Sprintf("Size: %d,\t Position %d\n", _list->getSize(), _position );
	//if we are at the end, return 0
	if( _position > _list->getSize() - 1 ||
			0 == _iter)
		return 0;

	_position++;
	_lastCar = *( (*_iter)++);
	return _lastCar;

}


void JPLane::removeCurrentCar()
{

	if(_position)
		_list->removeAt(_position - 1);
}

Car *JPLane::removeFirstCar()
{
	//return null if list is empty
	if( _list->isEmpty() )
		return 0;

	return _list->removeFirst();
}

void JPLane::addCarAtPos(Car* car, int direction)
{
	//TODO write addCarAtPos
	double sign = 1;
	bool isX = true;
	double carPos, listPos;
	Car *listCar;

	if(direction == JPIntersection::NORTHBOUND ||
			direction == JPIntersection::SOUTHBOUND)
	{
		isX = false; //we want to look at Y
		carPos = car->getY();
	}
	else
		carPos = car->getX();

	if(direction == JPIntersection::WESTBOUND ||
			direction == JPIntersection::SOUTHBOUND)
		sign = -1;
	carPos *= sign; //orient the car

	//find the position
	int leng, i;
	Iterator<Car*> iter = _list->begin();
	leng = _list->getSize();

	for(i = 0; i < leng; i++)
	{
		listCar = *(iter++);
		if(isX)
			listPos = sign * listCar->getX();
		else
			listPos = sign * listCar->getX();

		if(listPos < carPos) //proceed until no cars are in front
			break;
	}
	_list->add(i, car);
}

void JPLane::addCarAtEnd(Car* car)
{
	_list->addLast(car);
}


JPLane::~JPLane()
{
	//TODO destroy all cars in the list
	/*
	if( 0 != _iter)
		delete _iter;
	delete _list;
	*/
}

bool JPLane::isEmpty() const
{
	if( 0 == _list->getSize())
		return 1;
	else
		return 0;
}

int JPLane::getSize() const
{
	return _list->getSize();
}

int JPLane::getLeftTarget() const { return _leftTarget; }
int JPLane::getRightTarget() const { return _rightTarget; }
/**
 * \return A bitfield sum of the valid turn options \link STRAIGHT \endlink \link RIGHT \endlink \link LEFT \endlink
 */
int JPLane::getTurnOptions() const {return _turnOptions; }
