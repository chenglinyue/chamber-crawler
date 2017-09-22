#include "treasure.h"
#include "dragon.h"
#include "player.h"
#include "controller.h"
#include <stdlib.h>

using namespace std;
// 3 param ctor
Treasure::Treasure(Controller & c, int amt, char id):Item(c, id){
    amount = amt;
    if (amount == 6) obtainable = false;
    else obtainable = true;
}

// Tells player to pick up this treasure
void Treasure::pickUp(Player &player) {
    if (obtainable) player.pickUp(*this);
}

// getter for amount field (how much the treasure is worth)
int Treasure::getAmount() {
    return amount;
}

// setter for obtainable field
void Treasure::setObtainable(bool canObtain) {
    obtainable = canObtain;
}

// getter for obtainable field
bool Treasure::getObtainable() {
    return obtainable;
}

// create a copy of treasure
Treasure* Treasure::copy () {
    Treasure * t = new Treasure (*controller, amount, getItemID());
    return t;
}

// Dragon hoards need to place a dragon
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
            Dragon *dragon = new Dragon (*controller, new_loc, 'D');
            dragon->setDragonHoard(*this);
            placed = controller->placeEnemy (new_loc, *dragon);
            if (!placed) delete dragon;
        } while (!placed);
    }
}
