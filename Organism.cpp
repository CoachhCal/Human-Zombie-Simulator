//
// Created by calvi on 2024-12-03.
//

#include <iostream>
#include "Organism.h"



string Organism::getName() const {
    return this->name;
}

Organism::Organism(int x, int y) {
    this->x = x;
    this->y = y;
    this->moved = false;

}

int Organism::getX() const {
    return this->x;
}

int Organism::getY() const {
    return this->y;
}

void Organism::setX(int x) {
    this->x = x;
}

void Organism::setY(int y) {
    this->y = y;
}

Organism::~Organism() = default;
