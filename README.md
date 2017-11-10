# CS383 Traffic Sim

- Feel free to edit this with your own notes/info. Could help for communication

## Building
### To build with MSYS/MinGw
make test
### To build with Qt5.9.2/MinGw
- Get the installer at https://download.qt.io/official_releases/online_installers/
- Ensure MinGw is selected durring the install (other compilers are optional)
- From the cmd console add the appropriate directory for the compiler.

path=%path%;C:\Qt\Tools\mingw530_32\bin; 

- Compile

mingw32-make test

## Some notes from dj (don't think we can put our names?)

- Milestone 1 (60%) due Wednesday, October 25th

- Just copy/paste from the website so we have visibility of 6 deliverables
1. Overall (Group mark)
    Directory structure as defined in class. 1%
    make Overall code compiles with all features included (even though they are empty) and make test gives a complete report of which test cases fail 1%
2. Class diagram for your feature (Individual Mark) 3%
3. Sequence diagram for your feature (Individual Mark) 3%
4. Public view (header files) for your feature. (Private view can just be message stubs) (Individual Mark) 2%
5. Complete test plan for all functions in your feature. Most test cases should fail since there is no code yet. (Individual Mark) 3%
6. Gantt time-line with time estimates for the remainder of your feature. 2%

## Class / Module Responsibilities
This will be a bit redundant with the docs, but I thought it would be helpful in the meantime.
- 	SimulationEngine: Control the movement of cars by updating their location and speed. Add new cars to the system.
- 	TrafficModel: Determine when new cars will be added to the system and where they want to go. Provide this information to the SimulationEngine
-   Intersection: Serve as a container for lanes, speed limits, and other intersection information. Serve as a validator for the intersection configuration.
-  	Lane: Serve as an iterable container for cars.
- 	Car:  Serve as a container for information needed by the simulation engine and visualization (position, speed, etc). Generate random variable parameters not controlled by TrafficModel (e.g. desired speed, car length, etc)
-	TrafficLight: Provide the SimulationEngine with the light status (Red, Green, etc) provided the time. 
-	Input GUI: Allow the user to setup the intersection and stop light.
-	Visualization: Display a visualization of the intersection showing where each car is and animating movement.

### Optional/New/Unlcaimed
-	Output Report GUI: Display a report with the desired information. 
-	Output Tracker: Track parameters relevant to the report.
