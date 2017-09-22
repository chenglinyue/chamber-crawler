#include "shade.h"
#include "enemy.h"
using namespace std;

Shade::Shade(Controller &controller, pair<int, int>location, char id):Player(controller, location, 125, id){
    this->setHP(125);
    this->setAtk(25);
    this->setDef(25);
    initializePlayer();
}

void Shade::attackedBy(Enemy &e) {
    e.attack(*this);
}

Shade* Shade::copy () {
    Shade* tempCharacter = new Shade (*controller, loc, charID);
    return tempCharacter;
}
