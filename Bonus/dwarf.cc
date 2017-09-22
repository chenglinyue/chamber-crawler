#include "dwarf.h"
using namespace std;

Dwarf::Dwarf(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 100;
    atk = 20;
    def = 30;
}

void Dwarf::attackedBy(Player &p) {
     p.attack(*this);
}

Dwarf* Dwarf::copy () {
    Dwarf* tempCharacter = new Dwarf (*controller, loc, charID);
    return tempCharacter;
}
