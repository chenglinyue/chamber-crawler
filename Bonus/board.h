#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <time.h>

class Caption;

class Board {
    Caption *caption;
    std::vector <std::vector<char> > board;

    public:
        Board();
        ~Board();
        void update(std::pair<int, int>playerLoc, int sightRadius);
        void setAction (std::string action);
        std::string getAction();

        void setHP(const int health);
        void setAtk(const int attack);
        void setDef(const int defence);
        void setGold(const int amount);
        void setRace(const std::string race);
        void setStage(const int stageNumber);
        void setBoard(std::vector <std::vector<char> > &theBoard);
        int getGold();
        char getTile(std::pair<int, int> loc);
        void setTile(const std::pair< int, int> loc, const char c);
};

#endif
