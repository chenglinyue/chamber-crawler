#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"
#include <time.h>
#include <unistd.h>

class Treasure: public Item {
    int amount;
    bool obtainable;
    public:
        //Treasure(int amt, char id);
        Treasure(Controller & controller, int amt, char id);
        void pickUp(Player &player);
        Treasure* copy ();
        int getAmount();
        void placeDependencies ();
        void setObtainable(bool canObtain);
        bool getObtainable();
};

#endif
