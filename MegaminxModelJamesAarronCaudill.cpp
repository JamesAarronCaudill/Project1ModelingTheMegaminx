//Run This using `g++ -std=c++11 MegaminxModelJamesAarronCaudill.cpp`
//./a.out
//Author: James Aarron Caudill
//Due Date: September 4th, 2018
//Github Link: https://github.com/JamesAarronCaudill/Project1ModelingTheMegaminx.git
//Note: the GUI Code's creator is Adrian Wyllie. I haved tried to document
//	every area in which the code was borrowed and or modified.

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

bool runModel = true;


void CPr(int color);
void printSide(int color);
void run();
void baseMegaminx();
int changeSide();


/*
This struct is going to hold a single side of the Megaminx, there will be 12 objects of this structure.
Each of the objects will represent one face on the megaminx
The Colors will always stay the same are not to be changed, this will be used in the main function to help change colors, and one of the movements.
White will be the main face. The bottom of white will be the adjacent side of blue.
The bottom of Blue, Yellow, Purple, Green, Red are relative to white, with the bottom of white relative to blue.
The bottom of lBlue, orange, lgreen, pink, lyellow are relative to grey with the bottom of grey relative to light blue
*/
struct megaminx {
	int centerColor;
	int bottomColor;
	int bottomRightColor;
	int topRightColor;
	int topLeftColor;
	int bottomLeftColor;
	int bottomLeft;
	int bottomMiddle;
	int bottomRight;
	int bottomLeftMiddle;
	int bottomRightMiddle;
	int topLeft;
	int topRight;
	int topLeftMiddle;
	int topRightMiddle;
	int top;
} white, blue, yellow, purple, green, red, grey, lBlue, orange, lGreen, pink, lYellow;


int numberOutOfPlace(megaminx solvedWhite, megaminx solvedBlue, megaminx solvedYellow, megaminx solvedPurple, megaminx solvedGreen, megaminx solvedRed, megaminx solvedGrey, megaminx solvedLBlue, megaminx solvedLYellow, megaminx solvedPink, megaminx solvedLGreen, megaminx solvedOrange);
// The way I will handle this is there will be 2 functions for movement, and 1 for changing faces.
// Ex.
// Top Left Clock Wise turn when current face is white. I will then switch to the green face with
// 	the bottom relative to white, and then call the clock wise function to rotate clock wise so
//	using a modified version of Adrias printing function I can keep track of all of the pieces and
//	adjust my container as necessary. Then I will change back to the face that I originally called the move on.
//  currently the change face function is not merged in as it is not necessary for this implementation.





//NOTE: THIS GUI HAS BEEN ADOPTED AND MODIFIED FROM ADRIAN WYLLIE.
//  Example output:
//       3   2   2
//         3   2
//       3       1
//    4  4   s   1  1
//       4   0   0
//           0

// the above numbers relate to how the arrays below will be ordered.
// this print shows the center of a side, the colours of the edges and
// corners around the side, and the colours of the five sides next
// to that side. The five sides are presented to act as a key for
// orienting the sides when comparing with a physical model


//This will build the base Megaminx. This will be used to initilize the Megaminx to a "Solved State"
//There is probably a better way to do this however this is functional.
void baseMegaminx() {
	white = {0,1,2,3,4,5,0,0,0,0,0,0,0,0,0,0};
	blue = {1,0,5,9,10,2,1,1,1,1,1,1,1,1,1,1};
	yellow = {2,0,1,10,11,3,2,2,2,2,2,2,2,2,2,2};
	purple = {3,0,2,11,7,4,3,3,3,3,3,3,3,3,3,3};
	green = {4,0,3,7,8,5,4,4,4,4,4,4,4,4,4,4};
	red = {5,0,4,8,9,1,5,5,5,5,5,5,5,5,5,5};
  grey = {6,7,8,9,10,11,6,6,6,6,6,6,6,6,6,6};
	lBlue = {7,6,11,4,3,8,7,7,7,7,7,7,7,7,7,7};
	orange = {8,6,7,3,2,9,8,8,8,8,8,8,8,8,8,8};
  lGreen = {9,6,8,2,1,10,9,9,9,9,9,9,9,9,9,9};
  pink = {10,6,9,1,5,11,10,10,10,10,10,10,10,10,10,10};
	lYellow = {11,6,10,5,4,7,11,11,11,11,11,11,11,11,11,11};
	return;

}


