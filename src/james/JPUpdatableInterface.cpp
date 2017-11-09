/*
 * JPTrafficSimulationUpdatableInterface.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: james
 */

#include "../../inc/JPUpdatableInterface.h"

JPUpdatableInterface::JPUpdatableInterface() {}

JPUpdatableInterface::~JPUpdatableInterface() {}

/**
 * \brief an overridable update function
 */
void JPUpdatableInterface::updateState() {}

void JPUpdatableInterface::updateAddObject(void *object, int objType){}

void JPUpdatableInterface::updateRemoveObject(void *object, int objType){}
