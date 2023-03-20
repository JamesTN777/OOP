//James Nguyen
//ID:104785020
//Final Project
//CSCI 2312

//string for char arrays
#include <string>
//iostream&fstream for csv reading
#include <iostream>
#include <fstream>
//Vector to store ship pointers
#include <vector>
//stdlib&time for random seeding
#include <stdlib.h>
#include <time.h>

//Base class Ship
class Ship {
private: //3 Variables of Ship
    int x;
    int y;
    std::string direction;
    int size;
    char visual; //Visual is the char going on the grid
public:
    //Default initializer for ship
    Ship() {
        x = 0;
        y = 0;
        direction = ' ';
        size = 0;
        visual = '-'; 
    }
    //Constructor for ship
    Ship(int xpos, int ypos, std::string ShipDirection, int ShipSize, char visuals) { 
        x = xpos;
        y = ypos;
        direction = ShipDirection;
        size = ShipSize;
        visual = visuals;
    }
    //Accessors
    int getXpos() {
        return x;
    }
    int getYpos() {
        return y;
    }
    std::string getDirection() {
        return direction;
    }
    int getSize() {
        return size;
    }
    char getVisual() {
        return visual;
    }
    virtual std::string getName() = 0;
    //Mutators
    void setXpos(int X) {
        x = X; 
    }
    void setYpos(int Y) {
        y = Y;
    }
    void setDirection(std::string ShipDirection) {
        direction = ShipDirection;
    }
    void setSize(int ShipSize) {
        size = ShipSize;
    }


};
//Carrier Ship of size 5, visual 'C'
class Carrier : public Ship {
public:
    Carrier() : Ship(0,0,"H",5,'C') {}
    Carrier(int xpos, int ypos, std::string ShipDirection) : Ship(xpos, ypos, ShipDirection, 5, 'C') {}
    std::string getName() override {
        return "Carrier";
    }
};
//Battleship Ship of size 4, visual 'B'
class Battleship : public Ship {
public:
    Battleship() : Ship(0, 0, "H", 4, 'B') {}
    Battleship(int xpos, int ypos, std::string ShipDirection) : Ship(xpos, ypos, ShipDirection, 4, 'B') {}
    std::string getName() override {
        return "Battleship";
    }
}; 
//Cruiser Ship of size 3, visual 'R'
class Cruiser : public Ship {
public:
    Cruiser() : Ship(0, 0, "H", 3, 'R') {}
    Cruiser(int xpos, int ypos, std::string ShipDirection) : Ship(xpos, ypos, ShipDirection, 3, 'R') {}
    std::string getName() override {
        return "Cruiser";
    }
}; 
//Submarine Ship of size 3, visual 'S'
class Submarine : public Ship {
public:
    Submarine() : Ship(0, 0, "H", 3, 'S') {}
    Submarine(int xpos, int ypos, std::string ShipDirection) : Ship(xpos, ypos, ShipDirection, 3, 'S') {}
    std::string getName() override {
        return "Submarine";
    }
};  
//Destroyer Ship of size 2, visual 'D'
class Destroyer : public Ship {
public:
    Destroyer() : Ship(0, 0, "H", 2, 'D') {}
    Destroyer(int xpos, int ypos, std::string ShipDirection) : Ship(xpos, ypos, ShipDirection, 2, 'D') {}
    std::string getName() override {
        return "Destroyer";
    }
};

std::vector<Ship*>ReadShips()
{
    std::ifstream infile1("ship_placement.csv"); //create ifstream
    std::string TempString;
    int curr = 0; //current index
    Ship *TempShip;
    std::vector<Ship*>ShipVec;
    int tempInt;

    getline(infile1, TempString); //get header outside of while loop
    while (infile1.good())  //Tokens assigned to TempFakes
    {
        curr = 0;
        getline(infile1, TempString, ','); //TempString = Ship Name
        if (TempString == "Carrier")
        TempShip = new Carrier;
        else if (TempString == "Battleship")
        TempShip = new Battleship;
        else if (TempString == "Cruiser")
        TempShip = new Cruiser;
        else if (TempString == "Submarine")
        TempShip = new Submarine;
        else 
        TempShip = new Destroyer;

        if (TempString.empty())
            continue;

        getline(infile1, TempString, ','); //TempString = Position
        tempInt = (int)(TempString[0]-'A');
        TempShip->setXpos(tempInt);
        tempInt = TempString[1]-49;
        TempShip->setYpos(tempInt);
        getline(infile1, TempString); //TempString = Direction
        TempShip->setDirection(TempString);

        ShipVec.push_back(TempShip); //TempObject pushed back into return vector
    }
    return ShipVec;
}

