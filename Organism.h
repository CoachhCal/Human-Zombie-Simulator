//
// Created by calvi on 2024-12-03.
//

#ifndef SIM_ASSINGMENT_ORGANISM_H
#define SIM_ASSINGMENT_ORGANISM_H
#include <string>
#include "City.h"

using namespace std;

class Organism {

protected:
    string name;
    int x;
    int y;

public:
    string getName() const;
    virtual void turn(City *city) = 0;
    virtual ~Organism();
    Organism(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    bool moved;
    bool occupied;
    bool humanRecruitCount;
    int recruitCount;

};


#endif //SIM_ASSINGMENT_ORGANISM_H
