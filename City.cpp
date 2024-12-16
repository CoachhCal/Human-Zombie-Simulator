//
// Created by calvi on 2024-12-03.
//

#include <iostream>
#include <windows.h>
#include "City.h"
#include "Human.h"
#include "Zombie.h"
#include <ostream>
#include <thread>
#include <random>
#include "GameSpecs.h"
#include "Building.h"

using namespace std;

City::City() {
    createCity();
}

void City::step(){

    chrono:: milliseconds interval(300);

    while(this->hasDiversity() && this->generation < ITERATIONS) { //while both organisms exist and is less than iteration limit

        this_thread::sleep_for(interval);
        this->clearScreen();
        this->generation+=1; //counting generations
        reset(false); //sets organisms moved variable to false
        cout << *this; //print out the grid

        for (int x = 0; x < GRIDSIZE; x++) { //for each organism, call the turn method
            for (int y = 0; y < GRIDSIZE; y++) {
                if (this->grid[x][y] != nullptr) { //make sure space is not null ptr
                    this->grid[x][y]->turn(this);
                }
            }
        }
    }

    if(!this->hasDiversity()){ //if organism goes extinct

        if(countOrganisms("H") == 0){
            Col(HUMAN_COLOR);
            cout << "HUMANS HAVE GONE EXTINCT" << endl;

        }else if(countOrganisms("Z") == 0){
            Col(ZOMBIE_COLOR);
            cout << "ZOMBIES HAVE GONE EXTINCT" << endl;
        }


    }
}

int City::countOrganisms(const string& organismType){
    int organismCount = 0;

    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            if(this->grid[x][y] != nullptr) {
                if (this->grid[x][y]->getName() == organismType) { //count how many of the organism exists
                    organismCount += 1;
                }
            }
        }
    }
    return organismCount; //return number
}

void City::createCity() { //create city grid and populate

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> distCreate(0, static_cast<int>(GRIDSIZE-1)); //random number between 0 and grid size (inclusive)

    int x,y; // will change, but used for coordinates

    for (x = 0; x < 20; x++) { //create grid full of null pointers
        for (y = 0; y < 20; y++) {
            this->grid[x][y] = nullptr;
        }
    }

    for (int h = 0; h < HUMAN_STARTCOUNT; h++){ //populate grid with 100 humans
        do{
            x = distCreate(mt); //keep trying random coordinates until one is valid
            y = distCreate(mt);
        }while(this->grid[x][y] != nullptr); //if space is empty, exit loop to create human

        this->grid[x][y] = new Human(x,y, 0); //create human

    }

    for (int z = 0; z < ZOMBIE_STARTCOUNT; z++){ //populate grid with 5 zombies

        do{
            x = distCreate(mt); //keep trying random coordinates until one is valid
            y = distCreate(mt);
        }while(this->grid[x][y] != nullptr);

        this->grid[x][y] = new Zombie(x,y);
    }

    for (int b = 0; b < BUILDING_STARTCOUNT; b++){ //populate grid with 5 zombies

        do{
            x = distCreate(mt); //keep trying random coordinates until one is valid
            y = distCreate(mt);
        }while(this->grid[x][y] != nullptr);

        this->grid[x][y] = new Building(x,y);
    }
}

ostream& operator<<( ostream &output, City &city ){ //to print out grid and other information
    for(int x = 0; x< 20; x++){
        for(int y = 0; y<20; y++){
            if(city.grid[x][y] == nullptr) {
                city.Col(DASH_COLOR); //if null ptr print out hyphen
                output << " - ";
            }else if(city.grid[x][y]->getName() == "H"){ //if human print out H
                city.Col(HUMAN_COLOR);
                output << " " + city.grid[x][y]->getName() + " ";
            }else if (city.grid[x][y]->getName() == "Z"){ // if zombie print out Z
                city.Col(ZOMBIE_COLOR);
                output << " " + city.grid[x][y]->getName() + " ";
            }else if (city.grid[x][y]->getName() == "B"){ // if building print out Z
                city.Col(BUILDING_COLOR);
                output << " " + city.grid[x][y]->getName() + " ";
            }
        }
        output << endl;
    }
    city.Col(GEN_COLOR);
    output << "\nGENERATIONS: " << city.generation << endl;
    city.Col(HUMAN_COLOR);
    output << "HUMANS: " << city.countOrganisms("H") << endl;
    city.Col(ZOMBIE_COLOR);
    output << "ZOMBIES: " << city.countOrganisms("Z") << "\n\n" << endl;

    return output;
}

bool City::hasDiversity() { //check to see if both organisms still exist
    int human = 0;
    int zombie = 0;
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            if(this->grid[x][y] != nullptr) {
                if (this->grid[x][y]->getName() == "H" || this->grid[x][y]->getName() == "B" && this->grid[x][y]->occupied) {
                    human += 1;

                } else if (this->grid[x][y]->getName() == "Z") {
                    zombie += 1;
                }
            }
        }
    }
    if(human == 0 || zombie == 0) {
        return false;
    }
    else{
        return true;
    }
}

void City::reset(bool value) {
    for(int x = 0; x< 20; x++){
        for(int y = 0; y<20; y++) {
            if (this->grid[x][y] != nullptr) {
                this->grid[x][y]->moved = value; // resets all moved values to whatever is passed in
            }
        }
    }
}

void City::Col(int c) { //handle on console to change output color
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

void City::clearScreen() {
        cout << "\n\n\n";
}







