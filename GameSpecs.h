//
// Created by calvi on 2024-12-05.
//

#ifndef SIM_ASSINGMENT_GAMESPECS_H
#define SIM_ASSINGMENT_GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // inital Humans
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int BUILDING_STARTCOUNT = 15; //initial Zombie count
const int HUMAN_BREED = 2; // steps until a Human breeds
const int ZOMBIE_BREED = 8; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 6; // steps until a Zombie starves and converts back
const int INTERVAL = 300; // millisecond pause between city steps
const int ITERATIONS = 100; // max number of steps


const int HUMAN_COLOR = 9; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow
const int BUILDING_COLOR = 12;
const int DASH_COLOR = 8; // pale white
const int WHITE_COLOR = 7;
const int GEN_COLOR = 15;

#endif //SIM_ASSINGMENT_GAMESPECS_H
