#ifndef DWARF_H
#define DWARF_H

#include "enemy.h"

class Dwarf : public Enemy {
    public:
        Dwarf(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);
        virtual Dwarf* copy ();
};

#endif
