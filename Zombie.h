//
// Created by calvi on 2024-12-03.
//

#ifndef SIM_ASSINGMENT_ZOMBIE_H
#define SIM_ASSINGMENT_ZOMBIE_H


#include "Organism.h"
#include "City.h"

class Zombie : public Organism
{

public:
    int starveCount;
    int biteCount;
    Zombie(int x, int y);
    void turn(City *city) override;
};


#endif //SIM_ASSINGMENT_ZOMBIE_H
