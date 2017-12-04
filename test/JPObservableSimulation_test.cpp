/*
 * ObservableSimulation_test.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: james
 */

#include "JPObservableSimulation.h"
#include "JPConstants.h"
#include <list>

/**
 * \defgroup TST Testing Specific Classes
 * @{
 */

/**
 * \brief A simulated object type for testing the Observer/Observed classes.
 *
 * It is created with an id so it can be uniquely identified for verification purposes.
 */
class Gadget
{
public:
	Gadget(int id) { _id = id; }
	int getID() { return _id; }
private:
	int _id;
};

/**
 * \brief A simulated object type for testing the Observer/Observed classes.
 *
 * It is created with an id so it can be uniquely identified for verification purposes.
 */
class Gizmo
{
public:
	Gizmo(int id) { _id = id; }
	int getID() { return _id; }
private:
	int _id;
};

class ObservableTest: public JPObservableSimulation
{
public:
	static const int TYPE_GADGET = 0;
	static const int TYPE_GIZMO = 1;

	void addGadget(int id)
	{
		Gadget *g = new Gadget(id);
		_gadgets.push_back(g);
		pushAdd(g, TYPE_GADGET);
	}

	void addGizmo(int id)
	{
		Gizmo *g = new Gizmo(id);
		_gizmos.push_back(g);
		pushAdd(g, TYPE_GIZMO);
	}

	void removeGizmo()
	{
		Gizmo *g = _gizmos.front();
		pushRemove(g, TYPE_GIZMO);
		_gizmos.pop_front();

	}

	void removeGadget()
	{
		Gadget *g = _gadgets.front();
		pushRemove(g, TYPE_GADGET);
		_gadgets.pop_front();

	}

	int getStepsTaken() { return _stepsTaken; }
	void step()
	{
		_stepsTaken++;
		pushUpdate();
	}
	ObservableTest() { _stepsTaken = 0; }

private:
	int _stepsTaken;
	std::list<Gadget*> _gadgets;
	std::list<Gizmo*> _gizmos;
};

/** \brief A test class that can handle all 3 types of subscriptions */
class ObserverTest: public JPUpdatableInterface
{
public:
	int lastRemovedType;
	int lastAddedType;
	int lastRemovedID;
	int lastAddedID;
	int currentStep;
	ObservableTest *_ot;

	ObserverTest(ObservableTest *ot)
	{
		reset();
		_ot = ot;
	}

	/** clear all variables */
	void reset()
	{
		lastRemovedType = -1;
		lastAddedType = -1;
		lastRemovedID = -1;
		lastAddedID = -1;
		currentStep = -1;
	}

	//update handlers
	/** \brief Handle state update */
	void updateState() { currentStep = _ot->getStepsTaken();}

	/** \brief Handle an object being added to the simulation */
	void updateAddObject(void *object, int objType)
	{
//printf("Add Update %d\n", objType);
		if(ObservableTest::TYPE_GADGET == objType)
		{
//			printf("It's a gadget\n");
			Gadget *gadget = (Gadget*)object;
			lastAddedType = 0;
			lastAddedID = gadget->getID();
		}
		else if(ObservableTest::TYPE_GIZMO == objType)
		{
//			printf("It's a gizmo\n");
			Gizmo *gizmo = (Gizmo*)object;
			lastAddedType = 1;
			lastAddedID = gizmo->getID();
		}
//printf("Type: %d\t ID: %d\n",lastAddedType, lastAddedID);
	}

	/** \brief Handle an object being removed from the simulation */
	void updateRemoveObject(void *object, int objType)
	{
		if(ObservableTest::TYPE_GADGET == objType)
		{
			Gadget *gadget = (Gadget*)object;
			lastRemovedType = 0;
			lastRemovedID = gadget->getID();
		}
		else if(ObservableTest::TYPE_GIZMO == objType)
		{
			Gizmo *gizmo = (Gizmo*) object;
			lastRemovedType = 1;
			lastRemovedID = gizmo->getID();
		}
	}
};

/**
 * \brief A test class that only subscribes to state.
 */
class StateObserverTest: public ObserverTest
{
public:
	StateObserverTest(ObservableTest *sim): ObserverTest(sim)
	{
		sim->subscribe(this);
	}
};

/**
 * \brief A test class that only subscribes to object removal.
 */
class RemoveObserverTest: public ObserverTest
{
public:
	RemoveObserverTest(ObservableTest *sim): ObserverTest(sim)
	{
		sim->subscribeObjectRemoved(this);
	}
};

/**
 * \brief A test class that only subscribes to object addition.
 */
class AddObserverTest: public ObserverTest
{
public:
	AddObserverTest(ObservableTest *sim): ObserverTest(sim)
	{
		sim->subscribeObjectAdded(this);
	}
};

/**
 * \brief A test class that subscribes to everything.
 */
class AllObserverTest: public ObserverTest
{
public:
	AllObserverTest(ObservableTest *sim): ObserverTest(sim)
	{
		sim->subscribe(this);
		sim->subscribeObjectRemoved(this);
		sim->subscribeObjectAdded(this);
	}
};
/** @} */

