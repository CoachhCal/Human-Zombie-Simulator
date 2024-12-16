//
// Created by calvi on 2024-12-03.
//

#ifndef SIM_ASSINGMENT_HUMAN_H
#define SIM_ASSINGMENT_HUMAN_H

#include "Organism.h"
#include "City.h"
#include <iostream>
#include <ostream>
#include <utility>

class Human : public Organism
{

protected:

    int buildingCount;

public:

    Human(int x, int y, int count);

    void turn(City *city) override;
};


#endif //SIM_ASSINGMENT_HUMAN_H
