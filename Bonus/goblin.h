#ifndef GOBLIN_H
#define GOBLIN_H

#include "player.h"

class Enemy;

class Goblin : public Player {
    public:
        Goblin(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Enemy &e);
        Goblin* copy ();
};

#endif
