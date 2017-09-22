#ifndef BOOSTATK_H
#define BOOSTATK_H

#include "item.h"

class BoostAtk: public Item {
    public:
        BoostAtk (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual BoostAtk* copy ();
};


#endif