int verifyState(ObserverTest &observer, int step, int addT, int addID, int remT, int remID)
{
	int ret = 0;
	if(observer.currentStep != step)
		ret += 1;
	if(observer.lastAddedType != addT)
		ret += 2;
if (ret != 0) printf("addT %d, %d\n",observer.lastAddedType, addT );
	if(observer.lastAddedID != addID)
		ret += 4;
	if(observer.lastRemovedType != remT)
		ret += 8;
	if(observer.lastRemovedID != remID)
		ret += 16;
if( ret != 0 ) printf("%d\t%d\t%d\n", ret, observer.currentStep, step);
	return ret;
}
int testAdding(ObservableTest *sim, StateObserverTest &state, AllObserverTest &all, AddObserverTest &add, RemoveObserverTest &rem)
{
	int i;
	int ret = 0;
	//clear tracking variables
	state.reset();
	add.reset();
	rem.reset();
	all.reset();

	//add 10 each of gadgets and gizmos
	for(i = 0; i < 10; i++)
	{
		//add a gadget and make sure we got the correct updates
		sim->addGadget(i);
		//step, addT, addID, remT, remID
		if(verifyState(state, -1, -1, -1, -1, -1) != 0)
			ret += 1;
		if(verifyState(add, -1, 0, i, -1, -1) != 0)
			ret += 4; //*
		if(verifyState(rem, -1, -1, -1, -1, -1) != 0)
			ret += 8;
		if(verifyState(all, -1, 0, i, -1, -1) != 0)
			ret += 16; //*

		sim->addGizmo(i);
		//step, addT, addID, remT, remID
		if(verifyState(state, -1, -1, -1, -1, -1) != 0)
			ret += 32;
		if(verifyState(add, -1, 1, i, -1, -1) != 0)
			ret += 64; //*
		if(verifyState(rem, -1, -1, -1, -1, -1) != 0)
			ret += 128;
		if(verifyState(all, -1, 1, i, -1, -1) != 0)
			ret += 256; //*

		if(0 != ret) printf("[%d]\t%d\n", i, ret);
		if(0 != ret)
			return ret;
	}
	return 0;
}

int testRemoving(ObservableTest *sim, StateObserverTest &state, AllObserverTest &all, AddObserverTest &add, RemoveObserverTest &rem)
{
	int i;
	int ret = 0;
	//clear tracking variables
	state.reset();
	add.reset();
	rem.reset();
	all.reset();

	//remove all 20 items from the sim
	for(i = 0; i < 10; i++)
	{
		//add a gadget and make sure we got the correct updates
		sim->removeGadget();
		//step, addT, addID, remT, remID
		if(verifyState(state, -1, -1, -1, -1, -1) != 0)
			ret += 1;
		if(verifyState(add, -1, -1, -1, -1, -1) != 0)
			ret += 4; //*
		if(verifyState(rem, -1, -1, -1, 0, i) != 0)
			ret += 8;
		if(verifyState(all, -1, -1, -1, 0, i) != 0)
			ret += 16; //*

		sim->removeGizmo();
		//step, addT, addID, remT, remID
		if(verifyState(state, -1, -1, -1, -1, -1) != 0)
			ret += 32;
		if(verifyState(add, -1, -1, -1, -1, -1) != 0)
			ret += 64; //*
		if(verifyState(rem, -1, -1, -1, 1, i) != 0)
			ret += 128;
		if(verifyState(all, -1, -1, -1, 1, i) != 0)
			ret += 256; //*

		if(0 != ret) printf("[%d]\t%d\n", i, ret);
		if(0 != ret)
			return ret;
	}
	return 0;
}
int testState(ObservableTest *sim, StateObserverTest &state, AllObserverTest &all, AddObserverTest &add, RemoveObserverTest &rem)
{
	int i;
	int ret = 0;
	//clear tracking variables
	state.reset();
	add.reset();
	rem.reset();
	all.reset();

	//step 10 times
	for(i = 0; i < 10; i++)
	{
		//add a gadget and make sure we got the correct updates
		sim->step();
		//step, addT, addID, remT, remID
		if(verifyState(state, 1+i, -1, -1, -1, -1) != 0)
			ret += 1; //*
		if(verifyState(add, -1, -1, -1, -1, -1) != 0)
			ret += 4;
		if(verifyState(rem, -1, -1, -1, -1, -1) != 0)
			ret += 8;
		if(verifyState(all, 1+i, -1, -1, -1, -1) != 0)
			ret += 16; //*

		if(0 != ret) printf("[%d]\t%d\n", i, ret);
		if(0 != ret)
			return ret;
	}
	return 0;
}

int main()
{
	//create a simulation
	ObservableTest *mySim = new ObservableTest();

	//add the four observers
	StateObserverTest stateObserver(mySim);
	AllObserverTest allObserver(mySim);
	AddObserverTest addObserver(mySim);
	RemoveObserverTest removeObserver(mySim);

	//cause events make sure the right observers see them
	consts::testOuptut("JPObservableSimulation: Adding",
			testAdding(mySim, stateObserver, allObserver, addObserver, removeObserver));
	consts::testOuptut("JPObservableSimulation: Removing",
			testRemoving(mySim, stateObserver, allObserver, addObserver, removeObserver));
	consts::testOuptut("JPObservableSimulation: State",
			testState(mySim, stateObserver, allObserver, addObserver, removeObserver));

	return 0;
}
