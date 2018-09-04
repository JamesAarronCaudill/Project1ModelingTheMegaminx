#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool runModel = true;


void CPr(int color);
void printSide(int color);
void run();
void baseMegaminx();
int changeSide();
//This struct is going to hold a single side of the Megaminx, there will be 12 objects of this structure.
// Each of the objects will represent one color on the megaminx
// The Colors will always stay the same are not to be changed, this will be used in the main function to help change colors, and one of the movements.
//White will be the main face. The bottom of white will be the adjacent side of blue.
//The bottom of Blue, Yellow, Purple, Green, Red are relative to white, with the bottom of white relative to blue.
// The bottom of lBlue, orange, lgreen, pink, lyellow are relative to grey with the bottom of grey relative to light blue

struct megaminx {
	int centerColor;
	int bottomColor;
	int bottomRightColor;
	int topRightColor;
	int topLeftColor;
	int bottomLeftColor;
	int bottomLeft[3];
	int bottomMiddle[2];
	int bottomRight[3];
	int bottomLeftMiddle[2];
	int bottomRightMiddle[2];
	int topLeft[3];
	int topRight[3];
	int topLeftMiddle[2];
	int topRightMiddle[2];
	int top[3];
} white, blue, yellow, purple, green, red, grey, lBlue, orange, lGreen, pink, lYellow;

/*	This code was provided by Adrian Wyllie
	Feel free to modify it as you see fit.
	Some modification is required to integrate
	with your code. Depending on what your
	code looks like, this may not be usable,
	but I hope it helps!
*/



//White will be the main face. The bottom of white will be the adjacent side of blue.
//The bottom of Blue, Yellow, Purple, Green, Red are relative to white, with the bottom of white relative to blue.
// The bottom of lBlue, orange, lgreen, pink, lyellow are relative to grey with the bottom of grey relative to light blue



//The method of rotation will be chosing a face color, and there will be 12 options
// Front Face Clock Wise / Counter Clock Wise
// Bottom Clock Wise / Counter Clock Wise
// Right Clock Wise / Counter Clock Wise
// Left Clock Wise / Counter Clock Wise
// Top Right CLock Wise / Counter Clock Wise
// Top Left Clock Wise / Counter Clock Wise


// The way I will handle this is there will be 2 functions for movement, and 1 for changing faces.
// Ex.
// Top Left Clock Wise turn when current face is white. I will then switch to the green face with
// 	the bottom relative to white, and then call the clock wise function to rotate clock wise so
//	using a modified version of Adrias printing function I can keep track of all of the pieces and
//	adjust my container as necessary. Then I will change back to the face that I originally called the move on.






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
	megaminx white = {0, 1, 2, 3, 4, 5, {0,5,1}, {0,1}, {0,1,2}, {0,5}, {0,2}, {0,4,5}, {0,2,3}, {0,4}, {0,3}, {0,3,4}};
	megaminx blue = {1, 0, 5, 9 ,10, 2, {1,2,0}, {1,0}, {1,0,5}, {1,2}, {1,5}, {1,9,2}, {1,5,10}, {1,9}, {1,10}, {1,10,9}};
	megaminx yellow = {2, 0, 1, 10 ,11, 3, {2,3,0}, {2,0}, {2,0,1}, {2,3}, {2,1}, {2,8,3}, {2,1,9}, {2,8}, {2,9}, {2,9,8}};
  megaminx purple = {3, 0, 2, 11 ,7, 4, {3,4,0}, {3,0}, {3,0,2}, {3,4}, {3,2}, {3,7,4}, {3,2,8}, {3,7}, {3,8}, {3,8,7}};
	megaminx green = {4, 0, 3, 7 ,8, 5, {4,5,0}, {4,0}, {4,0,3}, {4,5}, {4,3}, {4,11,5}, {4,3,7}, {4,11}, {4,7}, {4,7,11}};
	megaminx red = {5, 0, 4, 8, 9, 1, {5,1,0}, {5,0}, {5,0,4}, {5,1}, {5,4}, {5,10,1}, {5,4,11}, {5,10}, {5,11}, {5,11,10}};
  megaminx grey = {6, 7, 8, 9, 10, 11, {6,11,7}, {6,7}, {6,7,8}, {6,11}, {6,8}, {6,10,11}, {6,8,9}, {6,10}, {6,9}, {6,9,10}};
	megaminx lBlue = {7, 6, 11, 4, 3, 8, {7,8,6}, {7,6}, {7,6,11}, {7,8}, {7,11}, {7,3,8}, {7,11,4}, {7,3}, {7,4}, {7,4,3}};
	megaminx orange = {8, 6, 7, 3, 2, 9, {8,9,6}, {8,6}, {8,6,7}, {8,9}, {8,7}, {8,2,9}, {8,7,3}, {8,2}, {8,3}, {8,3,2}};
  megaminx lGreen = {9, 6, 8, 2, 1, 10, {9,10,6}, {9,6}, {9,6,8}, {9,10}, {9,8}, {9,1,10}, {9,8,2}, {9,1}, {9,2}, {9,2,1}};
  megaminx pink = {10, 6, 9, 1, 5, 11, {10,11,6}, {10,6}, {10,6,9}, {10,11}, {10,8}, {10,5,11}, {10,9,1}, {10,5}, {10,1}, {10,1,5}};
	megaminx lYellow = {11, 6, 10, 5, 4, 7, {11,7,6}, {11,6}, {11,6,10}, {11,7}, {11,10}, {11,4,7}, {11,10,5}, {11,4}, {11,5}, {11,5,4}};

}
/*
void clockWise(int faceColor) {

}

void counterClockWise(int faceColor) {

}
void randomizer(int randomMoves)
{
	cout << "Welcome to the randomizer! You have " << randomMoves << " moves to make.";
}
*/

