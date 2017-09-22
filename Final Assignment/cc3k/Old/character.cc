#include "character.h"
#include "controller.h"
#include <iostream>
using namespace std;

Character::Character(Controller &controller, std::pair<int, int> location, char id):controller(&controller) {
    loc = location;
    charID = id;
}

Character::~Character() {}

void Character::takeDamage(const int dmg) {
    hp -= dmg;
    this->setHP(hp);
}

int Character::getDef() {
    return def;
}

int Character::getHP() {
    return hp;
}

int Character::getAtk() {
    return atk;
}

void Character::setHP(int health) {
    hp = health;
    if (hp <= 0) {
        hp = 0;
        dead();
    }
}

void Character::setAtk(int attack) {
    atk = attack;
}

void Character::setDef(int defence) {
    def = defence;
}

char Character::getCharacterID () {
    return charID;
}

void Character::setCharacterLoc(int x, int y) {
    loc = make_pair(x, y);
}

pair<int, int> Character::getCharacterLoc() {
    return loc;
}
