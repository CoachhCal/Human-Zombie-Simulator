//
// Created by calvi on 2024-12-03.
//

#include <iostream>
#include <ostream>
#include <utility>
#include <random>
#include "Zombie.h"
#include "Human.h"
#include "GameSpecs.h"

Zombie::Zombie(int x, int y) : Organism(x,y) {
    this->name = "Z";
    this->starveCount = 0;
    this->biteCount = 0;
    this->moved = true;

}

void Zombie::turn(City *city) {

    if (!this->moved) {
        this->moved = true;
        biteCount += 1;
        starveCount += 1;

        vector<pair<int, int>> possibleCoords; //coords to move to
        vector<pair<int, int>> eatCoords; //coords that to eat humans
        vector<pair<int, int>> biteCoords; //coords to bite humans
        int xCoord;
        int yCoord;
        int x = this->getX();
        int y = this->getY();

        //Below is same as human... find coordinates (for moving and for eating and add to vector
        if (0 < x && city->grid[x - 1][y] == nullptr) { //up
            possibleCoords.emplace_back(x - 1, y);

        } else if (0 < x && city->grid[x - 1][y] != nullptr && city->grid[x - 1][y]->getName() == "H") {

            eatCoords.emplace_back(x - 1, y);
        }

        if (x < GRIDSIZE-1 && city->grid[x + 1][y] == nullptr) { //down
            possibleCoords.emplace_back(x + 1, y);

        } else if (x < GRIDSIZE-1 && city->grid[x + 1][y] != nullptr && city->grid[x + 1][y]->getName() == "H") {
            eatCoords.emplace_back(x + 1, y);
        }

        if (y < GRIDSIZE-1 && city->grid[x][y + 1] == nullptr) { //right
            possibleCoords.emplace_back(x, y + 1);

        } else if (y < GRIDSIZE-1 && city->grid[x][y + 1] != nullptr && city->grid[x][y + 1]->getName() == "H") {
            eatCoords.emplace_back(x, y + 1);
        }

        if (0 < y && city->grid[x][y - 1] == nullptr) { //left

            possibleCoords.emplace_back(x, y - 1);
        } else if (0 < y && city->grid[x][y - 1] != nullptr && city->grid[x][y - 1]->getName() == "H") {
            eatCoords.emplace_back(x, y - 1);
        }

        if (0 < y && 0 < x && city->grid[x - 1][y - 1] == nullptr) { //left up
            possibleCoords.emplace_back(x - 1, y - 1);

        } else if (0 < y && 0 < x && city->grid[x - 1][y - 1] != nullptr &&
                   city->grid[x - 1][y - 1]->getName() == "H") {
            eatCoords.emplace_back(x - 1, y - 1);
        }

        if (y < GRIDSIZE-1 && 0 < x && city->grid[x - 1][y + 1] == nullptr) { //right up

            possibleCoords.emplace_back(x - 1, y + 1);
        } else if (y < GRIDSIZE-1 && 0 < x && city->grid[x - 1][y + 1] != nullptr &&
                   city->grid[x - 1][y + 1]->getName() == "H") {
            eatCoords.emplace_back(x - 1, y + 1);
        }

        if (y < GRIDSIZE-1 && x < GRIDSIZE-1 && city->grid[x + 1][y + 1] == nullptr) { //right down
            possibleCoords.emplace_back(x + 1, y + 1);
        } else if (y < GRIDSIZE-1 && x < GRIDSIZE-1 && city->grid[x + 1][y + 1] != nullptr &&
                   city->grid[x + 1][y + 1]->getName() == "H") {
            eatCoords.emplace_back(x + 1, y + 1);
        }

        if (0 < y && x < GRIDSIZE-1 && city->grid[x + 1][y - 1] == nullptr) { //left down
            possibleCoords.emplace_back(x + 1, y - 1);

        } else if (0 < y && x < GRIDSIZE-1 && city->grid[x + 1][y - 1] != nullptr &&
                   city->grid[x + 1][y - 1]->getName() == "H") {
            eatCoords.emplace_back(x + 1, y - 1);
        }


        if (!eatCoords.empty()) { //if the zombie found a human to eat
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<int> dist(0, static_cast<int>(eatCoords.size()) - 1);
            int s = dist(mt);

            xCoord = eatCoords[s].first; //select random human to eat from vector
            yCoord = eatCoords[s].second;

            delete city->grid[xCoord][yCoord]; //delete human
            city->grid[xCoord][yCoord] = this; //move to humans spot

            this->setX(xCoord);
            this->setY(yCoord);

            city->grid[x][y] = nullptr; //set original position to null

            starveCount = 0; //reset count

        } else if (starveCount >= ZOMBIE_STARVE) { //if zombie couldn't eat and starve count is 3 or more
            delete city->grid[x][y]; //delete zombie
            city->grid[x][y] = nullptr; //for buildings
//            city->grid[x][y] = new Human(x, y); //replace with human

        } else if (!possibleCoords.empty()) { //coords to move to if no human to eat
            //https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<int> dist(0, static_cast<int>(possibleCoords.size()) - 1);
            int s = dist(mt);

            xCoord = possibleCoords[s].first; //random coord from vector
            yCoord = possibleCoords[s].second;

            city->grid[xCoord][yCoord] = this; //zombie moves
            this->setX(xCoord);
            this->setY(yCoord);
            city->grid[x][y] = nullptr; //set original position to null
        }

        // -------- CHECK TO SEE IF ZOMBIE IS READY TO BITE ---------
        // locate humans around zombies position and add to vector.

        if (starveCount < ZOMBIE_STARVE && biteCount >= ZOMBIE_BREED) {
            if (0 < x && city->grid[x - 1][y] != nullptr && city->grid[x - 1][y]->getName() == "H") { //up

                biteCoords.emplace_back(x - 1, y);
            } else if (x < GRIDSIZE-1 && city->grid[x + 1][y] != nullptr && city->grid[x + 1][y]->getName() == "H") { //down

                biteCoords.emplace_back(x + 1, y);
            } else if (y < GRIDSIZE-1 && city->grid[x][y + 1] != nullptr &&
                       city->grid[x][y + 1]->getName() == "H") { //right

                biteCoords.emplace_back(x, y + 1);
            } else if (0 < y && city->grid[x][y - 1] != nullptr && city->grid[x][y - 1]->getName() == "H") { //left

                biteCoords.emplace_back(x, y - 1);
            } else if (0 < y && 0 < x && city->grid[x - 1][y - 1] != nullptr &&
                       city->grid[x - 1][y - 1]->getName() == "H") { //left up
                biteCoords.emplace_back(x - 1, y - 1);
            } else if (y < GRIDSIZE-1 && 0 < x && city->grid[x - 1][y + 1] != nullptr &&
                       city->grid[x - 1][y + 1]->getName() == "H") { //right up

                biteCoords.emplace_back(x - 1, y + 1);
            } else if (y < GRIDSIZE-1 && x < GRIDSIZE-1 && city->grid[x + 1][y + 1] != nullptr &&
                       city->grid[x + 1][y + 1]->getName() == "H") { //right down
                biteCoords.emplace_back(x + 1, y + 1);
            } else if (0 < y && x < GRIDSIZE-1 && city->grid[x + 1][y - 1] != nullptr &&
                       city->grid[x + 1][y - 1]->getName() == "H") { //left down
                biteCoords.emplace_back(x + 1, y - 1);

            }

            if (!biteCoords.empty()) { //if there is a human to bite
                random_device rd;
                mt19937 mt(rd());
                uniform_int_distribution<int> dist(0, static_cast<int>(biteCoords.size()) - 1);
                int s = dist(mt);

                xCoord = biteCoords[s].first; //randomly choosing which human to bite
                yCoord = biteCoords[s].second;

                delete city->grid[xCoord][yCoord]; //delete human
                city->grid[xCoord][yCoord] = new Zombie(xCoord, yCoord); //add zombie
                biteCount = 0; //reset counter
            }

        }
    }

}
