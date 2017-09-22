#include "orcs.h"
#include "goblin.h"
#include <stdlib.h>
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
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + goblin.getDef()))*atk) * 1.5;
            goblin.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

Orcs* Orcs::copy () {
    Orcs* tempCharacter = new Orcs (*controller, loc, charID);
    return tempCharacter;
}
