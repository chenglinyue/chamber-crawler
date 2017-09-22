#ifndef DROW_H
#define DROW_H

#include "player.h"

class BoostAtk;
class BoostDef;
class RestoreHealth;
class PoisonHealth;
class WoundAtk;
class WoundDef;

class Drow : public Player {
    public:
        Drow(Controller &controller, std::pair<int, int>location, char id);
        virtual void attackedBy(Enemy &e);
        virtual Drow* copy ();

        virtual void pickUp(BoostAtk &boostatk);
        virtual void pickUp(BoostDef &boostdef);
        virtual void pickUp(RestoreHealth &restorehealth);
        virtual void pickUp(PoisonHealth &poisonhealth);
        virtual void pickUp(WoundAtk &woundatk);
        virtual void pickUp(WoundDef &wounddef);
};

#endif
