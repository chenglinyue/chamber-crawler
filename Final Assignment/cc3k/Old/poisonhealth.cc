#include "poisonhealth.h"
#include "player.h"

PoisonHealth::PoisonHealth (Controller & c, char id):Item(c, id){}

void PoisonHealth::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

PoisonHealth* PoisonHealth::copy () {
    PoisonHealth * t = new PoisonHealth (*(getController()), getItemID());
    return t;
}
