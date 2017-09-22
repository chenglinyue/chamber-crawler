#include "restorehealth.h"
#include "player.h"

RestoreHealth::RestoreHealth (Controller & c, char id):Item(c, id){}

void RestoreHealth::pickUp(Player &player) {
    player.pickUp(*this);
    pickedUp(this);
}

RestoreHealth* RestoreHealth::copy () {
    RestoreHealth * t = new RestoreHealth (*controller, getItemID());
    return t;
}
