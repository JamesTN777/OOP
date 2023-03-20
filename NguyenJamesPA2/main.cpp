#include "Function.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
//Name:James Nguyen
//ID:104785020
//This is the main function. It takes in an x and y from the user
//and fills two grids full of 0's with a 1/3 chance of being 1
//a third grid is made containing 1's only where both original grids
//display a 1. All grids are displayed for the user.
//Program runs and compiles perfectly.



int main() {
    srand(time(0)); //random seed by time
    int row; 
    int col; 
    Grid Grid1; 
    Grid Grid2; 
    vector<int>GridVec1; //param for grid 1
    vector<int>GridVec2; //param for grid 2
    vector<int>GridVec3; //intersection grid
    int i2=0; //second index
    int i=0; //first index
    int randnum; //used to generate random numbers

    cout << "Please enter the number of rows for your grids: "; //Get User Input for rows and columns
    cin >> row;
    cout << "\nPlease enter the number of columns for grids: ";
    cin >> col;

    Grid1.setX(row); //set x and y for grids
    Grid1.setY(col);
    Grid2.setX(row);
    Grid2.setY(col);
    //fill grid 1 with 0's and 1/3 chance of 1's
    for (i = 0; i < row * col; i++) { 
        int randnum = rand()%3;
        if (randnum == 2) {
            Grid1.FillGrid(GridVec1, 1);
        }
        else {
            Grid1.FillGrid(GridVec1, 0);
        }
        }
    //fill grid 2 with 0's and 1/3 chance of 1's
    for (i = 0; i < row * col; i++) { 
        int randnum = rand() % 3;
        if (randnum == 2) {
            Grid1.FillGrid(GridVec2, 1);
        }
        else {
            Grid1.FillGrid(GridVec2, 0);
        }
    }
    //Display grid 1
    cout << "\nGrid1:\n"; 
    for (i = 0; i < GridVec1.size(); i++) {
        cout << GridVec1.at(i) << " ";
        if (i2 == row-1){ //i2 = row #
            cout << "\n"; //cout newl
            i2 = 0; //reset i2
        }
        else {
            i2 = i2 + 1; //increment i2
        } 
}
    //Display grid 2
    cout << "\nGrid2:\n"; 
    for (i = 0; i < GridVec2.size(); i++) {
        cout << GridVec2.at(i) << " ";
        if (i2 == row - 1) { //i2 = row #
            cout << "\n"; //cout newl
            i2 = 0; //reset i2
        }
        else {
            i2 = i2 + 1;//increment i2
        }

    }
    cout << "\nGrid3:\n";
    //call RunIntersec
    RunIntersec(GridVec1, GridVec2, GridVec3); 
    //Print out Grid 3
    for (i = 0; i < GridVec3.size(); i++) {
        cout << GridVec3.at(i) << " ";
        if (i2 == row - 1) { //i2 = row #
            cout << "\n"; //cout newl
            i2 = 0; //reset i2
        }
        else {
            i2 = i2 + 1; //increment i2
        }

    }

}

