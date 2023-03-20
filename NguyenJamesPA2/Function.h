/**
 Header file for main containing the declaration of functions.
 This function.h declares grid class and functions GetX, GetY, 
 SetX, SetY, FillGrid and RunIntersec
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#ifndef HW2_FUNCTION_H
#define HW2_FUNCTION_H
//create grid class
class Grid;
//defining grid class
class Grid {
private:
	//private variables
	int _x;
	int _y;

public:	
//default constructor
	Grid();
//overload constructor
	Grid(int x, int y);
//accessor
	int getX();
	int getY();

//mutator
	void setX(int x);
	void setY(int y);

	std::vector <int> FillGrid(std::vector<int>& NewVec, int RandInt);

};
//Declaring RunIntersec
std::vector<int> RunIntersec(std::vector <int>& TempoVec1, std::vector <int>& TempoVec2, std::vector<int>&TempVec3);



#endif //HW2_Function_H
