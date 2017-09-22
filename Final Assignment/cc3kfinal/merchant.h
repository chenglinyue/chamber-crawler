#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class Merchant : public Enemy {
    public:
        Merchant(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);
        virtual Merchant* copy ();
        virtual void dead();
};

#endif