//This is a pretty messy form of the clockwise function. I am almost sure there is a way to elemenate code.
//However the best method I had found to do this is the hard code the changes.
void clockWise(int color) {
	megaminx colorName;
	switch(color) {
						//White will be Represented with int == 0
						case 0 : colorName = white; break;
						//Blue will be Represented with int == 1
						case 1 : colorName = blue; break;
						//Yellow will be Represented with int == 2
						case 2 : colorName = yellow; break;
						//Purple will be Represented with int == 3
						case 3 : colorName = purple; break;
						//Green will be Represented with int == 4
						case 4 : colorName = green; break;
						//Red will be Represented with int == 5
						case 5 : colorName = red; break;
						//Grey will be Represented with int == 6
						case 6 : colorName = grey; break;
						//Light Blue will be Represented with int == 7
						case 7 : colorName = lBlue; break;
						//Orange will be Represented with int == 8
						case 8 : colorName = orange; break;
						//Light Green will be Represented with int == 9
						case 9 : colorName = lGreen; break;
						//Pink will be Represented with int == 10
						case 10 : colorName = pink; break;
						//Light Yellow will be Represented with int == 11
						case 11 : colorName = lYellow; break;

				}
	megaminx copyWhite = white;
	megaminx copyBlue = blue;
	megaminx copyYellow = yellow;
	megaminx copyPurple = purple;
	megaminx copyGreen = green;
	megaminx copyRed = red;
	megaminx copyGrey = grey;
	megaminx copyLBlue = lBlue;
	megaminx copyLYellow = lYellow;
	megaminx copyPink = pink;
	megaminx copyLGreen = lGreen;
	megaminx copyOrange = orange;

		//This will then assign the face back after it has been adjusted
		switch(colorName.centerColor) {
					//White will be Reresented with int == 0
					case 0 :
						blue.bottomLeft = copyYellow.bottomLeft;
						blue.bottomMiddle = copyYellow.bottomMiddle;
						blue.bottomRight = copyYellow.bottomRight;
						red.bottomLeft = copyBlue.bottomLeft;
						red.bottomMiddle = copyBlue.bottomMiddle;
						red.bottomRight = copyBlue.bottomRight;
						green.bottomLeft = copyRed.bottomLeft;
						green.bottomMiddle = copyRed.bottomMiddle;
						green.bottomRight = copyRed.bottomRight;
						purple.bottomLeft = copyGreen.bottomLeft;
						purple.bottomMiddle = copyGreen.bottomMiddle;
						purple.bottomRight = copyGreen.bottomRight;
						yellow.bottomLeft = copyPurple.bottomLeft;
						yellow.bottomMiddle = copyPurple.bottomMiddle;
						yellow.bottomRight = copyPurple.bottomRight;
						break;
					//Blue will be Represented with int == 1
					case 1 :
						white.bottomLeft = copyRed.topLeft;
						white.bottomMiddle = copyRed.bottomLeftMiddle;
						white.bottomRight = copyRed.bottomLeft;
						yellow.bottomRight = copyWhite.bottomLeft;
						yellow.bottomRightMiddle = copyWhite.bottomMiddle;
						yellow.topRight = copyWhite.bottomRight;
						lGreen.top = copyYellow.bottomRight;
						lGreen.topLeftMiddle = copyYellow.bottomRightMiddle;
						lGreen.topLeft = copyYellow.topRight;
						pink.topRight = copyLGreen.top;
						pink.topRightMiddle = copyLGreen.topLeftMiddle;
						pink.top = copyLGreen.topLeft;
						red.bottomLeft = copyPink.top;
						red.bottomLeftMiddle = copyPink.topRightMiddle;
						red.topLeft = copyPink.topRight;
						break;
					//Yellow will be Represented with int == 2
					case 2 :
						white.bottomRight = copyBlue.topLeft;
						white.bottomRightMiddle = copyBlue.bottomLeftMiddle;
						white.topRight = copyBlue.bottomLeft;
						purple.bottomRight = copyWhite.bottomRight;
						purple.bottomRightMiddle = copyWhite.bottomRightMiddle;
						purple.topRight = copyWhite.topRight;
						orange.top = copyPurple.bottomRight;
						orange.topLeftMiddle = copyPurple.bottomRightMiddle;
						orange.topLeft = copyPurple.topRight;
						lGreen.topRight = copyOrange.top;
						lGreen.topRightMiddle = copyOrange.topLeftMiddle;
						lGreen.top = copyOrange.topLeft;
						blue.bottomLeft = copyLGreen.top;
						blue.bottomLeftMiddle = copyLGreen.topRightMiddle;
						blue.topLeft = copyLGreen.topRight;
						break;
					//Purple will be Represented with int == 3
					case 3 :
						white.topRight = copyYellow.topLeft;
						white.topRightMiddle = copyYellow.bottomLeftMiddle;
						white.top = copyYellow.bottomLeft;
						green.bottomRight = copyWhite.topRight;
						green.bottomRightMiddle = copyWhite.topRightMiddle;
						green.topRight = copyWhite.top;
						lBlue.top = copyGreen.bottomRight;
						lBlue.topLeftMiddle = copyGreen.bottomRightMiddle;
						lBlue.topLeft = copyGreen.topRight;
						orange.top = copyLBlue.topLeft;
						orange.topRightMiddle = copyLBlue.topLeftMiddle;
						orange.topRight = copyLBlue.top;
						yellow.topLeft = copyOrange.topRight;
						yellow.bottomLeftMiddle = copyOrange.topRightMiddle;
						yellow.bottomLeft = copyOrange.top;
						break;
					//Green will be Represented with int == 4
					case 4 :
						white.top = copyPurple.topLeft;
						white.topLeftMiddle = copyPurple.bottomLeftMiddle;
						white.topLeft = copyPurple.bottomLeft;
						red.bottomRight = copyWhite.top;
						red.bottomRightMiddle = copyWhite.topLeftMiddle;
						red.topRight = copyWhite.topLeft;
						lYellow.top = copyRed.bottomRight;
						lYellow.topLeftMiddle = copyRed.bottomRightMiddle;
						lYellow.topLeft = copyRed.topRight;
						lBlue.topRight = copyLYellow.top;
						lBlue.topRightMiddle = copyLYellow.topLeftMiddle;
						lBlue.top = copyLYellow.topLeft;
						purple.topLeft = copyLBlue.topRight;
						purple.bottomLeftMiddle = copyLBlue.topRightMiddle;
						purple.bottomLeft = copyLBlue.top;
						break;
					//Red will be Represented with int == 5
					case 5 :
						white.topLeft = copyGreen.topLeft;
						white.bottomLeftMiddle = copyGreen.bottomLeftMiddle;
						white.bottomLeft = copyGreen.bottomLeft;
						blue.bottomRight = copyWhite.topLeft;
						blue.bottomRightMiddle = copyWhite.bottomLeftMiddle;
						blue.topRight = copyWhite.bottomLeft;
						pink.top = copyBlue.bottomRight;
						pink.topLeftMiddle = copyBlue.bottomRightMiddle;
						pink.topLeft = copyBlue.topRight;
						lYellow.topRight = copyPink.top;
						lYellow.topRightMiddle = copyPink.topLeftMiddle;
						lYellow.top = copyPink.topLeft;
						green.topLeft = copyLYellow.topRight;
						green.bottomLeftMiddle = copyLYellow.topRightMiddle;
						green.bottomLeft = copyLYellow.top;
						break;
					//Grey will be Represented with int == 6
					case 6 :
						lBlue.bottomLeft = copyLYellow.bottomLeft;
						lBlue.bottomMiddle = copyLYellow.bottomMiddle;
						lBlue.bottomRight = copyLYellow.bottomRight;
						orange.bottomLeft = copyLBlue.bottomLeft;
						orange.bottomMiddle = copyLBlue.bottomMiddle;
						orange.bottomRight = copyLBlue.bottomRight;
						lGreen.bottomLeft = copyOrange.bottomLeft;
						lGreen.bottomMiddle = copyOrange.bottomMiddle;
						lGreen.bottomRight = copyOrange.bottomRight;
						pink.bottomLeft = copyLGreen.bottomLeft;
						pink.bottomMiddle = copyLGreen.bottomMiddle;
						pink.bottomRight = copyLGreen.bottomRight;
						lYellow.bottomLeft = copyPink.bottomLeft;
						lYellow.bottomMiddle = copyPink.bottomMiddle;
						lYellow.bottomRight = copyPink.bottomRight;
						break;
					//Light Blue will be Represented with int == 7
					case 7 :
						grey.bottomLeft = copyLYellow.topLeft;
						grey.bottomMiddle = copyLYellow.bottomLeftMiddle;
						grey.bottomRight = copyLYellow.bottomLeft;
						orange.bottomRight = copyGrey.bottomLeft;
						orange.bottomRightMiddle = copyGrey.bottomMiddle;
						orange.topRight = copyGrey.bottomRight;
						purple.top = copyOrange.bottomRight;
						purple.topLeftMiddle = copyOrange.bottomRightMiddle;
						purple.topLeft = copyOrange.topRight;
						green.topRight = copyPurple.top;
						green.topRightMiddle = copyPurple.topLeftMiddle;
						green.top = copyPurple.topLeft;
						lYellow.bottomLeft = copyGreen.top;
						lYellow.bottomLeftMiddle = copyGreen.topRightMiddle;
						lYellow.topLeft = copyGreen.topRight;
						break;
					//Orange will be Represented with int == 8
					case 8 :
						grey.bottomRight = copyLBlue.topLeft;
						grey.bottomRightMiddle = copyLBlue.bottomLeftMiddle;
						grey.topRight = copyLBlue.bottomLeft;
						lGreen.bottomRight = copyGrey.bottomRight;
						lGreen.bottomRightMiddle = copyGrey.bottomRightMiddle;
						lGreen.topRight = copyGrey.topRight;
						yellow.top = copyLGreen.bottomRight;
						yellow.topLeftMiddle = copyLGreen.bottomRightMiddle;
						yellow.topLeft = copyLGreen.topRight;
						purple.topRight = copyYellow.top;
						purple.topRightMiddle = copyYellow.topLeftMiddle;
						purple.top = copyYellow.topLeft;
						lBlue.bottomLeft = copyPurple.top;
						lBlue.bottomLeftMiddle = copyPurple.topRightMiddle;
						lBlue.topLeft = copyPurple.topRight;
						break;
					//Pink will be Represented with int == 9
					case 9 :
						grey.top = copyLGreen.topLeft;
						grey.topLeftMiddle = copyLGreen.bottomLeftMiddle;
						grey.topLeft = copyLGreen.bottomLeft;
						lYellow.bottomRight = copyGrey.top;
						lYellow.bottomRightMiddle = copyGrey.topLeftMiddle;
						lYellow.topRight = copyGrey.topLeft;
						red.top = copyLYellow.bottomRight;
						red.topLeftMiddle = copyLYellow.bottomRightMiddle;
						red.topLeft = copyLYellow.topRight;
						blue.topRight = copyRed.top;
						blue.topRightMiddle = copyRed.topLeftMiddle;
						blue.top = copyRed.topLeft;
						lGreen.topLeft = copyBlue.topRight;
						lGreen.bottomLeftMiddle = copyBlue.topRightMiddle;
						lGreen.bottomLeft = copyBlue.top;
						break;
					//Light Green will be Represented with int == 10
					case 10 :
						grey.topRight = copyOrange.bottomLeft;
						grey.topRightMiddle = copyOrange.bottomLeftMiddle;
						grey.top = copyOrange.bottomLeft;
						pink.bottomRight = copyGrey.topRight;
						pink.bottomRightMiddle = copyGrey.topRightMiddle;
						pink.topRight = copyGrey.top;
						blue.top = copyPink.bottomRight;
						blue.topLeftMiddle = copyPink.bottomRightMiddle;
						blue.topLeft = copyPink.topRight;
						yellow.top = copyBlue.topLeft;
						yellow.topRightMiddle = copyBlue.topLeftMiddle;
						yellow.topRight = copyBlue.top;
						orange.topLeft = copyYellow.topRight;
						orange.bottomLeftMiddle = copyYellow.topRightMiddle;
						orange.bottomLeft = copyYellow.top;
						break;
					//Light Yellow will be Represented with int == 11
					case 11 :
						grey.topLeft = copyPink.topLeft;
						grey.bottomLeftMiddle = copyPink.bottomLeftMiddle;
						grey.bottomLeft = copyPink.bottomLeft;
						lBlue.bottomRight = copyGrey.topLeft;
						lBlue.bottomRightMiddle = copyGrey.bottomLeftMiddle;
						lBlue.topRight = copyGrey.bottomLeft;
						lGreen.top = copyLBlue.bottomRight;
						lGreen.topLeftMiddle = copyLBlue.bottomRightMiddle;
						lGreen.topLeft = copyLBlue.topRight;
						red.topRight = copyLGreen.top;
						red.topRightMiddle = copyLGreen.topLeftMiddle;
						red.top = copyLGreen.topLeft;
						pink.topLeft = copyRed.topRight;
						pink.bottomLeftMiddle = copyRed.topRightMiddle;
						pink.bottomLeft = copyRed.top;
						break;
			}

}

