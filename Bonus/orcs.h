#ifndef ORCS_H
#define ORCS_H
#include "enemy.h"

class Orcs : public Enemy {
    public:
        Orcs(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);
        virtual void attack(Goblin &goblin);
        virtual Orcs* copy();
};

#endif
