#include "boostdef.h"
#include "player.h"

BoostDef::BoostDef (Controller & c, char id):Item(c, id, "BD"){}

void BoostDef::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

BoostDef* BoostDef::copy () {
    BoostDef * t = new BoostDef (*controller, getItemID());
    return t;
}
