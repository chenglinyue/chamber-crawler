#ifndef ELF_H
#define ELF_H

#include "enemy.h"

class Elf : public Enemy {
    public:
        Elf(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Player &p);

        virtual void attack(Shade &shade);
        virtual void attack(Goblin &goblin);
        virtual void attack(Troll &troll);
        virtual void attack(Vampire &vampire);

        virtual Elf* copy();
};

#endif
