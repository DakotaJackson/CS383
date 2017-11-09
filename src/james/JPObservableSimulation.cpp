/*
 * ObservableSimulation.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: james
 */

#include "../../inc/JPObservableSimulation.h"

JPObservableSimulation::JPObservableSimulation(){}

JPObservableSimulation::~JPObservableSimulation(){}

void JPObservableSimulation::subscribe(JPUpdatableInterface *iface)
{
	_stateSubscribers.push_back(iface);
}

void JPObservableSimulation::subscribeObjectAdded(JPUpdatableInterface *iface)
{
	_addSubscribers.push_back(iface);
}

void JPObservableSimulation::subscribeObjectRemoved(
		JPUpdatableInterface *iface)
{
	_removeSubscribers.push_back(iface);
}

void JPObservableSimulation::pushUpdate()
{
	for(juivit iter = _stateSubscribers.begin(); iter != _stateSubscribers.end(); iter++)
		(*iter)->updateState();
}

void JPObservableSimulation::pushAdd(void* object, int objType)
{
	for(juivit iter = _addSubscribers.begin(); iter != _addSubscribers.end(); iter++)
		(*iter)->updateAddObject(object, objType);
}

void JPObservableSimulation::pushRemove(void* object, int objType)
{
	for(juivit iter = _removeSubscribers.begin(); iter != _removeSubscribers.end(); iter++)
		(*iter)->updateRemoveObject(object, objType);
}
