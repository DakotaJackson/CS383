/*
 * JPTrafficSimulationUpdatableInterface.h
 *
 *  Created on: Oct 25, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPUPDATABLEINTERFACE_H_
#define SRC_JAMES_JPUPDATABLEINTERFACE_H_

/**
 * \brief An interface class with overidable update functions.
 *
 * It contains three notification functions each of which is optional. The first \link updateState \endlink
 * is called when ever the state of simulation changes. The second two are called when objects are added
 * or removed from the simulation. This can allow services such as a tabulator to process objects immediately
 * after adding or immediately before removing them to/from the simulation.
 *
 * For example, consider a reporting system that wants to track how long a car spent waiting. If wait time is
 * a parameter held and updated within the car, the reporting system will want to see it immediately before it
 * leaves the simulation. When the car is at the simulation boundary and about to be deleted it will first send
 * a \link updateRemoveObject \endlink. This prevents the reporting module from needing to predict which state
 * update will be the last to have a given car.
 *
 */
class JPUpdatableInterface
{
public:
	JPUpdatableInterface();
	virtual ~JPUpdatableInterface();
	//uniquely named update method

	/**
	 * \brief This will be called in observers when a state transition has been completed.
	 */
	virtual void updateState();

	/**
	 * \brief Called when a new object is added into the simulation.
	 *
	 * This allows an observer such as a tabulator to examine objects immediately when they
	 * are added to the simulation.
	 * \param object A pointer to the object
	 * \param objType An integer that defines the type of object so that it can be properly cast.
	 * The values for this should be defined as either static constants are using enumeration
	 * in the subclass of JPObservableSimulation
	 */
	virtual void updateAddObject(void *object, int objType);

	/**
	 * \brief Called when an object is about to be removed from the simulation
	 *
	 * This allows an observer such as a tabulator to examine objects immediately before they are
	 * removed the simulation.
	 * \param object A pointer to the object
	 * \param objType An integer that defines the type of object so that it can be properly cast.
	 * The values for this should be defined as either static constants are using enumeration
	 * in the subclass of JPObservableSimulation
	 */
	virtual void updateRemoveObject(void *object, int objType);
};

#endif /* SRC_JAMES_JPUPDATABLEINTERFACE_H_ */
