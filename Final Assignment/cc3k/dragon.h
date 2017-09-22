#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Treasure;

class Dragon : public Enemy {
    Treasure *dragonHoard;
    public:
        Dragon(Controller & controller, std::pair<int, int> loc, char id);
        virtual void attackedBy(Player &p);
        virtual void dead();
        virtual Dragon* copy();
        void setDragonHoard(Treasure &treasure);
        Treasure* getDragonHoard();
};

#endif