//A very simple way to not reproduce code.
//A counter clockwise turn is the exact same as a clockwise turn 4 times.
//There is no sense in doing the exact reverse of the clockwise function
void counterClockWise(int color) {
	for(int i = 0; i < 4; i++){
		clockWise(color);
	}
}

//For my randomizer I decided to psuedo randomly choose a face by seeding random with time, choosing a face from 0-11,
//from the face choosing 1 of 12 directions to go, so this way there is a greater variance in my psuedo randomizer.
void randomizer(int randomMoves)
{
	srand (time(NULL));
	cout << "Welcome to the randomizer! You have " << randomMoves << " moves to make.";

	for(int i = 0; i < randomMoves; i++){
		int faceColor = rand() % 12;

		megaminx colorName;
		switch(faceColor) {
							//White will be Represented with int == 0
							case 0 : colorName = white; break;
							//Blue will be Represented with int == 1
							case 1 : colorName = blue; break;
							//Yellow will be Represented with int == 2
							case 2 : colorName = yellow; break;
							//Purple will be Represented with int == 3
							case 3 : colorName = purple; break;
							//Green will be Represented with int == 4
							case 4 : colorName = green; break;
							//Red will be Represented with int == 5
							case 5 : colorName = red; break;
							//Grey will be Represented with int == 6
							case 6 : colorName = grey; break;
							//Light Blue will be Represented with int == 7
							case 7 : colorName = lBlue; break;
							//Orange will be Represented with int == 8
							case 8 : colorName = orange; break;
							//Light Green will be Represented with int == 9
							case 9 : colorName = lGreen; break;
							//Pink will be Represented with int == 10
							case 10 : colorName = pink; break;
							//Light Yellow will be Represented with int == 11
							case 11 : colorName = lYellow; break;

					}

		//The method of rotation will be chosing a face color, and there will be 12 options
		// Front Face Clock Wise 0/1 Counter Clock Wise
		// Bottom Clock Wise 2/3 Counter Clock Wise
		// Right Clock Wise 4/5 Counter Clock Wise
		// Left Clock Wise 6/7 Counter Clock Wise
		// Top Right CLock Wise 8/9 Counter Clock Wise
		// Top Left Clock Wise 10/11 Counter Clock Wise
		int direction = rand() % 12;
		switch(direction) {
							//White will be Represented with int == 0
							case 0 : clockWise(colorName.centerColor); break;
							//Blue will be Represented with int == 1
							case 1 : counterClockWise(colorName.centerColor); break;
							//Yellow will be Represented with int == 2
							case 2 : clockWise(colorName.bottomColor); break;
							//Purple will be Represented with int == 3
							case 3 : counterClockWise(colorName.bottomColor); break;
							//Green will be Represented with int == 4
							case 4 : clockWise(colorName.bottomRightColor); break;
							//Red will be Represented with int == 5
							case 5 : counterClockWise(colorName.bottomRightColor); break;
							//Grey will be Represented with int == 6
							case 6 : clockWise(colorName.bottomLeftColor); break;
							//Light Blue will be Represented with int == 7
							case 7 : counterClockWise(colorName.bottomLeftColor); break;
							//Orange will be Represented with int == 8
							case 8 : clockWise(colorName.topRightColor); break;
							//Light Green will be Represented with int == 9
							case 9 : counterClockWise(colorName.topRightColor); break;
							//Pink will be Represented with int == 10
							case 10 : clockWise(colorName.topLeftColor); break;
							//Light Yellow will be Represented with int == 11
							case 11 : counterClockWise(colorName.topLeftColor); break;
					}


	}
}