//===================================================================================================================================================

class GameBoard {
private:
    //Private variable grid
    char grid[10][10];

public:
    //Gameboard constructor
    GameBoard() {
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
               this->at(row,col)= 'W';
            }
        }
    }
    bool isValid(Ship *ship) { //Boundary Checking
        if (ship->getDirection() == "V") { //Check Vertical placement
            if ((ship->getXpos() + ship->getSize()) > 9) {
                return false;
            }
            for (int row = ship->getXpos(); row < ship->getXpos() + ship->getSize(); row++) {
                if (this->at(row, ship->getYpos()) != 'W') {
                    return false;
                }
            }
        }
        else { //Check Horizontal placement
            if ((ship->getYpos() + ship->getSize()) > 9) { 
                return false;
            }
            for (int col = ship->getYpos(); (col < ship->getYpos() + ship->getSize()); col++) {
                if (this->at(ship->getXpos(), col) != 'W') {
                    return false;
                }
            }
        }
        return true;
    }

    char& at(int row, int col) { //.at() for GameBoards
        return grid[row][col];
    }


    void setShip(Ship *ship) { //Gameboard function to place ship using ship ptr parameter
        if (isValid(ship)) {
            if (ship->getDirection() == "H") { //horizontal placement
                for (int r = ship->getXpos(); r < (ship->getXpos() + ship->getSize()); r++) {
                    this->at(r, ship->getYpos()) = ship->getVisual();
                }
            }
            else {  //vertical placement
                for (int c = ship->getYpos(); c < (ship->getYpos() + ship->getSize()); c++) {
                    this->at(ship->getXpos(), c) = ship->getVisual();
                }
            }
        }
        else { //Cannot place ship
            std::cout << "\nUnable to create. Please replace your ship." << std::endl;
        }
    }

    void PrintGrid() {
        std::cout << "\n  0 1 2 3 4 5 6 7 8 9" << std::endl;
        for (int i = 0; i < 10; i++) { //Columns = i
            std::cout << (char)('A' + i) << " ";
            for (int j = 0; j < 10; j++) { //Rows = j

                std::cout << this->at(j, i) << " ";

            }
            std::cout << std::endl;
        }
    }

    bool checkSunk(Ship *ship) {
        if (ship->getDirection() == "V") { //Check vertical placement
            if ((ship->getXpos() + ship->getSize()) > 9) {
                return false;
            }
            for (int r = ship->getXpos(); r < (ship->getXpos() + ship->getSize()); r++) {
                if (this->at(r, ship->getYpos()))
                    return false;
            }
        }
        else {
            if ((ship->getYpos() + ship->getSize()) < 9) { //Check horizontal placement
                return false;
            }
                for (int c = ship->getYpos(); c < (ship->getYpos() + ship->getSize()); c++) {
                    if (this->at(ship->getXpos(), c))
                        return false;
                
                }
        }
            return true;
}
/* This was my initial checkHit before I implemented different messages to display depending on ship hit.
    bool checkHit(int row, int col) {
        if (this->at(row, col) == 'C'||this->at(row,col)=='B'|| this->at(row, col) == 'R' || this->at(row, col) == 'S' || this->at(row, col) == 'D') {
            return true;
        }
        else return false;
    }
    */
    bool checkHit(int row, int col) { //Check for visual at (row, col)
        switch (this->at(row, col)) {
        case 'C':
            std::cout << "Carrier hit!" << std::endl;
            return true;
            break;
        case 'B':
            std::cout << "Battleship hit!" << std::endl;
            return true;
            break;
        case 'R':
            std::cout << "Cruiser hit!" << std::endl;
            return true;
            break;
        case 'S':
            std::cout << "Submarine hit!" << std::endl;
            return true;
            break;
        case 'D':
            std::cout << "Destroyer hit!" << std::endl;
            return true;
            break;
        case 'X':
            std::cout << "Spot already fired at!" << std::endl;
            return false;
        default:
            return false;
        }
    }

    bool FinishedGame(std::vector<Ship*>SumVec) { //CheckSunk but with vector parameter
        int Counter = 0;
        for (int i = 0; i < SumVec.size(); i++) {
            if (this->checkSunk(SumVec.at(i))) {
                Counter = Counter + 1;
            }
        }
        if (Counter == 5)
            return true;
        else return false;
    }
	};

