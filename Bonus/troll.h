#ifndef TROLL_H
#define TROLL_H

#include "player.h"

class Troll : public Player {
    public:
        Troll(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Enemy &e);
        virtual Troll* copy ();
        void recover();
};

#endif