//This runs the program, starts with the base megaminx, then randomizes it, then prints it out.
void run(){
	//Storing the Solved Base Megaminx to compare to later.
	megaminx solvedWhite = white;
	megaminx solvedBlue = blue;
	megaminx solvedYellow = yellow;
	megaminx solvedPurple = purple;
	megaminx solvedGreen = green;
	megaminx solvedRed = red;
	megaminx solvedGrey = grey;
	megaminx solvedLBlue = lBlue;
	megaminx solvedLYellow = lYellow;
	megaminx solvedPink = pink;
	megaminx solvedLGreen = lGreen;
	megaminx solvedOrange = orange;


	//Initilizing random time based on the current time
	srand (time(NULL));

	//Printing the base Megaminx
	printSide(0);
	printSide(1);
	printSide(2);
	printSide(3);
	printSide(4);
	printSide(5);
	printSide(6);
	printSide(7);
	printSide(8);
	printSide(9);
	printSide(10);
	printSide(11);

  //This is where the user will enter a numver of random moves.
	int randomMoves;
	cout << "Please enter a number to randomize the Megaminx: ";
	cin >> randomMoves;
	//If the input is good it will call the randomizer using the numver the user enterned.
	if(cin.good()){
		randomizer(randomMoves);
	}
	//If not it will choose a number between 5-15
	if(!cin.good()){
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "That was not a number, we will choose a number between 5 and 15 for you." << endl;
		randomMoves = rand() % (16 - 10) + 5;
		randomizer(randomMoves);
	}

	//Prints the entire megaminx after randomization
	cout << "Here is the megaminx randomized" << endl;
	printSide(0);
	printSide(1);
	printSide(2);
	printSide(3);
	printSide(4);
	printSide(5);
	printSide(6);
	printSide(7);
	printSide(8);
	printSide(9);
	printSide(10);
	printSide(11);

	float outOfPlace = numberOutOfPlace(solvedWhite, solvedBlue, solvedYellow, solvedPurple, solvedGreen, solvedRed, solvedGrey, solvedLBlue, solvedLYellow, solvedPink, solvedLGreen, solvedOrange);

	int heuristicValue = ceil(outOfPlace/25);

	cout << endl << "Heuristic Value: " << heuristicValue << endl;

}

