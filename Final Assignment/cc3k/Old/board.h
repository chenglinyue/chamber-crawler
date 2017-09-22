#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <time.h>

class Caption;

class Board {
    Caption *caption;

    public:
        Board();
        ~Board();
        void update(std::vector <std::vector<char> > board);
        void setAction (std::string action);
        std::string getAction();

        void setHP(int health);
        void setAtk(int attack);
        void setDef(int defence);
        void setGold(int amount);
        void setRace(std::string race);
        void setStage(int stageNumber);
        int getGold();
};

#endif
