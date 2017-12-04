#Most classes/files will have three targets
#target1 ClassName.o -> compile the class
#target2 test/UnitTestName.exe -> compile the unit test program and any test stubs
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
CPPFLAGS = -g -Wall -pipe -O2 -std=c++11 -Iinc/
QTFLAGS = 
QTINC =
QTLIB = 

.PHONY: clean docs test SFBuildTest SFallTest BGbuildTest BGallTest DJbuildTest DJallTest JJbuildTest JJallTest JPbuildTest JPallTest cleandocs
############################################################################
#Begin Samantha

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
DJTrafficLightManager.o: src/dakota/DJTrafficLightManager.cpp inc/DJTrafficLightManager.h
	$(CPP) $(CPPFLAGS) -c src/dakota/DJTrafficLightManager.cpp
DJbuildTest: 
DJallTest:
#End Dakota 


############################################################################
#Begin Joe


JJTestOutput.o: test/JJTestOutput.cpp test/JJTestOutput.h
	$(CPP) $(CPPFLAGS) JJTestOutput.cpp JJTestOutput.h

JJbuildTest: 
JJallTest: 
#End Joe

############################################################################
#Begin James
#car dummy #get rid of this when the real car is here also need to replace alll references to car header/src
SFCar.o: src/james/SFCar.cpp
	$(CPP) $(CPPFLAGS) -c src/james/SFCar.cpp 	

#Observer/Observed Interface
JPUpdatableInterface.o: src/james/JPUpdatableInterface.cpp inc/JPUpdatableInterface.h
	$(CPP) $(CPPFLAGS) -c src/james/JPUpdatableInterface.cpp

JPObservableSimulation.o: JPUpdatableInterface.o src/james/JPObservableSimulation.cpp inc/JPObservableSimulation.h
	$(CPP) $(CPPFLAGS) -c src/james/JPObservableSimulation.cpp
	
test/JPObservableSimulation_test.exe: JPObservableSimulation.o test/JPObservableSimulation_test.cpp
	$(CPP) $(CPPFLAGS) test/JPObservableSimulation_test.cpp JPObservableSimulation.o JPUpdatableInterface.o -o test/JPObservableSimulation_test
	
JPOStest: test/JPObservableSimulation_test.exe
	test/JPObservableSimulation_test.exe
	 
#Test Stubs and Adapters
JPLightTestStub.o: test/JPLightTestStub.cpp test/JPLightTestStub.h #DJTrafficLightManager.o
	$(CPP) $(CPPFLAGS) -c test/JPLightTestStub.cpp	#DJTrafficLightManager
	
JPCarTestStub.o: test/JPCarTestStub.cpp test/JPCarTestStub.h SFCar.o 
	$(CPP) $(CPPFLAGS) -c test/JPCarTestStub.cpp 

JPTrafficLightAdapter.o: src/james/JPTrafficLightAdapter.cpp inc/JPTrafficLightAdapter.h JPLightTestStub.o SFCar.o DJTrafficLightManager.o
	$(CPP) $(CPPFLAGS) -c src/james/JPTrafficLightAdapter.cpp 

#Lane
JPLane.o: src/james/JPLane.cpp inc/JPLane.h inc/JPConstants.h SFCar.o src/james/LinkedList.cpp
	$(CPP) $(CPPFLAGS) -c src/james/JPLane.cpp

test/JPLane_test.exe: JPLane.o test/JPLane_test.cpp JPCarTestStub.o
	$(CPP) $(CPPFLAGS)  JPLane.o JPCarTestStub.o SFCar.o test/JPLane_test.cpp $(LIBS) -o test/JPLane_test
	
JPLtest: test/JPLane_test.exe
	test/JPLane_test.exe

#Intersection
JPIntersectionExceptions.o: src/james/JPIntersectionExceptions.cpp inc/JPIntersectionExceptions.h
	$(CPP) $(CPPFLAGS) -c src/james/JPIntersectionExceptions.cpp

JPIntersection.o: src/james/JPIntersection.cpp  inc/JPConstants.h  inc/JPIntersection.h  JPLane.o SFCar.o JPIntersectionExceptions.o
	$(CPP) $(CPPFLAGS) -c src/james/JPIntersection.cpp

test/JPIntersection_test.exe: JPLane.o  test/JPIntersection_test.cpp JPIntersection.o
	$(CPP) $(CPPFLAGS) JPLane.o JPIntersection.o JPIntersectionExceptions.o SFCar.o test/JPIntersection_test.cpp  $(LIBS) -o test/JPIntersection_test
	
JPItest: test/JPIntersection_test.exe
	test/JPIntersection_test.exe

#Intersection Grid
JPIntersectionGrid.o: src/james/JPIntersectionGrid.cpp inc/JPIntersectionGrid.h JPIntersection.o JPIntersectionExceptions.o SFCar.o
	$(CPP) $(CPPFLAGS) -c src/james/JPIntersectionGrid.cpp

test/JPIntersectionGrid_test.exe: test/JPIntersectionGrid_test.cpp JPIntersectionGrid.o JPLane.o
	$(CPP) $(CPPFLAGS) JPIntersection.o JPIntersectionExceptions.o SFCar.o JPIntersectionGrid.o JPLane.o test/JPIntersectionGrid_test.cpp  $(LIBS) -o test/JPIntersectionGrid_test
	
