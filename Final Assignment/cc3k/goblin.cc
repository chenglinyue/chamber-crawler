#include "goblin.h"
#include "enemy.h"
using namespace std;

Goblin::Goblin(Controller &controller, pair<int, int>location, char id):Player(controller, location, 110, id){
    this->setHP(110);
    this->setAtk(15);
    this->setDef(20);
    initializePlayer();
}

void Goblin::attackedBy(Enemy &e) {
    e.attack(*this);
}

Goblin* Goblin::copy () {
    Goblin* tempCharacter = new Goblin (*controller, loc, charID);
    return tempCharacter;
}
