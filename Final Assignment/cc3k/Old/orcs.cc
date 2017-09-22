#include "orcs.h"
#include "goblin.h"
//#include "controller.h"
#include <iostream>
#include <sstream>
using namespace std;

Orcs::Orcs(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 180;
    atk = 30;
    def = 25;
}

void Orcs::attackedBy(Player &p) {
    p.attack(*this);
}

void Orcs::attack(Goblin &goblin) {
    // Orcs do 50% more damage to goblins
    int dmg = ceil((100.0/(100 + goblin.getDef()))*atk) * 1.5;
    goblin.takeDamage(dmg);
    stringstream action;
    string enemyID;
    enemyID.push_back(charID);
    action << controller->getAction() << enemyID << " deals " << dmg
           << " damage to PC. ";
    controller->setAction(action.str());
}

Orcs* Orcs::copy () {
    Orcs* tempCharacter = new Orcs (*controller, loc, charID);
    return tempCharacter;
}
