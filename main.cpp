#include <iostream>

#include "City.h"
#include "Organism.h"
#include <vector>
#include <random>


using namespace std;


int main() {

    City *city = new City(); //create city
    city->step(); //everything happens here

    return 0;
}