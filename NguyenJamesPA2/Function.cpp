/**
This cpp file includes the definitions of the functions declared in function.h
including SetX, SetY, GetX, Gety, the class Grid itself, and FillGrid and RunIntersec
*/
#include "Function.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

//Defining default constructor of Grid class
Grid::Grid() {
	_x = 0;
	_y = 0;
}
//Defining Accessor of Grid
int Grid::getX() {
	return _x;
}

int Grid::getY() {
	return _y;
}

//Defining Mutators of Grid
void Grid::setX(int x) {
	_x = x;
}

void Grid::setY(int y) {
	_y = y;
}
//Function to fill grid, had to be remade with integer as parameter
std::vector<int> Grid::FillGrid(std::vector<int>& NewVec, int RandInt)
{
	int rows; //Useless variables now that I removed the for loop
	int cols;
	rows = getX();
	cols = getY();
	
	//for (int i = 0; i < rows * cols; i++) { //deleted loop inside function because seed doesn't randomize with every function call
		NewVec.push_back(RandInt);	
	//}

	return NewVec;
}
//Definition of RunIntersec
vector <int> RunIntersec(std::vector<int>& TempVec, std::vector<int>& TempVec2, std::vector<int>& TempVec3) {
	int i;
	//fill third grid if and only if both grid 1 and 2 have a 1 there.
	for (i = 0; i < TempVec.size(); ++i) {
		if (TempVec.at(i) == 1 && TempVec2.at(i)==1) {
			TempVec3.push_back(1);
		}
		else {
			TempVec3.push_back(0);
		}
	}
	return TempVec3;
}
