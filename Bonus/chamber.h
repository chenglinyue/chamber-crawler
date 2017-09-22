#ifndef CHAMBER_H
#define CHAMBER_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class Chamber {
    private:
        std::vector<std::pair<int, int> > chamberPoints;
    public:
        Chamber (const int x, const int y, std::vector<std::vector<char> > & board, const int chamberID);
        void floodFill (const int x, const int y, std::vector<std::vector<char> > & board, const int chamberID);
        void addFloorPoint (const int x, const int y);
        bool isInChamber (const int x, const int y);
        std::pair<int, int>getRandomLoc();
};

#endif
