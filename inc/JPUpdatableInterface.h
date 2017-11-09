/*
 * JPTrafficSimulationUpdatableInterface.h
 *
 *  Created on: Oct 25, 2017
 *      Author: james
 */

#ifndef SRC_JAMES_JPUPDATABLEINTERFACE_H_
#define SRC_JAMES_JPUPDATABLEINTERFACE_H_

/**
 * \brief and interface class with an overidable update function
 */
class JPUpdatableInterface {
public:
	JPUpdatableInterface();
	virtual ~JPUpdatableInterface();
	//uniquely named update method
	virtual void updateState();
	virtual void updateAddObject(void *object, int objType);
	virtual void updateRemoveObject(void *object, int objType);
};

#endif /* SRC_JAMES_JPUPDATABLEINTERFACE_H_ */
