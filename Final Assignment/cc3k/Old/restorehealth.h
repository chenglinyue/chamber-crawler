#ifndef RESTOREHEALTH_H
#define RESTOREHEALTH_H

#include "item.h"

class RestoreHealth: public Item {
    public:
        RestoreHealth (Controller & c, char id);
        virtual void pickUp(Player &player);
        virtual RestoreHealth* copy ();
};


#endif
