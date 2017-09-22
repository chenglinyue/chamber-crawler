#include "dragon.h"
#include "shade.h"
#include "drow.h"
#include "goblin.h"
#include "troll.h"
#include "treasure.h"
#include "vampire.h"
using namespace std;

Dragon::Dragon(Controller & controller, std::pair<int, int> loc, char id):Enemy(controller, loc, id) {
    hp = 150;
    atk = 20;
    def = 20;
}

void Dragon::attackedBy(Player &p) {
    p.attack(*this);
}

Dragon* Dragon::copy() {
    Dragon* tempCharacter = new Dragon(*controller, loc, charID);
    return tempCharacter;
}

void Dragon::dead() {
    string action = "PC has slain D. ";
    controller->setAction(action);
    dragonHoard->setObtainable(true);
    controller->enemyDead(*this);
}

void Dragon::setDragonHoard(Treasure &treasure) {
    dragonHoard = &treasure;
}

Treasure* Dragon::getDragonHoard() {
    return dragonHoard;
}
