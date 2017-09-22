#include "troll.h"
#include "enemy.h"
using namespace std;

Troll::Troll(Controller &controller, pair<int, int>location, char id):Player(controller, location, 120, id){
    this->setHP(120);
    this->setAtk(25);
    this->setDef(15);
    initializePlayer();
}

void Troll::attackedBy(Enemy &e) {
    e.attack(*this);
}

Troll* Troll::copy () {
    Troll* tempCharacter = new Troll (*controller, loc, charID);
    return tempCharacter;
}

void Troll::recover() {
    hp += 5;
    if (hp > 120) {
        hp = 120;
    }
    else controller->setAction("PC regains 5 health. " + controller->getAction());
    this->setHP(hp);
}
