#include "elf.h"
#include "shade.h"
#include "goblin.h"
#include "troll.h"
#include "vampire.h"
using namespace std;

Elf::Elf(Controller &controller, std::pair<int, int>location, char id):Enemy(controller, location, id) {
    hp = 140;
    atk = 30;
    def = 10;
}

void Elf::attackedBy(Player &p) {
    p.attack(*this);
}

void Elf::attack(Goblin &goblin) {
    srand (time(NULL));
    // Elves get two turns again all races except drow
    for (int i = 0; i < 2; i++) {
        int miss = rand() % 2;
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + goblin.getDef()))*atk);
            goblin.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

void Elf::attack(Shade &shade) {
    srand (time(NULL));
    // Elves get two turns again all races except drow
    for (int i = 0; i < 2; i++) {
        int miss = rand() % 2;
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + shade.getDef()))*atk);
            shade.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

void Elf::attack(Troll &troll) {
    srand (time(NULL));
    // Elves get two turns again all races except drow
    for (int i = 0; i < 2; i++) {
        int miss = rand() % 2;
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + troll.getDef()))*atk);
            troll.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

void Elf::attack(Vampire &vampire) {
    srand (time(NULL));
    // Elves get two turns again all races except drow
    for (int i = 0; i < 2; i++) {
        int miss = rand() % 2;
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + vampire.getDef()))*atk);
            vampire.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

Elf* Elf::copy() {
    Elf* tempCharacter = new Elf (*controller, loc, charID);
    return tempCharacter;
}
