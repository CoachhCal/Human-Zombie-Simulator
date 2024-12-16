//
// Created by calvi on 2024-12-06.
//

#include "Building.h"
#include "Human.h"
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include "GameSpecs.h"

using namespace std;

Building::Building(int x, int y) : Organism(x, y) { //when human created, assign values to certain variables
    this->name = "B";
    this->occupied = false;
    this->moved = false;

}

void Building::turn(City *city) {

//    cout << "building turn" << endl;

    if (!this->moved) {


        this->moved = true;

        vector<pair<int, int>> possibleCoords; //coords to move
        int x = this->getX();
        int y = this->getY();
        int xCoord;
        int yCoord;
        int s;

        if(this->occupied){
//            cout << "occupied"<<endl;

            if (0 < x && city->grid[x - 1][y] == nullptr) { //find free space to recruit to
                possibleCoords.emplace_back(x - 1, y);

            }
            if (x < GRIDSIZE -1 && city->grid[x + 1][y] == nullptr) {
                possibleCoords.emplace_back(x + 1, y);

            }
            if (y < GRIDSIZE -1 && city->grid[x][y + 1] == nullptr) {
                possibleCoords.emplace_back(x, y + 1);
            }
            if (0 < y && city->grid[x][y - 1] == nullptr) {
                possibleCoords.emplace_back(x, y - 1);
            }

            if(!possibleCoords.empty()){
//                cout << "moving" << endl;
                random_device rd;
                mt19937 mt(rd());
                uniform_int_distribution<int> distNew(0, static_cast<int>(possibleCoords.size()) - 1);
                s = distNew(mt);

                xCoord = possibleCoords[s].first; //choose a random spot from vector to create human
                yCoord = possibleCoords[s].second;

                city->grid[xCoord][yCoord] = new Human(xCoord, yCoord, city->grid[x][y]->recruitCount); //place human in chosen spot
                this->occupied = false; //empty building
            }
        }
    }
}