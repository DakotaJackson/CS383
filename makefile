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
CPPFLAGS = -g -Wall -pipe -O2

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

#Updatable Interface
JPUpdatableInterface.o: src/james/JPUpdatableInterface.cpp inc/JPUpdatableInterface.h
	$(CPP) $(CPPFLAGS) -c src/james/JPUpdatableInterface.cpp


#Test Stubs
JPLightTestStub.o: test/JPLightTestStub.cpp test/JPLightTestStub.h #DJTrafficLightManager.o
	$(CPP) $(CPPFLAGS) -c test/JPLightTestStub.cpp	#DJTrafficLightManager
	
JPCarTestStub.o: test/JPCarTestStub.cpp test/JPCarTestStub.h SFCar.o 
	$(CPP) $(CPPFLAGS) -c test/JPCarTestStub.cpp 

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
JPTrafficModelExceptions.o: inc/JPConstants.h
	$(CPP) $(CPPFLAGS) -c src/james/JPTrafficModelExceptions.cpp src/james/JPTrafficModelExceptions.cpp inc/JPTrafficModelExceptions.h

JPTrafficModel.o: src/james/JPTrafficModel.cpp inc/JPConstants.h inc/JPTrafficModel.h  JPTrafficModelExceptions.o  JPIntersectionExceptions.o  
	$(CPP) $(CPPFLAGS) -c src/james/JPTrafficModel.cpp 

test/JPTrafficModel_test.exe: JPTrafficModel.o test/JPTrafficModel_test.cpp
	$(CPP) $(CPPFLAGS) JPTrafficModel.o JPTrafficModelExceptions.o JPIntersectionExceptions.o test/JPTrafficModel_test.cpp  $(LIBS) -o test/JPTrafficModel_test
	
JPTMtest: test/JPTrafficModel_test.exe
	test/JPTrafficModel_test.exe

#Simulation Engine
JPSimulationEngine.o: src/james/JPSimulationEngine.cpp inc/JPConstants.h inc/ inc/JPSimulationEngine.h SFCar.o JPLane.o JPIntersection.o JPTrafficModelExceptions.o JPIntersectionGrid.o JPTrafficModel.o JPIntersectionExceptions.o JPUpdatableInterface.o
	$(CPP) $(CPPFLAGS) -c src/james/JPSimulationEngine.cpp

test/JPSimulationEngine_test.exe: JPSimulationEngine.o test/JPSimulationEngine_test.cpp
	$(CPP) $(CPPFLAGS) SFCar.o JPLane.o JPIntersection.o JPIntersectionExceptions.o  JPIntersectionGrid.o JPTrafficModel.o JPTrafficModelExceptions.o JPSimulationEngine.o JPUpdatableInterface.o test/JPSimulationEngine_test.cpp  $(LIBS) -o test/JPSimulationEngine_test
	
JPSEtest: test/JPSimulationEngine_test.exe
	test/JPSimulationEngine_test.exe


JPbuildTest: test/JPLane_test.exe test/JPIntersection_test.exe test/JPIntersectionGrid_test.exe test/JPTrafficModel_test.exe test/JPSimulationEngine_test.exe
JPallTest: JPLtest JPItest JPIGtest JPTMtest JPSEtest 

buildTest: JPbuildTest BGbuildTest DJbuildTest SFbuildTest JJbuildTest
test: JPallTest BGallTest DJallTest SFallTest JJallTest
 	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f test/*.exe

cleandocs:
	rm -rf docs/latex
	rm -rf docs/html

docs:
	#clean out existing documentation
	doxygen docs/dxy.cfg 
	#remove temporary files generated by later versions of doxygen
	rm -f docs/*.tmp
