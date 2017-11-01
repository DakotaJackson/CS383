#ifndef SRC_SFCARCONSTANT_H_
#define SRC_SFCARCONSTANT_H_

class SFcarConstant{
	namespace carconsts{
		
		// Car Constants, Type of car, length, desired speed
		const int cars[10][3] = {
			//{ #, #, #} ,
			//{ #, #, #} ,			
			//{ #, #, #} ,
			//{ #, #, #} ,
			//{ #, #, #} ,
			//{ #, #, #} ,
			//{ #, #, #} ,			
			//{ #, #, #} ,
			//{ #, #, #} ,
			//{ #, #, #} 
		};
		
		// This spot is reserved for a list of currently generated cars and info
		// LIST SPOT
		
		// Possible angle turns
		// Not quite sure how to manage degrees
		const int turnRight = .45
		const int turnLeft = .45
		const int UTurn	= .90
		const int straight = 0
		
		int numberOfCars;
		
		// Storage for X and Y position
		int xPos;
		int yPos;
		
	};
	
	public:

		// Generator for picking random car
		void getNewCar(){
			//int newCar = (rand()%10)+1;
			//switch(newCar){
				//case '1':
					//type = cars [0][0]
					//length = cars[0][1];
					//desiredSpeed = cars[0][2];
					// Not sure how to declare a spot for storing x and y values for each car.
					
			return newCar;
		};
		
		// Generator for picking random direction
		// May need to set int DESIRE constants to 0,1,2
		void getDirection(){
			//int direction = (rand()%3;
			// include james directions or make own
			return direction;
		};
		
		void updatePos(int, int){
			// This will hold and update positions
		
}
				
