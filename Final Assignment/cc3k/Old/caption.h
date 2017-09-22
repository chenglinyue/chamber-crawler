#ifndef CAPTION_H
#define CAPTION_H

#include <iostream>

class Caption {
    std::string race;
    std::string action;
    int hp, atk, def, gold, stage;
    public:
        Caption();
        void updateCaption();
        void setAction(std::string actionString);
        std::string getAction();

        // setters
        void setHP(int health);
        void setAtk(int attack);
        void setDef(int defence);
        void setGold(int amount);
        void setRace(std::string race);
        void setStage(int stageNumber);
        int getGold();
};

#endif
