#ifndef BOARD_H
#define BOARD_H

#include <iostream>

#include "chamber.h"

const int BOARDHEIGHT = 27;
const int BOARDWIDTH = 80;
const int NUMCHAMBERS = 3;

const int CHAMBERONEX = 2;
const int CHAMBERONEY = 2;
const int CHAMBERONEWIDTH = 29;
const int CHAMBERONEHEIGHT = 6;

const int CHAMBERTWOX = 3;
const int CHAMBERTWOY = 14;
const int CHAMBERTWOWIDTH = 24;
const int CHAMBERTWOHEIGHT = 9;

const int CHAMBERTHREEX = 37;
const int CHAMBERTHREEY = 9;
const int CHAMBERTHREEWIDTH = 15;
const int CHAMBERTHREEHEIGHT = 5;

class Board {
    Chamber *chambers[NUMCHAMBERS];

    // The first of the pair will represent the actual
    // board while the second of the pair represents
    // the board with all chambers marked with the respective
    // number from 1 - 5
    std::pair<char,char> ** board;
    public:
        Board();
        void initializeBoard();
        void printBoard();
};

#endif
