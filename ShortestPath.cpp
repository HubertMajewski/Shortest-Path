/* 
 * File:   main.cpp
 * Author: Hubert Majewski (23476002)
 *
 * Created on April 24, 2018, 10:57 PM
 */

#include <iostream>

using namespace std;


const int rows = 5;
const int cols = 6;
static int calculatedCost[rows][cols] = {0}; // the memo part

int cost(int, int);

int main(int argc, char** argv) {


	int exitColumn[rows]; //create array of int pointer elements

	// Get the shortest path out of each cell on the right
	for (int i = 0; i < rows; i++) {
		exitColumn[i] = cost(i, cols - 1); //prep calculatedCost Board
	}

	int recommendedPathIndex[cols] = {0};
	// now find the smallest of them 
	int minimum = exitColumn[0]; //start at index 0
	for (int i = 0; i < rows; i++) {
		if (exitColumn[i] < minimum) {
			minimum = exitColumn[i];
			recommendedPathIndex[cols - 1] = i;
		}
	}
	for (int i = 0; i < cols; i++) {
		cout << recommendedPathIndex[i] << " ";
	}
	cout << endl << endl;

	for (int j = cols - 1; j > 0; j--) { //go backwards

		int left = calculatedCost[recommendedPathIndex[j]][j - 1];
		int up = calculatedCost[(recommendedPathIndex[j] - 1 + rows) % rows][j - 1];
		int down = calculatedCost[(recommendedPathIndex[j] + 1) % rows][j - 1];
		
		recommendedPathIndex[j - 1] = (left < up && left < down ? recommendedPathIndex[j] : (up < down? (recommendedPathIndex[j] - 1 + rows) % rows :(recommendedPathIndex[j] + 1) % rows ));
		
		// set Index to be the smallest of the two
	}

	cout << "The sortest path is minimum of " << minimum << endl;

	for (int i = 0; i < cols; i++) {
		if (recommendedPathIndex[i] < 10)
			cout << "0" << recommendedPathIndex[i] << " ";
		else {
			cout << recommendedPathIndex[i] << " ";
		}
	}
	cout << endl << endl;

	//Print
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			if (calculatedCost[i][j] < 10) {
				cout << "0" << calculatedCost[i][j] << " ";
			} else {
				cout << calculatedCost[i][j] << " ";
			}
		cout << endl;
	}


	return 0;
}

int cost(int i, int j) { // i is the row, j is the column 
	static int weight[rows][cols] = {// the "terrain"
		{3, 4, 1, 2, 8, 6},
		{6, 1, 8, 2, 7, 4},
		{5, 9, 3, 9, 9, 5},
		{8, 4, 1, 3, 2, 6},
		{3, 7, 2, 8, 6, 4}
	};

	//base case 
	if (j == 0) {
		calculatedCost[i][0] = weight[i][0];
		return weight[i][0];
	}

	if (calculatedCost[i][j] > 0) {//check if non existant calculation
		return calculatedCost[i][j];
	}

	// recursive call 
	int left = weight[i][j] + cost(i, j - 1);
	int up = weight[i][j] + cost((i + (rows - 1)) % rows, j - 1); //To cycle about the rows
	int down = weight[i][j] + cost((i + 1) % rows, j - 1);

	// find the value of the shortest path sum at cell (i,j) 
	int min = (left > up ? up : left);
	min = (min > down ? down : min);

	return calculatedCost[i][j] = min; //return calc cost after assigned by min
}
