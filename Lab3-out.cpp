// Jordan Maxwell
// Lab 3-OUT
// This program implements a game named Bug Zapper 


#include <iostream>
#include <ctime>
#include "graph1.h"

using namespace std;

const int WIDTH = 64; 
const int HEIGHT = 64;

//Protoypes
void initDisplay();
int getNoBugs();
int* getXCoords(int no_bugs);
int* getYCoords(int no_bugs);
int* displayObjects(int* x_coords, int* y_coords, int no_objects);
int zapBugs(int* x, int* y, int* objects, int no_bugs);


int main()
{
	//display graphics function
	displayGraphics();

	// random function
	srand(time(0));

	// function variables
	int no_bugs = 0;
	int score = 0;
	int* x_coords = NULL; 
	int* y_coords = NULL;
	int* objectNums = NULL; 

	// function call statements 
	initDisplay();
	no_bugs = getNoBugs();
	x_coords = getXCoords(no_bugs);
	y_coords = getYCoords(no_bugs);
	objectNums = displayObjects(x_coords, y_coords, no_bugs);
	score = zapBugs(x_coords, y_coords, objectNums, no_bugs);


	delete[] x_coords; 
	delete[] y_coords;
	delete[] objectNums;
}



// displays the initial grass backdrop and the white score / shot box in the top middle of the screen
void initDisplay()
{
	int rect; 
	int score = 0; 
	int shot = 0;

	//backdrop grass image
	displayPNG("grass.png", 0, 0);
	
	// the white square header
	drawRect(250, 0, 200, 40); 
	rect = drawRect(250, 0, 200, 40);
	setColor(rect, 255, 255, 255);

	// the score and shots icon
	gout << setPos(285, 20) << setColor(0, 0, 0) << "Score:    " << "Shots:    " << endg;
}


// prompts the user to enter the number of bugs that they want to play with 
int getNoBugs()
{
	int no_bugs = 0;

	do
	{
		cout << "\nEnter the number of bugs you wish to display <between 5 and 20 inclusive> : ";
		cin >> no_bugs; 

		if (no_bugs < 5 || no_bugs > 20)
		{
			cout << "\nERROR! PLEASE ENTER A NUMBER BETWEEN 5 AND 20 INCLUSIVE!\n";
		}
	} while (no_bugs < 5 || no_bugs > 20);

	return no_bugs; 
}


// dynamically allocates an array of integers with no_objects elements and sets each element to a random number between 
// 0 and 640-WIDTH where WIDTH is the width of the bugs.png image (64x64 is the dimension of the bugs.png).
int* getXCoords(int no_bugs)
{
	// dynamically allocate memory for an array with no_bugs elements
	int* x_coords = new int[no_bugs];

	// assign each element in the array a random x-coordinate
	for (int i = 0; i < no_bugs; i++)
	{
		x_coords[i] = rand() % (640 - WIDTH); 
	}

	return x_coords; 
}


// dynamically allocates an array of integers with no_bugs elements and sets each element to a random number between 40 and 440-HEIGHT, 
// where HEIGHT is the height of the bugs.png image (the dimension of bugs.png is 64x64). 
int* getYCoords(int no_bugs)
{
	// dynamically allocate the memory 
	int* y_coords = new int[no_bugs]; 

	// assign each element in the array a random y-coordinate
	for (int i = 0; i < no_bugs; i++)
	{
		y_coords[i] = (rand() % (400 - HEIGHT)) + 40; 
	}

	return y_coords; 
}


// displays a bugs.png at the corresponding x coordinate x/y coordinates and creates an array to store the object numbers 
int* displayObjects(int* x_coords, int* y_coords, int no_objects)
{
	// dynamically allocate a parallel array that holds the object number of each image displayed
	int* objectNums = new int[no_objects]; 

	for (int i = 0; i < no_objects; i++)
	{
		objectNums[i] = displayPNG("bugs.png", x_coords[i], y_coords[i]);
	}

	return objectNums; 
}


// prompts the user to try to zap the bugs in 14 guesses
int zapBugs(int* x, int* y, int* objects, int no_bugs)
{
	int x_guess;
	int y_guess; 
	int score = 0;
	int shots = 0;
	int zap_point[20];
	bool* bug_zapped = new bool[no_bugs]; 
	*bug_zapped = {0}; 

	cout << "\nTry to ZAP the bugs by guessing their coordinates!\n";


	//for (int i = 0; i < (no_bugs * 2); i++)
	while (shots < (2 * no_bugs) && score < no_bugs)
	{
		shots++;

		cout << "\nEnter a x/y coordinate: ";
		cin >> x_guess >> y_guess;

		for (int j = 10; j >= 0; j--)
		{
			drawCircle(j, x_guess, y_guess);
			zap_point[j] = drawCircle(j, x_guess, y_guess);
			setColor(zap_point[j], 0, 0, 0);
		}

		for (int k = 0; k < no_bugs; k++)
		{
			if (bug_zapped[k] != 1)
			{
				if ((x_guess > x[k]) && (x_guess < (x[k] + WIDTH)) && (y_guess > y[k]) && (y_guess < (y[k] + HEIGHT)))
				{
					removeObject(objects[k]);
					score = score + 1;
					bug_zapped[k] = 1; 
				}
			}
		}

		gout << setPos(340, 20) << setColor(0, 0, 0) << score << endg;
		gout << setPos(425, 20) << setColor(0, 0, 0) << shots << endg;

	}

	delete[] bug_zapped; 

	// determine the winner
	if (score == no_bugs)
		gout << setPos(330, 35) << setColor(0, 0, 0) << "Winner" << endg; 
	else if (shots == (2 * no_bugs))
		gout << setPos(330, 35) << setColor(0, 0, 0) << "Game Over" << endg;


	return score; 

}
