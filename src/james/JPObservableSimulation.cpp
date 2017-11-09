/*
 * ObservableSimulation.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: james
 */

#include "../../inc/JPObservableSimulation.h"

JPObservableSimulation::JPObservableSimulation()
{
}

JPObservableSimulation::~JPObservableSimulation()
{
	// TODO Auto-generated destructor stub
}

void JPObservableSimulation::subscribe(JPUpdatableInterface iface) {
}

void JPObservableSimulation::subscribeObjectAdded(JPUpdatableInterface iface) {
}

void JPObservableSimulation::subscribeObjectRemoved(
		JPUpdatableInterface iface) {
}

void JPObservableSimulation::pushUpdate() {
}

void JPObservableSimulation::pushAdd(void* object, int objType) {
}

void JPObservableSimulation::pushRemove(void* object, int objType) {
}
