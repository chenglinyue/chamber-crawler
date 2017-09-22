#include "character.h"
#include "controller.h"
#include <iostream>
using namespace std;

// 3 param ctor
Character::Character(Controller &controller, std::pair<int, int> location, char id):controller(&controller) {
    loc = location;
    charID = id;
}

// dtor
Character::~Character() {}

// Character was attacked, update hp
int Character::takeDamage(const int dmg) {
    hp -= dmg;
    int currentHp = hp;
    this->setHP(hp);
    return currentHp;
}

// getter for def field
int Character::getDef() {
    return def;
}

// getter for hp field
int Character::getHP() {
    return hp;
}

// getter for atk field
int Character::getAtk() {
    return atk;
}

// setter for hp field
void Character::setHP(int health) {
    hp = health;
    if (hp <= 0) {
        hp = 0;
        dead();
    }
}

// getter for charID field
char Character::getCharacterID () {
    return charID;
}

// setter for loc field
void Character::setCharacterLoc(int x, int y) {
    loc = make_pair(x, y);
}

// getter for loc field
pair<int, int> Character::getCharacterLoc() {
    return loc;
}
