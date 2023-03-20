//James Nguyen
//ID:104785020
//Homework 4
//CSCI 2312
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//New Creature class using inheritance
class Creature
{
public:
    Creature() {
        //Default initialize strength and hitpoints to 10
        strength = 10;
        hitpoints = 10;
    }
    //Construct creature as an object of two int values 
    Creature(int StrengthVal, int HitPointVal) {
        strength = StrengthVal;
        hitpoints = HitPointVal;
    }
    //only returns int value
    int getStrength() { 
        return strength;
    }
    //outputs message with value
    int getHitpoints() { 
        return hitpoints;
    }
    //Set strength and hitpoint values
    void setStrength(int StrengthVal) { 
        strength = StrengthVal;
    }
    void setHitpoints(int HitPointVal) {
        hitpoints = HitPointVal;
    }
    
    //virtual getSpecies function
    virtual std::string getSpecies() { 
        return "Some Species"; //Original Definition shouldn't be used
    }
    //virtual getDamage function. All creatures use this
    virtual int getDamage() {
        int damage = (rand() % strength) + 1; //Always at least 1 damage
        std::cout << getSpecies() << " deals " << damage << " damage!\n";
        return damage; //
    }
private:
    int hitpoints;
    int strength;
};
//Rewritten demon class for inheritance
class Demon : public Creature
{
public:
    Demon() : Creature(){}
    Demon(int StrengthVal, int HitPointVal) : Creature() {
        setStrength(StrengthVal);
        setHitpoints(HitPointVal);
    }
    virtual std::string getSpecies() {
        return "Some Demon"; //Original definition shouldn't be used
    }
    int getDamage() { //5% chance to deal 50 damage
        int damage = Creature::getDamage();
        if (rand() % 100 <= 5)
            std::cout << getSpecies() << " additional damage chance success! +50 damage\nTotal damage: " << damage + 50 << std::endl;
        else
            std::cout << "Additional damage chance failed." << std::endl;
            return damage;
    }
};

class Balrog : public Demon
{
public:
    Balrog() : Demon() {}
    Balrog(int StrengthVal, int HitPointVal) : Demon() {
        setStrength(StrengthVal);
        setHitpoints(HitPointVal);
    }
    std::string getSpecies() {
        return "Balrog"; 
    }
    int getDamage() { //Balrog additional attack
        int damage = Demon::getDamage();
        int second = (rand() % getStrength());
        std::cout << getSpecies() << " attacks again for " << second << " more damage!\n";
        return damage+second;
    }
};

class Cyberdemon : public Demon
{
public:
    Cyberdemon() : Demon() {}
    Cyberdemon(int StrengthVal, int HitPointVal) : Demon() {
        setStrength(StrengthVal);
        setHitpoints(HitPointVal);
    }
    std::string getSpecies() {
        return "Cyberdemon";
    }
    //getDamage inherited for cyberdemons
};

class Human : public Creature
{
public:
    Human() : Creature() {}
    Human(int StrengthVal, int HitPointVal) : Creature() {
        setStrength(StrengthVal);
        setHitpoints(HitPointVal);
    }
    virtual std::string getSpecies() {
        return "Human"; //Will be used unless human subclass
    }
    //getDamage inherited for humans
};

class Elf : public Creature
{
public:
    Elf() : Creature() {}
    Elf(int StrengthVal, int HitPointVal) : Creature() {
        setStrength(StrengthVal);
        setHitpoints(HitPointVal);
    }
    virtual std::string getSpecies() {
        return "Elf"; //Will be used unless elf subclass
    }
    int getDamage() {
        int damage = Creature::getDamage();
        //std::cout << "Elf inflicts " << damage << "damage! " << std::endl;
        if (rand() % 100 <= 10) {
            damage = damage + damage;
            std::cout << getSpecies() << " inflicts bonus magical damage for " << damage<< std::endl;  
        }
        else {
            std::cout << getSpecies() << " bonus magical damage chance failed." << std::endl;
        }
        return damage;
    }
};


int main() {
    //Seed for true random code
    srand(time(NULL));
    //Initialize with default constructor each class
    Human h;
    Elf e;
    Cyberdemon c;
    Balrog b;
    //initialize with given value
    Human Crea1(10, 10);
    Elf Crea2(7, 13);
    Cyberdemon Crea3(8, 12);
    Balrog Crea4(5, 15);

    //Example of getStrength()
    std::cout << "Examples of getStrength: " << std::endl;
    std::cout << Crea1.getSpecies() << " has " << Crea1.getStrength() << " strength." << std::endl;
    std::cout << Crea2.getSpecies() << " has " << Crea2.getStrength() << " strength." << std::endl;
    std::cout << Crea3.getSpecies() << " has " << Crea3.getStrength() << " strength." << std::endl;
    std::cout << Crea4.getSpecies() << " has " << Crea4.getStrength() << " strength." << std::endl;
    //Example of getHitpoints()
    std::cout << "\nExamples of getHitpoints: " << std::endl;
    std::cout << Crea1.getSpecies() << " has " << Crea1.getHitpoints() << " hitpoints." << std::endl;
    std::cout << Crea2.getSpecies() << " has " << Crea2.getHitpoints() << " hitpoints." << std::endl;
    std::cout << Crea3.getSpecies() << " has " << Crea3.getHitpoints() << " hitpoints." << std::endl;
    std::cout << Crea4.getSpecies() << " has " << Crea4.getHitpoints() << " hitpoints." << std::endl;
    //Example of Damage
    std::cout << "\nExamples of getDamage: " << std::endl;
    Crea1.getDamage();
    Crea2.getDamage();
    Crea3.getDamage();
    Crea4.getDamage();

    return 0;
}
