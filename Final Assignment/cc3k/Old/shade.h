#ifndef SHADE_H
#define SHADE_H

#include "player.h"

class Enemy;

class Shade : public Player {
    public:
        Shade(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Enemy &e);
        Shade* copy ();
};

#endif
