//
// Created by calvi on 2024-12-06.
//

#ifndef SIM_ASSINGMENT_BUILDING_H
#define SIM_ASSINGMENT_BUILDING_H

#include "Organism.h"
#include "City.h"
#include <iostream>
#include <ostream>
#include <utility>

class Building : public Organism
{

protected:



public:
    Building(int x, int y);

    void turn(City *city) override;
};


#endif //SIM_ASSINGMENT_BUILDING_H
