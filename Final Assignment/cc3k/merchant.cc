#include "merchant.h"
#include "treasure.h"
using namespace std;

Merchant::Merchant(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 30;
    atk = 70;
    def = 5;
    isHostile = false;
}

void Merchant::attackedBy(Player &p) {
    controller->turnMerchantsHostile();
    p.attack(*this);
}

Merchant* Merchant::copy () {
    Merchant* tempCharacter = new Merchant (*controller, loc, charID);
    return tempCharacter;
}

void Merchant::dead() {
    stringstream action;
    action << controller->getAction() << "PC has slain " << charID << ". ";

    // Merchants drop a Merchant Hoard upon death
    Treasure *merchantHoard = new Treasure (*controller, 4, 'G');
    controller->placeTreasure(loc, merchantHoard);

    controller->setAction(action.str());
    controller->enemyDead(*this);
}
