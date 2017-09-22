#include "woundatk.h"
#include "player.h"

WoundAtk::WoundAtk (Controller & c, char id):Item(c, id, "WA"){}

void WoundAtk::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

WoundAtk* WoundAtk::copy () {
    WoundAtk * t = new WoundAtk (*controller, getItemID());
    return t;
}
