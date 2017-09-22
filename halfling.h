#ifndef HALFLING_H
#define HALFLING_H

#include "enemy.h"

class Halfling : public Enemy {
    public:
        Halfling(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);
        virtual Halfling* copy ();
};

#endif