//Used for sanity Checking
int changeSide(){
	int side;
	cout << "Please choose a side to change to: ";
	cin >> side;
	return side;
}

int numberOutOfPlace(megaminx solvedWhite, megaminx solvedBlue, megaminx solvedYellow, megaminx solvedPurple, megaminx solvedGreen, megaminx solvedRed, megaminx solvedGrey, megaminx solvedLBlue, megaminx solvedLYellow, megaminx solvedPink, megaminx solvedLGreen, megaminx solvedOrange){

	 float outOfPlace = 0.0;

	 for(int i = 0; i < 12; i++){
		 megaminx colorName;
		 megaminx solvedColorName;
		 switch(i) {
	 						//White will be Represented with int == 0
	 						case 0 : colorName = white; solvedColorName = solvedWhite; break;
	 						//Blue will be Represented with int == 1
	 						case 1 : colorName = blue; solvedColorName = solvedBlue; break;
	 						//Yellow will be Represented with int == 2
	 						case 2 : colorName = yellow; solvedColorName = solvedYellow; break;
	 						//Purple will be Represented with int == 3
	 						case 3 : colorName = purple; solvedColorName = solvedPurple; break;
	 						//Green will be Represented with int == 4
	 						case 4 : colorName = green; solvedColorName = solvedGreen; break;
	 						//Red will be Represented with int == 5
	 						case 5 : colorName = red; solvedColorName = solvedRed; break;
	 						//Grey will be Represented with int == 6
	 						case 6 : colorName = grey; solvedColorName = solvedGrey; break;
	 						//Light Blue will be Represented with int == 7
	 						case 7 : colorName = lBlue; solvedColorName = solvedLBlue; break;
	 						//Orange will be Represented with int == 8
	 						case 8 : colorName = orange; solvedColorName = solvedOrange; break;
	 						//Light Green will be Represented with int == 9
	 						case 9 : colorName = lGreen; solvedColorName = solvedLGreen; break;
	 						//Pink will be Represented with int == 10
	 						case 10 : colorName = pink; solvedColorName = solvedPink; break;
	 						//Light Yellow will be Represented with int == 11
	 						case 11 : colorName = lYellow; solvedColorName = solvedLYellow; break;
	 				}
	  	if(colorName.centerColor == solvedColorName.centerColor){
				if(colorName.bottomMiddle != solvedColorName.bottomMiddle)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.bottomLeft != solvedColorName.bottomLeft)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.bottomRight != solvedColorName.bottomRight)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.bottomLeftMiddle != solvedColorName.bottomLeftMiddle)
				{
				  outOfPlace = outOfPlace + 1;
				}
				if(colorName.bottomRightMiddle != solvedColorName.bottomRightMiddle)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.topLeft != solvedColorName.topLeft)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.topRight != solvedColorName.topRight)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.topLeftMiddle != solvedColorName.topLeftMiddle)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.topRightMiddle != solvedColorName.topRightMiddle)
				{
					outOfPlace = outOfPlace + 1;
				}
				if(colorName.top != solvedColorName.top)
				{
					outOfPlace = outOfPlace + 1;
				}
				cout << outOfPlace << endl;
			}
	 }
	 cout << outOfPlace << endl;
	 return outOfPlace;
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*
		This code was provided by Adrian Wyllie. This has been modified by
				James Aarron Caudill to fit my implementation.