JPIGtest: test/JPIntersectionGrid_test.exe
	test/JPIntersectionGrid_test.exe

#Traffic Model
JPTrafficModelExceptions.o: inc/JPConstants.h inc/JPTrafficModelExceptions.h src/james/JPTrafficModelExceptions.cpp
	$(CPP) $(CPPFLAGS) -c src/james/JPTrafficModelExceptions.cpp

JPTrafficModel.o: src/james/JPTrafficModel.cpp inc/JPConstants.h inc/JPTrafficModel.h  JPTrafficModelExceptions.o  JPIntersectionExceptions.o  
	$(CPP) $(CPPFLAGS) -c src/james/JPTrafficModel.cpp 

test/JPTrafficModel_test.exe: JPTrafficModel.o test/JPTrafficModel_test.cpp
	$(CPP) $(CPPFLAGS) JPTrafficModel.o JPTrafficModelExceptions.o JPIntersectionExceptions.o test/JPTrafficModel_test.cpp  $(LIBS) -o test/JPTrafficModel_test
	
JPTMtest: test/JPTrafficModel_test.exe
	test/JPTrafficModel_test.exe

#Other Exceptions
JPOtherException.o: src/james/JPOtherException.cpp inc/JPOtherException.h
	$(CPP) $(CPPFLAGS) -c src/james/JPOtherException.cpp

#Simulation Engine
JPSimulationEngine.o: src/james/JPSimulationEngine.cpp inc/JPConstants.h inc/JPSimulationEngine.h SFCar.o JPLane.o JPIntersection.o JPTrafficModelExceptions.o JPIntersectionGrid.o JPTrafficModel.o JPIntersectionExceptions.o JPUpdatableInterface.o JPObservableSimulation.o JPOtherException.o JPTrafficLightAdapter.o
	$(CPP) $(CPPFLAGS) -c src/james/JPSimulationEngine.cpp

test/JPSimulationEngine_test.exe: JPSimulationEngine.o test/JPSimulationEngine_test.cpp JPLightTestStub.o JPCarTestStub.o 
	$(CPP) $(CPPFLAGS) SFCar.o JPLane.o JPIntersection.o JPIntersectionExceptions.o  JPIntersectionGrid.o JPTrafficModel.o JPTrafficModelExceptions.o JPSimulationEngine.o JPUpdatableInterface.o JPObservableSimulation.o JPLightTestStub.o JPCarTestStub.o JPOtherException.o JPTrafficLightAdapter.o DJTrafficLightManager.o test/JPSimulationEngine_test.cpp  $(LIBS) -o test/JPSimulationEngine_test
	
JPSEtest: test/JPSimulationEngine_test.exe
	test/JPSimulationEngine_test.exe

#Simulation Controler
JPSimulationControler.o: src/james/JPSimulationControler.cpp inc/JPConstants.h inc/JPSimulationControler.h JPSimulationEngine.o SFCar.o JPLane.o JPIntersection.o JPTrafficModelExceptions.o JPIntersectionGrid.o JPTrafficModel.o JPIntersectionExceptions.o JPUpdatableInterface.o JPObservableSimulation.o
	$(CPP) $(CPPFLAGS) -c src/james/JPSimulationControler.cpp

test/JPSimulationControler_test.exe: JPSimulationControler.o test/JPSimulationControler_test.cpp JPLightTestStub.o
	$(CPP) $(CPPFLAGS) JPSimulationControler.o SFCar.o JPLane.o JPIntersection.o JPIntersectionExceptions.o  JPIntersectionGrid.o JPTrafficModel.o JPTrafficModelExceptions.o JPSimulationEngine.o JPUpdatableInterface.o JPObservableSimulation.o JPOtherException.o JPLightTestStub.o JPTrafficLightAdapter.o DJTrafficLightManager.o test/JPSimulationControler_test.cpp  $(LIBS) -o test/JPSimulationControler_test
	
JPSCtest: test/JPSimulationControler_test.exe
	test/JPSimulationControler_test.exe
	
demo: test/JPSimulationControler_test.exe
	test/JPSimulationControler_test.exe -d
	

JPbuildTest: test/JPLane_test.exe test/JPIntersection_test.exe test/JPIntersectionGrid_test.exe test/JPTrafficModel_test.exe test/JPSimulationEngine_test.exe test/JPObservableSimulation_test.exe test/JPSimulationControler_test.exe
JPallTest: JPLtest JPItest JPIGtest JPTMtest JPSEtest JPOStest JPSCtest

buildTest: JPbuildTest BGbuildTest DJbuildTest SFbuildTest JJbuildTest 
test: JPallTest BGallTest DJallTest SFallTest JJallTest
 	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f test/*.exe
	rm -f inc/*.gch

cleandocs:
	rm -rf docs/latex
	rm -rf docs/html

docs:
	#clean out existing documentation
	doxygen docs/dxy.cfg 
	#remove temporary files generated by later versions of doxygen
	rm -f docs/*.tmp
