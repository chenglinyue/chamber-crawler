#ifndef HUMAN_H
#define HUMAN_H

#include "enemy.h"

class Human : public Enemy {
    public:
        Human(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);
        virtual Human* copy ();
        void dead();
};

#endif
