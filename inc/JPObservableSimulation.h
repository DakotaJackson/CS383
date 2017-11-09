/*
 * ObservableSimulation.h
 *
 *  Created on: Nov 8, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_OBSERVABLESIMULATION_H_
#define SRC_JAMES_OBSERVABLESIMULATION_H_
#include "JPUpdatableInterface.h"
#include <vector>

class JPObservableSimulation
{
typedef std::vector<JPUpdatableInterface*>::iterator juivit;
public:
	JPObservableSimulation();
	virtual ~JPObservableSimulation();

	/** \brief Subscribe to state change updates */
	void subscribe(JPUpdatableInterface *iface);
	/** \brief Subscribe to udpates for the addition of objects */
	void subscribeObjectAdded(JPUpdatableInterface *iface);
	/** \brief Subscribe to udpates for the addition of objects */
	void subscribeObjectRemoved(JPUpdatableInterface *iface);

protected:
	/** \brief call the updateState function on observers */
	void pushUpdate();
	/** \brief call the updateAddObject function on observers */
	void pushAdd(void* object, int objType);
	/** \brief call the updateRemoveObject function on observers */
	void pushRemove(void* object, int objType);

private:
	std::vector<JPUpdatableInterface*> _stateSubscribers;
	std::vector<JPUpdatableInterface*> _addSubscribers;
	std::vector<JPUpdatableInterface*> _removeSubscribers;
};

#endif /* SRC_JAMES_OBSERVABLESIMULATION_H_ */
