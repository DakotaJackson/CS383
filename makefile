#Most classes/files will have three targets
#target1 ClassName.o -> compile the class
#target2  UnitTestName.exe -> compile the unit test program and any test stubs
#target3 ABREVIATEIONtest -> run the unit test
#
#there are a few special targets: 
#	test which runs all tests  
#	clean which deletes any compiled code
#	docs which generates documentation using doxygen
#	cleandocs which purges the html and latex subdirs of docs
#	buildTest - build all the tests but don't run so make test runs
#		all tests consecutively without compiling inbetween
#	INITIALStest - a target that runs all of a given individual's tests so not everybody is
#		is trying to update the same line in the makefile
#	INITIALSbuildTest - a target that builds all of an individual's test 

#make format
#targetName (e.g what you are creating): preqrequisites/requried files
#(tab)	command1
#(tab)	command2

#TODO
#setup usage of simlib
#setup usage of qt

LIBS = -lm
CPP=g++ 
CPPFLAGS = -g -Wall -pipe -O2 -std=c++11 
QTFLAGS = 
QTINC =
QTLIB = 

.PHONY: clean docs test SFBuildTest SFallTest BGbuildTest BGallTest DJbuildTest DJallTest JJbuildTest JJallTest JPbuildTest JPallTest cleandocs
############################################################################
#Begin Samantha

SFCarGen.o: SFCarGen.cpp  SFCarGen.h
	$(CPP) $(CPPFLAGS) -c  SFCarGen.cpp
SFbuildTest: 
SFallTest: 
#End Samantha


############################################################################
#Begin Brandon

BGbuildTest: 
BGallTest:
#End Brandon


############################################################################
#Begin Dakota 
DJTrafficLightManager.o:  DJTrafficLightManager.cpp  DJTrafficLightManager.h
	$(CPP) $(CPPFLAGS) -c  DJTrafficLightManager.cpp
DJbuildTest: 
DJallTest:
#End Dakota 


############################################################################
#Begin Joe


JJTestOutput.o:  JJTestOutput.cpp  JJTestOutput.h
	$(CPP) $(CPPFLAGS) JJTestOutput.cpp JJTestOutput.h

JJbuildTest: 
JJallTest: 
#End Joe

############################################################################
#Begin James
ALLCOMPS=JPLane.o JPIntersection.o JPIntersectionExceptions.o  JPIntersectionGrid.o JPTrafficModel.o JPTrafficModelExceptions.o JPSimulationEngine.o JPUpdatableInterface.o JPObservableSimulation.o JPLightTestStub.o JPCarTestStub.o JPOtherException.o JPTrafficLightAdapter.o DJTrafficLightManager.o
#car dummy #get rid of this when the real car is here also need to replace alll references to car header/src
#SFCar.o:  SFCar.cpp
#	$(CPP) $(CPPFLAGS) -c  SFCar.cpp 	

#Observer/Observed Interface
JPUpdatableInterface.o:  JPUpdatableInterface.cpp  JPUpdatableInterface.h
	$(CPP) $(CPPFLAGS) -c  JPUpdatableInterface.cpp

JPObservableSimulation.o: JPUpdatableInterface.o  JPObservableSimulation.cpp  JPObservableSimulation.h
	$(CPP) $(CPPFLAGS) -c  JPObservableSimulation.cpp
	
 JPObservableSimulation_test.exe: JPObservableSimulation.o  JPObservableSimulation_test.cpp
	$(CPP) $(CPPFLAGS)  JPObservableSimulation_test.cpp JPObservableSimulation.o JPUpdatableInterface.o -o  JPObservableSimulation_test
	
JPOStest:  JPObservableSimulation_test.exe
	 JPObservableSimulation_test.exe
	 
#Test Stubs and Adapters
JPLightTestStub.o:  JPLightTestStub.cpp  JPLightTestStub.h #DJTrafficLightManager.o
	$(CPP) $(CPPFLAGS) -c  JPLightTestStub.cpp	#DJTrafficLightManager
	
JPCarTestStub.o:  JPCarTestStub.cpp  JPCarTestStub.h SFCarGen.o 
	$(CPP) $(CPPFLAGS) -c  JPCarTestStub.cpp 

JPTrafficLightAdapter.o:  JPTrafficLightAdapter.cpp  JPTrafficLightAdapter.h JPLightTestStub.o SFCarGen.o DJTrafficLightManager.o
	$(CPP) $(CPPFLAGS) -c  JPTrafficLightAdapter.cpp 

#Lane
JPLane.o:  JPLane.cpp  JPLane.h  JPConstants.h SFCarGen.o  LinkedList.cpp
	$(CPP) $(CPPFLAGS) -c  JPLane.cpp

 JPLane_test.exe: JPLane.o  JPLane_test.cpp JPCarTestStub.o
	$(CPP) $(CPPFLAGS)  JPLane.o JPCarTestStub.o SFCarGen.o  JPLane_test.cpp $(LIBS) -o  JPLane_test
	
JPLtest:  JPLane_test.exe
	 JPLane_test.exe

#Intersection
JPIntersectionExceptions.o:  JPIntersectionExceptions.cpp  JPIntersectionExceptions.h
	$(CPP) $(CPPFLAGS) -c  JPIntersectionExceptions.cpp