*/
void printSide(int color) {
	/*This is going to bring in the color in integer form, then it will select the side from the struct*/
	megaminx colorName;
	switch(color) {
						//White will be Represented with int == 0
						case 0 : colorName = white; break;
						//Blue will be Represented with int == 1
						case 1 : colorName = blue; break;
						//Yellow will be Represented with int == 2
						case 2 : colorName = yellow; break;
						//Purple will be Represented with int == 3
						case 3 : colorName = purple; break;
						//Green will be Represented with int == 4
						case 4 : colorName = green; break;
						//Red will be Represented with int == 5
						case 5 : colorName = red; break;
						//Grey will be Represented with int == 6
						case 6 : colorName = grey; break;
						//Light Blue will be Represented with int == 7
						case 7 : colorName = lBlue; break;
						//Orange will be Represented with int == 8
						case 8 : colorName = orange; break;
						//Light Green will be Represented with int == 9
						case 9 : colorName = lGreen; break;
						//Pink will be Represented with int == 10
						case 10 : colorName = pink; break;
						//Light Yellow will be Represented with int == 11
						case 11 : colorName = lYellow; break;

				}

		/*
				This is where you need to populate the three arrays with the correct colours
				In a solved puzzle printing the white side, the printE and printC arrays need to contain
				5 of whatever int you use for the colour white, and the printS array needs to contain the
				ints for the five adjacent sides' center colours. Be very careful here to preserve
				the relation of the arrays like shown in the example output

				the first int of the printE array needs to correspond to a colour from the edge between the
				side being printed and the side represented by the first int of printS. The first int of
				printC is the colour of the corner between the printed side and the sides of the first two
				ints in the printS array

				make sure to grab the colours from the edges and corners that correspond to the side being
				printed.
		*/

	/*This is building the Megaminx using the struct and picking the correct elements out*/
	int printE[5] = {colorName.bottomMiddle, colorName.bottomRightMiddle, colorName.topRightMiddle, colorName.topLeftMiddle, colorName.bottomLeftMiddle};
	int printC[5] = {colorName.bottomRight, colorName.topRight, colorName.top, colorName.topLeft, colorName.bottomLeft};
	int printS[5] = {colorName.bottomColor, colorName.bottomRightColor, colorName.topRightColor, colorName.topLeftColor, colorName.bottomLeftColor};
	int center = colorName.centerColor;

	//This next block of code prints the side in the same layout as the example output at the
	//top. Each line has several lines of code on it. Each line alternates between printing
	//whitespace and calling a helper function to print the colour. Each line ends with
	//cout << endl; which moves on to the next line. This is not very clean, but it works.

				cout << " "; CPr(printS[3]); cout << "    "; CPr(printC[2]); cout << "    "; CPr(printS[2]); cout << endl;
        cout << "    "; CPr(printE[3]); cout << "   "; CPr(printE[2]); cout << endl;
        cout << "  "; CPr(printC[3]); cout << "       "; CPr(printC[1]); cout << endl;
        CPr(printS[4]); cout << " "; CPr(printE[4]); cout << "   "; CPr(center); cout << "   "; CPr(printE[1]); cout << " "; CPr(printS[1]); cout << endl;
        cout << "  "; CPr(printC[4]); cout << "   "; CPr(printE[0]); cout << "   "; CPr(printC[0]); cout << endl;
        cout << "      "; CPr(printS[0]); cout << endl << endl;
        return;

}

