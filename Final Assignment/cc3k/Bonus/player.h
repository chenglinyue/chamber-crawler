#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <cmath>
#include <iostream>

class Enemy;
class Human;
class Dwarf;
class Orcs;
class Merchant;
class Dragon;
class Elf;
class Halfling;
//class Controller;
class Item;
class Treasure;
class BoostAtk;
class BoostDef;
class RestoreHealth;
class PoisonHealth;
class WoundAtk;
class WoundDef;

class Player : public Character{
    int gold, maxHP;
    int baseAtk, baseDef;
    public:
        Player(Controller& controller, std::pair<int, int>location, char id); // One param ctor for vampires who don't HP cap
        Player(Controller& controller, std::pair<int, int>location, const int maxHealth, char id);
        // Attacking
        virtual void attack(Human &human);
        virtual void attack(Dwarf &dwarf);
        virtual void attack(Orcs &orcs);
        virtual void attack(Merchant &merchant);
        virtual void attack(Dragon &dragon);
        virtual void attack(Elf &elf);
        virtual void attack(Halfling &halfling);

        // Defending
        virtual void attackedBy(Enemy &enemy) = 0;
        virtual void makeMove();

        virtual void setHP(const int health);
        void setAtk(const int attack);
        void setDef(const int defence);
        void setGold(const int amount);

        int getGold();
        int getBaseAtk();
        int getBaseDef();

        virtual void pickUp(Treasure &treasure);
        virtual void pickUp(BoostAtk &boostatk);
        virtual void pickUp(BoostDef &boostdef);
        virtual void pickUp(RestoreHealth &restorehealth);
        virtual void pickUp(PoisonHealth &poisonhealth);
        virtual void pickUp(WoundAtk &woundatk);
        virtual void pickUp(WoundDef &wounddef);

        void initializePlayer();
        void dead();
        virtual Character* copy () = 0;
};

#endif
