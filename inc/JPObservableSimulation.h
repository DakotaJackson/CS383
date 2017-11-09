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

class JPObservableSimulation {
typedef std::vector<JPUpdatableInterface>::iterator juivit;
public:
	JPObservableSimulation();
	virtual ~JPObservableSimulation();

	void subscribe(JPUpdatableInterface iface);
	void subscribeObjectAdded(JPUpdatableInterface iface);
	void subscribeObjectRemoved(JPUpdatableInterface iface);

protected:
	void pushUpdate();
	void pushAdd(void* object, int objType);
	void pushRemove(void* object, int objType);

private:
	std::vector<JPUpdatableInterface> _stateSubscribers;
	std::vector<JPUpdatableInterface> _addSubscribers;
	std::vector<JPUpdatableInterface> _removeSubscribers;
};

#endif /* SRC_JAMES_OBSERVABLESIMULATION_H_ */
