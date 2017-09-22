#include "halfling.h"
using namespace std;

Halfling::Halfling(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 100;
    atk = 15;
    def = 20;
}

void Halfling::attackedBy(Player &p) {
     p.attack(*this);
}

Halfling* Halfling::copy () {
    Halfling* tempCharacter = new Halfling (*controller, loc, charID);
    return tempCharacter;
}
