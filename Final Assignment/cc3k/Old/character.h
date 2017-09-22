#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class Controller;

class Character {

    protected:
        int hp, atk, def;
        std::pair<int, int> loc;
        Controller *controller;
        char charID;

    public:
        Character(Controller &controller, std::pair<int, int>location, char id);
        virtual void takeDamage(const int dmg);
        virtual ~Character() = 0; // To make Character class abstract
        virtual void dead() = 0;
        virtual void setHP(int health);
        virtual void setAtk(int attack);
        virtual void setDef(int defence);
        int getDef(); // getter for def field
        int getHP();
        int getAtk();
        std::pair<int, int> getCharacterLoc();
        void setCharacterLoc(const int x, const int y);
        char getCharacterID ();
        virtual Character* copy () = 0;
};

#endif