//===================================================================================================================================================
int main() {
    //UserShips = vector of player's ships
    //ShipList = vector of CPU's ships
    std::vector<Ship*>ShipList;
    std::vector<Ship*>UserShips;
    ShipList = ReadShips();
    //Random seeding
    srand(time(NULL));
    //Four Gameboards
    GameBoard UserGrid1;
    GameBoard UserGrid2;
    GameBoard CPUGrid1;
    GameBoard CPUGrid2;
    //Setting the ships from file into CPU1 grid
    for (int i = 0; i < ShipList.size(); i++) {
        CPUGrid1.setShip(ShipList.at(i));
    }
    //Game Instructions
    std::cout << "Welcome to the game of Battleship. Your goal is to sink the other player's ships before they sink yours." << std::endl;
    std::cout << "The game works on a 10x10 grid where both players set 5 ships." << std::endl;
    std::cout << "The players then take turns guessing grid coordinates to fire at the other player's ship." << std::endl;
    std::cout << "Water is marked with a 'W' on the grid, while ships have their respective letters C, B, R, S, and D." << std::endl;
    std::cout << "A hit on the grid will be marked with an X. A miss will be marked with an O." << std::endl;
    std::cout << "The first player to sink all of the opponent's ships wins! Goodluck!\n" << std::endl;
    //Showing a blank grid for placement
    UserGrid1.PrintGrid();
    //Creating pointers to new of each ship object
    Carrier *UserCarrier = new Carrier();
    Battleship *UserBattleship = new Battleship();
    Cruiser *UserCruiser = new Cruiser();
    Submarine *UserSubmarine = new Submarine();
    Destroyer *UserDestroyer = new Destroyer();
    int inputNum;
    int inputNum2;
    std::string inputString;
    bool correct = false;
    //===========================================
    //USER SHIP PLACEMENT
    while (!correct) { //Placing Carrier
        std::cout << "Please enter the X value for your Carrier (0-9)" << std::endl;
        std::cin >> inputNum;
        UserCarrier->setXpos(inputNum);
        std::cout << "Please enter the Y value for your Carrier (0-9)" << std::endl;
        std::cin >> inputNum;
        UserCarrier->setYpos(inputNum);
        std::cout << "Please enter the direction of your Carrier (H/V)" << std::endl;
        std::cin >> inputString;
        UserCarrier->setDirection(inputString);

        if (UserGrid1.isValid(UserCarrier)) {
            UserGrid1.setShip(UserCarrier);
            correct = true;
            UserShips.push_back(UserCarrier);
        }
        else std::cout << "Please replace your Carrier." << std::endl;
    } 
    correct = false;
    while (!correct) { //Placing Battleship
        std::cout << "Please enter the X value for your Battleship (0-9)" << std::endl;
        std::cin >> inputNum;
        UserBattleship->setXpos(inputNum);
        std::cout << "Please enter the Y value for your Battleship (0-9)" << std::endl;
        std::cin >> inputNum;
        UserBattleship->setYpos(inputNum);
        std::cout << "Please enter the direction of your Battleship (H/V)" << std::endl;
        std::cin >> inputString;
        UserBattleship->setDirection(inputString);

        if (UserGrid1.isValid(UserBattleship)) {
            UserGrid1.setShip(UserBattleship);
            correct = true;
            UserShips.push_back(UserBattleship);
        }
        else std::cout << "Please replace your Battleship." << std::endl;
    }
    correct = false;
    while (!correct) { //Placing Cruiser
        std::cout << "Please enter the X value for your Cruiser (0-9)" << std::endl;
        std::cin >> inputNum;
        UserCruiser->setXpos(inputNum);
        std::cout << "Please enter the Y value for your Cruiser (0-9)" << std::endl;
        std::cin >> inputNum;
        UserCruiser->setYpos(inputNum);
        std::cout << "Please enter the direction of your Cruiser (H/V)" << std::endl;
        std::cin >> inputString;
        UserCruiser->setDirection(inputString);

        if (UserGrid1.isValid(UserCruiser)) {
            UserGrid1.setShip(UserCruiser);
            correct = true;
            UserShips.push_back(UserCruiser);
        }
        else std::cout << "Please replace your Carrier." << std::endl;
    }
    correct = false;
    while (!correct) { //Placing Submarine
        std::cout << "Please enter the X value for your Submarine (0-9)" << std::endl;
        std::cin >> inputNum;
        UserSubmarine->setXpos(inputNum);
        std::cout << "Please enter the Y value for your Submarine (0-9)" << std::endl;
        std::cin >> inputNum;
        UserSubmarine->setYpos(inputNum);
        std::cout << "Please enter the direction of your Submarine (H/V)" << std::endl;
        std::cin >> inputString;
        UserSubmarine->setDirection(inputString);

        if (UserGrid1.isValid(UserSubmarine)) {
            UserGrid1.setShip(UserSubmarine);
            UserShips.push_back(UserSubmarine);
            correct = true;
        }
        else std::cout << "Please replace your Submarine." << std::endl;
    }
    correct = false;
    while (!correct) { //Placing Destroyer
        std::cout << "Please enter the X value for your Destroyer (0-9)" << std::endl;
        std::cin >> inputNum;
        UserDestroyer->setXpos(inputNum);
        std::cout << "Please enter the Y value for your Destroyer (0-9)" << std::endl;
        std::cin >> inputNum;
        UserDestroyer->setYpos(inputNum);
        std::cout << "Please enter the direction of your Destroyer (H/V)" << std::endl;
        std::cin >> inputString;
        UserDestroyer->setDirection(inputString);

        if (UserGrid1.isValid(UserDestroyer)) {
            UserGrid1.setShip(UserDestroyer);
            correct = true;
            UserShips.push_back(UserDestroyer);
        }
        else std::cout << "Please replace your Destroyer." << std::endl;
    }
    //===========================================
    //Show grid once before loop
    std::cout << "This is your grid." << std::endl;
    UserGrid1.PrintGrid();
    //LifePoints for game loop
    int UserHP=17;
    int CPUHP = 17;
    //while (Ships are not sunk)
    //while (!UserGrid1.FinishedGame(UserShips) || !CPUGrid1.FinishedGame(ShipList)){ FinishedGame() Not working
    while (UserHP!=0 && CPUHP!=0){
        do { 
            std::cout << "Please insert an x value to fire at. (0-9)" << std::endl;
            std::cin >> inputNum;
            std::cout << "Please insert an x value to fire at. (0-9)" << std::endl;
            std::cin >> inputNum2;
        } while (inputNum > 10 || inputNum2 > 10); //Error checking for user input to be 0-9
        std::cout << "You have fired at (" << inputNum << "," << inputNum2 << ")\n";
        //if hit, -1 from CPU HP and mark X
        if (CPUGrid1.checkHit(inputNum, inputNum2)) {
            CPUGrid1.at(inputNum, inputNum2) = 'X';
            UserGrid2.at(inputNum, inputNum2) = 'X';
            CPUHP = CPUHP - 1;
        }
        //if miss, mark O
        else {
            (CPUGrid1.at(inputNum, inputNum2) = 'O');
            std::cout << "It was a miss." << std::endl;
            UserGrid2.at(inputNum, inputNum2) = 'O';

        }
        //CPU will guess random in grid of 100 chars
        inputNum = rand() % 100; 
        if (inputNum > 10) { //if over 10, split into 2 digits
            inputNum2 = inputNum % 10;
            inputNum = inputNum / 10 % 10;
        }
        else { //if under 10, make 10's digit 0;
            inputNum2 = inputNum % 10;
            inputNum = 0;
        }
        //Output CPU fire coords no matter what
        std::cout << "CPU Fires at (" << inputNum << "," << inputNum2 << ")" << std::endl;
        //if hit, -1 from UserHP, mark X
        if (UserGrid1.checkHit(inputNum, inputNum2)) {
            UserHP = UserHP - 1; 
            UserGrid1.at(inputNum, inputNum2) = 'X';
        }
        //if miss, mark O
        else { 
            std::cout << "CPU missed!" << std::endl;
            UserGrid1.at(inputNum, inputNum2) = 'O';
        }

        std::cout << "\nPlacement Grid: " << std::endl;
        UserGrid1.PrintGrid();
        std::cout << "\nTracking Grid: " << std::endl;
        UserGrid2.PrintGrid();
    }
    if (UserHP == 0) { //Failure message
        std::cout << "You just lost to a CPU. Get good." << std::endl;
    }
    else { //Victory Message
        std::cout << "\nWell played! You have sunk all your opponents ships." << std::endl;
    }

    return 0;
}