JPIntersection.o:  JPIntersection.cpp   JPConstants.h   JPIntersection.h  JPLane.o SFCarGen.o JPIntersectionExceptions.o
	$(CPP) $(CPPFLAGS) -c  JPIntersection.cpp

 JPIntersection_test.exe: JPLane.o   JPIntersection_test.cpp JPIntersection.o
	$(CPP) $(CPPFLAGS) JPLane.o JPIntersection.o JPIntersectionExceptions.o SFCarGen.o  JPIntersection_test.cpp  $(LIBS) -o  JPIntersection_test
	
JPItest:  JPIntersection_test.exe
	 JPIntersection_test.exe

#Intersection Grid
JPIntersectionGrid.o:  JPIntersectionGrid.cpp  JPIntersectionGrid.h JPIntersection.o JPIntersectionExceptions.o SFCarGen.o
	$(CPP) $(CPPFLAGS) -c  JPIntersectionGrid.cpp

 JPIntersectionGrid_test.exe:  JPIntersectionGrid_test.cpp $(ALLCOMPS)
	$(CPP) $(CPPFLAGS) SFCarGen.o $(ALLCOMPS)  JPIntersectionGrid_test.cpp  $(LIBS) -o  JPIntersectionGrid_test
	
JPIGtest:  JPIntersectionGrid_test.exe
	 JPIntersectionGrid_test.exe

#Traffic Model
JPTrafficModelExceptions.o:  JPConstants.h  JPTrafficModelExceptions.h  JPTrafficModelExceptions.cpp
	$(CPP) $(CPPFLAGS) -c  JPTrafficModelExceptions.cpp

JPTrafficModel.o:  JPTrafficModel.cpp  JPConstants.h  JPTrafficModel.h  JPTrafficModelExceptions.o  JPIntersectionExceptions.o  
	$(CPP) $(CPPFLAGS) -c  JPTrafficModel.cpp 

 JPTrafficModel_test.exe: JPTrafficModel.o  JPTrafficModel_test.cpp
	$(CPP) $(CPPFLAGS) JPTrafficModel.o JPTrafficModelExceptions.o JPIntersectionExceptions.o  JPTrafficModel_test.cpp  $(LIBS) -o  JPTrafficModel_test
	
JPTMtest:  JPTrafficModel_test.exe
	 JPTrafficModel_test.exe

#Other Exceptions
JPOtherException.o:  JPOtherException.cpp  JPOtherException.h
	$(CPP) $(CPPFLAGS) -c  JPOtherException.cpp

#Simulation Engine
JPSimulationEngine.o:  JPSimulationEngine.cpp  JPConstants.h  JPSimulationEngine.h SFCarGen.o JPLane.o JPIntersection.o JPTrafficModelExceptions.o JPIntersectionGrid.o JPTrafficModel.o JPIntersectionExceptions.o JPUpdatableInterface.o JPObservableSimulation.o JPOtherException.o JPTrafficLightAdapter.o
	$(CPP) $(CPPFLAGS) -c  JPSimulationEngine.cpp

 JPSimulationEngine_test.exe: JPSimulationEngine.o  JPSimulationEngine_test.cpp JPLightTestStub.o JPCarTestStub.o SFCarGen.o 
	$(CPP) $(CPPFLAGS) SFCarGen.o $(ALLCOMPS)  JPSimulationEngine_test.cpp  $(LIBS) -o  JPSimulationEngine_test
	
JPSEtest:  JPSimulationEngine_test.exe
	 JPSimulationEngine_test.exe

#Simulation Controler
JPSimulationControler.o:  JPSimulationControler.cpp  JPConstants.h  JPSimulationControler.h JPSimulationEngine.o SFCarGen.o JPLane.o JPIntersection.o JPTrafficModelExceptions.o JPIntersectionGrid.o JPTrafficModel.o JPIntersectionExceptions.o JPUpdatableInterface.o JPObservableSimulation.o
	$(CPP) $(CPPFLAGS) -c  JPSimulationControler.cpp

 JPSimulationControler_test.exe: JPSimulationControler.o  JPSimulationControler_test.cpp JPLightTestStub.o
	$(CPP) $(CPPFLAGS) JPSimulationControler.o SFCarGen.o $(ALLCOMPS)  JPSimulationControler_test.cpp  $(LIBS) -o  JPSimulationControler_test
	
JPSCtest:  JPSimulationControler_test.exe
	 JPSimulationControler_test.exe
	
demo:  JPSimulationControler_test.exe
	 JPSimulationControler_test.exe -d
	

JPbuildTest:  JPLane_test.exe  JPIntersection_test.exe  JPIntersectionGrid_test.exe  JPTrafficModel_test.exe  JPSimulationEngine_test.exe  JPObservableSimulation_test.exe  JPSimulationControler_test.exe
JPallTest: JPLtest JPItest JPIGtest JPTMtest JPSEtest JPOStest JPSCtest

buildTest: JPbuildTest BGbuildTest DJbuildTest SFbuildTest JJbuildTest 
test: JPallTest BGallTest DJallTest SFallTest JJallTest
 	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f  *.exe
	rm -f  *.gch

cleandocs:
	rm -rf docs/latex
	rm -rf docs/html

docs:
	#clean out existing documentation
	doxygen docs/dxy.cfg 
	#remove temporary files generated by later versions of doxygen
	rm -f docs/*.tmp
