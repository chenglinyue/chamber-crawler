#include "treasure.h"
#include "dragon.h"
#include "player.h"
#include "controller.h"
#include <stdlib.h>

using namespace std;

Treasure::Treasure(Controller & c, int amt, char id):Item(c, id){
    amount = amt;
    if (amount == 6) obtainable = false;
    else obtainable = true;
}

void Treasure::pickUp(Player &player) {
    if (obtainable) player.pickUp(*this);
}

int Treasure::getAmount() {
    return amount;
}

void Treasure::setObtainable(bool canObtain) {
    obtainable = canObtain;
}

bool Treasure::getObtainable() {
    return obtainable;
}

Treasure* Treasure::copy () {
    Treasure * t = new Treasure (*(getController()), amount, getItemID());
    return t;
}

void Treasure::placeDependencies () {
    if (amount == 6) {
        srand (time(NULL));
        bool placed = false;
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
            Dragon *dragon = new Dragon (*(getController()), new_loc, 'D');
            dragon->setDragonHoard(*this);
            placed = controller->placeCharacter (new_loc, *dragon);
        } while (!placed);
    }
}
