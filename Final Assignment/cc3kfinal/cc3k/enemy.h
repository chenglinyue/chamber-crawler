#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "player.h"
#include "controller.h"
#include <cmath>
#include <sstream>
#include <iostream>

class Player;
class Shade;
class Drow;
class Goblin;
class Troll;
class Vampire;

class Enemy : public Character{
    protected:
        bool isHostile;
    public:
        Enemy(Controller& controller, std::pair<int, int>location, char id);
        // Defending
        virtual void attackedBy(Player &p) = 0;

        // Attacking
        virtual void attack(Shade &shade);
        virtual void attack(Drow &drow);
        virtual void attack(Goblin &goblin);
        virtual void attack(Troll &troll);
        virtual void attack(Vampire &vampire);
        void doDamage(const int dmg);
        void missed();
        void setIsHostile(bool hostile);
        bool getIsHostile();

        //virtual void makeMove();
        virtual void dead();

        virtual Character* copy () = 0;
};

#endif
