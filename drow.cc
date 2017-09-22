#include "drow.h"
#include "enemy.h"
using namespace std;

Drow::Drow(Controller &controller, pair<int, int>location, char id):Player(controller, location, 150, id){
    this->setHP(150);
    this->setAtk(25);
    this->setDef(15);
    initializePlayer();
}

void Drow::attackedBy(Enemy &e) {
    e.attack(*this);
}

void Drow::pickUp(WoundDef &wounddef) {
    string action = "PC uses WD. ";
    controller->setAction(action);
    this->setDef(def - 5 * 1.5);
}

void Drow::pickUp(WoundAtk &woundatk) {
    string action = "PC uses WA. ";
    controller->setAction(action);
    this->setAtk(atk - 5 * 1.5);
}

void Drow::pickUp(RestoreHealth &restorehealth) {
    string action = "PC uses RH. ";
    controller->setAction(action);
    this->setHP(hp + 10 * 1.5);
}

void Drow::pickUp(PoisonHealth &poisonhealth) {
    string action = "PC uses PH. ";
    controller->setAction(action);
    this->setHP(hp - 10 * 1.5);
}

void Drow::pickUp(BoostDef &boostdef) {
    string action = "PC uses BD. ";
    controller->setAction(action);
    this->setDef(def + 5 * 1.5);
}

void Drow::pickUp(BoostAtk &boostatk) {
    string action = "PC uses BA. ";
    controller->setAction(action);
    this->setAtk(atk + 5 * 1.5);
}

Drow* Drow::copy () {
    Drow* tempCharacter = new Drow (*controller, loc, charID);
    return tempCharacter;
}
