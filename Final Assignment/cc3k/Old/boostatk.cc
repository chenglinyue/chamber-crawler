#include "boostatk.h"
#include "player.h"

BoostAtk::BoostAtk (Controller & c, char id):Item(c, id){}

void BoostAtk::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

BoostAtk* BoostAtk::copy () {
    BoostAtk * t = new BoostAtk (*(getController()), getItemID());
    return t;
}