//This next function is a helper function that prints a specific colour when given an integer
//This prints IN colour because I can ANSI Escape codes and now you can too!
//The \033[..m is the escape code. 1 is bold, 38;5;.. selects a colour in 256 colour mode,
//0 resets text attributes.
//More info at en.wikipedia.org/wiki/ANSI_escape_code
//You need to replace each colour's name with the number you use for the colour, or dont, if
//you used enum with these colour names
void CPr(int color) {
	switch(color) {
						//White will be Represented with int == 0
		  			case 0: cout << "\033[1;38;5;255mW\033[0m"; break;
						//Blue will be Represented with int == 1
						case 1: cout << "\033[1;38;5;21mB\033[0m"; break;
						//Yellow will be Represented with int == 2
		        case 2: cout << "\033[1;38;5;226mY\033[0m"; break;
						//Purple will be Represented with int == 3
		        case 3: cout << "\033[1;38;5;90mP\033[0m"; break;
						//Green will be Represented with int == 4
		        case 4: cout << "\033[1;38;5;34mG\033[0m"; break;
						//Red will be Represented with int == 5
		        case 5: cout << "\033[1;38;5;196mR\033[0m"; break;
						//Grey will be Represented with int == 6
		        case 6: cout << "\033[1;38;5;243mE\033[0m"; break;
						//Light Blue will be Represented with int == 7
		        case 7: cout << "\033[1;38;5;33mU\033[0m"; break;
						//Orange will be Represented with int == 11
		        case 8: cout << "\033[1;38;5;208mO\033[0m"; break;
						//Light Green will be Represented with int == 9
		        case 9: cout << "\033[1;38;5;10mN\033[0m"; break;
						//Pink will be Represented with int == 10
		        case 10: cout << "\033[1;38;5;213mK\033[0m"; break;
						//Light Yellow will be Represented with int == 11
		        case 11: cout << "\033[1;38;5;230mL\033[0m"; break;
        }
        return;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


int main(){
	cout << "Hello! Welcome to the Megaminx Model." << endl;
	cout << "Please be patient while be build your Megaminx" << endl;
	cout << "..." << endl;

	baseMegaminx();

	cout << "Done!" << endl;
	cout << "This is where you will make your moves." << endl;
	run();
}
