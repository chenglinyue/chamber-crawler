#ifndef POISONHEALTH_H
#define POISONHEALTH_H

#include "item.h"

class PoisonHealth: public Item {
    public:
        PoisonHealth (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual PoisonHealth* copy ();
};

#endif
