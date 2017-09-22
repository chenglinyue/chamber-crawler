#include "wounddef.h"
#include "player.h"

WoundDef::WoundDef (Controller & c, char id):Item(c, id){}

void WoundDef::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

WoundDef* WoundDef::copy () {
    WoundDef * t = new WoundDef (*controller, getItemID());
    return t;
}