void run(){
	//Printing the base Megaminx using the white face
	printSide(0);

	while (runModel == true) {
		//int side = changeSide();
		//printSide(side);
	}

//TODO: This needs to be updated after the test run has been established that i can correctly change sides.
/*
	int randomMoves;

	cout << "This is the base Megaminx in a solved state." << endl;
	cout << "Please enter a number of moves to randomize the Megaminx.: ";
	cin >> randomMoves;

	if(cin.good()){
		randomizer(randomMoves)
	}
	if(!cin.good()){
		cin.clear()
		cin.ignore(INT_MAX, '\n')
		cout << "That was not a number, we will choose a number between 5 and 15 for you." << endl;
		randomMoves = rand() % (16 - 10) + 5
		randomizer(randomMoves)
	}
	*/
}
/*
int changeSide(){
	int side;
	//cout << "Change the sides of the MegaMinx: ";
	//cin >> side;
	return side;
}
*/
void printSide(int color) {
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
						//Light Yellow will be Represented with int == 8
						case 8 : colorName = lYellow; break;
						//Pink will be Represented with int == 9
						case 9 : colorName = pink; break;
						//Light Green will be Represented with int == 10
						case 10 : colorName = lGreen; break;
						//Orange will be Represented with int == 11
						case 11 : colorName = orange; break;
				}

	//int printE[5]; //contains the colours of the five edges in COUNTERCLOCKWISE order
	//int printC[5]; //contains the colours of the five corners in COUNTERCLOCKWISE order
	//int printS[5]; //contains the colours of the five adjacent sides in COUNTERCLOCKWISE order
	//int center; //the colour of the center of the side to be printed

	int printE[5] = {colorName.bottomMiddle[0], colorName.bottomRightMiddle[0], colorName.topRightMiddle[0], colorName.topLeftMiddle[0], colorName.bottomLeftMiddle[0]};
	int printC[5] = {colorName.bottomRight[0], colorName.topRight[0], colorName.top[0], colorName.topLeft[0], colorName.bottomLeft[0]};
	int printS[5] = {colorName.bottomColor, colorName.bottomRightColor, colorName.topRightColor, colorName.topLeftColor, colorName.bottomLeftColor};
	int center = colorName.centerColor;

	/*
	This is where you need to populate the three arrays abouve with the correct colours
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

	//This next block of code prints the side in the same layout as the example output at the
	//top. Each line has several lines of code on it. Each line alternates between printing
	//whitespace and calling a helper function to print the colour. Each line ends with
	//cout << endl; which moves on to the next line. This is not very clean, but it works.
	/*
	cout << " "; CPr(printS[3]); cout << "    "; CPr(printC[2]); cout << "    "; CPr(printS[2]); cout << endl;
        cout << "    "; CPr(printE[3]); cout << "   "; CPr(printE[2]); cout << endl;
        cout << "  "; CPr(printC[3]); cout << "       "; CPr(printC[1]); cout << endl;
        CPr(printS[4]); cout << " "; CPr(printE[4]); cout << "   "; CPr(center); cout << "   "; CPr(printE[1]); cout << " "; CPr(printS[1]); cout << endl;
        cout << "  "; CPr(printC[4]); cout << "   "; CPr(printE[0]); cout << "   "; CPr(printC[0]); cout << endl;
        cout << "      "; CPr(printS[0]); cout << endl << endl;
        return;
				*/
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
		  			case 0 : cout << "\033[1;38;5;255mW\033[0m"; break;
						//Blue will be Represented with int == 1
						case 1 : cout << "\033[1;38;5;21mB\033[0m"; break;
						//Yellow will be Represented with int == 2
		        case 2 : cout << "\033[1;38;5;226mY\033[0m"; break;
						//Purple will be Represented with int == 3
		        case 3 : cout << "\033[1;38;5;90mP\033[0m"; break;
						//Green will be Represented with int == 4
		        case 4 : cout << "\033[1;38;5;34mG\033[0m"; break;
						//Red will be Represented with int == 5
		        case 5 : cout << "\033[1;38;5;196mR\033[0m"; break;
						//Grey will be Represented with int == 6
		        case 6 : cout << "\033[1;38;5;243mE\033[0m"; break;
						//Light Blue will be Represented with int == 7
		        case 7 : cout << "\033[1;38;5;33mU\033[0m"; break;
						//Light Yellow will be Represented with int == 8
		        case 8 : cout << "\033[1;38;5;230mL\033[0m"; break;
						//Pink will be Represented with int == 9
		        case 9 : cout << "\033[1;38;5;213mK\033[0m"; break;
						//Light Green will be Represented with int == 10
		        case 10 : cout << "\033[1;38;5;10mN\033[0m"; break;
						//Orange will be Represented with int == 11
		        case 11 : cout << "\033[1;38;5;208mO\033[0m"; break;
        }
        return;
}


int main(){
	//cout << "Hello! Welcome to the Megaminx Model." << endl;
	//cout << "Please be patient while be build your Megaminx" << endl;
	//cout << "..." << endl;

	baseMegaminx();

	//cout << "Done!" << endl;
	//cout << "This is where you will make your moves." << endl;
	//run();
}
