//
// Created by calvi on 2024-12-03.
//

#include "Human.h"
#include "Building.h"
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include "GameSpecs.h"

using namespace std;

Human::Human(int x, int y, int count) : Organism(x, y) { //when human created, assign values to certain variables
    this->name = "H";
    this->buildingCount = 0;
    this->moved = true; //mark s true in case a human was made mid-step

}

void Human::turn(City *city) {
//    cout << "human start" << endl;

    if(!this->moved) { //if human hasn't moved yet

        this->moved = true;
        this->recruitCount += 1;
//        this->buildingCount += 1;
        vector<pair<int, int>> possibleCoords; //coords to move
        vector<pair<int, int>> buildingCoords;
        vector<pair<int, int>> recruitCoords; //coords to recruit
        int xCoord;
        int yCoord;
        int x = this->getX();
        int y = this->getY();
        int s;

//        cout << "human before coords" << endl;

        if (0 < x && city->grid[x - 1][y] == nullptr) { //check what coors are available to move too
            possibleCoords.emplace_back(x - 1, y); //store cords in vector

//            cout << "human check 1 for null" << endl;

        } else if (0 < x && city->grid[x - 1][y]->getName() == "B" && !city->grid[x - 1][y]->occupied) { //check what coors are available to move too
            buildingCoords.emplace_back(x - 1, y); //store cords in vector
//            cout << "human check building 1" << endl;

        }

        if (x < GRIDSIZE - 1 && city->grid[x + 1][y] == nullptr) {
            possibleCoords.emplace_back(x + 1, y);
//            cout << "human check 2 for null" << endl;

        } else if (x < GRIDSIZE - 1 && city->grid[x + 1][y]->getName() == "B" && !city->grid[x + 1][y]->occupied) {
            buildingCoords.emplace_back(x + 1, y);
//            cout << "human check building 2" << endl;

        }

        if (y < GRIDSIZE - 1 && city->grid[x][y + 1] == nullptr) {
            possibleCoords.emplace_back(x, y + 1);
//            cout << "human check 3 for null" << endl;
        } else if (y < GRIDSIZE - 1 && city->grid[x][y + 1]->getName() == "B" && !city->grid[x][y+1]->occupied) {
            buildingCoords.emplace_back(x, y + 1);
//            cout << "human check building 3" << endl;
        }

        if (0 < y && city->grid[x][y - 1] == nullptr) {
            possibleCoords.emplace_back(x, y - 1);
//            cout << "human check 4 for null" << endl;
        }
        else if (0 < y && city->grid[x][y - 1]->getName() == "B" && !city->grid[x][y-1]->occupied) {
            buildingCoords.emplace_back(x, y - 1);
//            cout << "human check building 4" << endl;
        }

//        cout << "right before first check" << endl;
        if (!buildingCoords.empty() && this->buildingCount > 1) { //humans prefer to move to buildings if close to one, but can only move to a building after every second turn
            if (this->recruitCount > HUMAN_BREED - 1) { // if recruit count is 3 or more
                x = this->getX();
                y = this->getY();

                if (0 < x && city->grid[x - 1][y] == nullptr) { //find free space to recruit to
                    recruitCoords.emplace_back(x - 1, y);

                }
                if (x < GRIDSIZE - 1 && city->grid[x + 1][y] == nullptr) {
                    recruitCoords.emplace_back(x + 1, y);

                }
                if (y < GRIDSIZE - 1 && city->grid[x][y + 1] == nullptr) {
                    recruitCoords.emplace_back(x, y + 1);
                }
                if (0 < y && city->grid[x][y - 1] == nullptr) {
                    recruitCoords.emplace_back(x, y - 1);
                }

                if (!recruitCoords.empty()) {
                    random_device rd;
                    mt19937 mt(rd());
                    uniform_int_distribution<int> distNew(0, static_cast<int>(recruitCoords.size()) - 1);
                    s = distNew(mt);

                    xCoord = possibleCoords[s].first; //choose a random spot from vector to create human
                    yCoord = possibleCoords[s].second;

                    city->grid[xCoord][yCoord] = new Human(xCoord, yCoord, 0); //placce human in chosen spot
                }

                random_device rd;
                mt19937 mt(rd());
                uniform_int_distribution<int> distBuild(0, static_cast<int>(buildingCoords.size()) - 1);
                s = distBuild(mt);

                xCoord = buildingCoords[s].first; //s is a random index from the coords vector.
                yCoord = buildingCoords[s].second; //these are the coords the human will move to

                city->grid[xCoord][yCoord]->occupied = true; //human "moves" to building
                city->grid[xCoord][yCoord]->humanRecruitCount = city->grid[x][y]->recruitCount;
                delete city->grid[x][y];
                city->grid[x][y] = nullptr; //set original position to null

            }
        } else if (!possibleCoords.empty()) { //https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
//            cout << "ready to move" << endl;
            this->buildingCount += 1;
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<int> dist(0, static_cast<int>(possibleCoords.size()) - 1);
            s = dist(mt);

            xCoord = possibleCoords[s].first; //s is a random index from the coords vector.
            yCoord = possibleCoords[s].second; //these are the coords the human will move to

            city->grid[xCoord][yCoord] = this; //move human
            this->setX(xCoord);
            this->setY(yCoord);
            city->grid[x][y] = nullptr; //set original position to null

            if (this->recruitCount > HUMAN_BREED - 1) { // if recruit count is 3 or more
                x = this->getX();
                y = this->getY();

                if (0 < x && city->grid[x - 1][y] == nullptr) { //find free space to recruit to
                    recruitCoords.emplace_back(x - 1, y);

                }
                if (x < GRIDSIZE - 1 && city->grid[x + 1][y] == nullptr) {
                    recruitCoords.emplace_back(x + 1, y);

                }
                if (y < GRIDSIZE - 1 && city->grid[x][y + 1] == nullptr) {
                    recruitCoords.emplace_back(x, y + 1);
                }
                if (0 < y && city->grid[x][y - 1] == nullptr) {
                    recruitCoords.emplace_back(x, y - 1);
                }

                if (!recruitCoords.empty()) {
                    uniform_int_distribution<int> distNew(0, static_cast<int>(recruitCoords.size()) - 1);
                    s = dist(mt);

                    xCoord = possibleCoords[s].first; //choose a random spot from vector to create human
                    yCoord = possibleCoords[s].second;

                    city->grid[xCoord][yCoord] = new Human(xCoord, yCoord, 0); //placce human in chosen spot
                }

                this->recruitCount = 0; //reset counter whether human was recruited or not
            }

        }
    }

//    cout << "human done" << endl;

}
