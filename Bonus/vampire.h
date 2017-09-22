#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "player.h"

class Vampire : public Player {
    public:
        Vampire(Controller &controller, std::pair<int, int>location, char id);;
        // Attacking
        virtual void attack(Human &human);
        virtual void attack(Dwarf &dwarf);
        virtual void attack(Orcs &orcs);
        virtual void attack(Merchant &merchant);
        virtual void attack(Dragon &dragon);
        virtual void attack(Elf &elf);
        virtual void attack(Halfling &halfling);

        virtual void attackedBy(Enemy &e);
        virtual void setHP(int health);
        virtual Vampire* copy ();
};

#endif
