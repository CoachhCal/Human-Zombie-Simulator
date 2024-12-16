//
// Created by calvi on 2024-12-03.
//

#ifndef SIM_ASSINGMENT_CITY_H
#define SIM_ASSINGMENT_CITY_H

#include <ostream>

using namespace std;

class Organism;

class City {
public:
    City();
    Organism *grid[20][20];
    void createCity();
    void step();
    int generation;
    void reset(bool);
    void clearScreen();
    int countOrganisms(const string&);
    bool hasDiversity();
    void Col(int c);
    friend ostream& operator<<(ostream &output, City &city );

};


#endif //SIM_ASSINGMENT_CITY_H
