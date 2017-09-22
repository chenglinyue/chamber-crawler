#include "human.h"
#include "treasure.h"
#include <stdlib.h>
using namespace std;

Human::Human(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 140;
    atk = 20;
    def = 20;
}

void Human::attackedBy(Player &p) {
     p.attack(*this);
}

Human* Human::copy () {
    Human* tempCharacter = new Human (*controller, loc, charID);
    return tempCharacter;
}
void Human::dead() {
    srand (time(NULL));
    stringstream action;
    action << controller->getAction() << "PC has slain " << charID << ". ";

    // Humans drop 2 normal piles of gold (value of 2 each)
    Treasure *normalPile1 = new Treasure (*controller, 2, 'G');
    // Place first gold pile at where the Human was when it was slain
    controller->placeTreasure(loc, normalPile1);
    bool placed = false;
    // Place second gold pile randomly around where the Human was when slain
    do {
        int direction = rand() % 4;
        std::pair<int, int> new_loc;
        if (direction == 0)
            new_loc = make_pair (loc.first+1, loc.second);
        if (direction == 1)
            new_loc = make_pair (loc.first-1, loc.second);
        if (direction == 2)
            new_loc = make_pair (loc.first, loc.second+1);
        if (direction == 3)
            new_loc = make_pair (loc.first, loc.second-1);
        Treasure *normalPile2 = new Treasure (*controller, 2, 'G');
        placed = controller->placeTreasure (new_loc, normalPile2);
    } while (!placed);

    controller->setAction(action.str());
    controller->enemyDead(*this);
}
