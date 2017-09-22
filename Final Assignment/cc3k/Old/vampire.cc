#include "vampire.h"
#include "orcs.h"
#include "human.h"
#include "dwarf.h"
#include "dragon.h"
#include "merchant.h"
#include "elf.h"
#include "halfling.h"
#include <iostream>
#include <sstream>
using namespace std;

Vampire::Vampire(Controller &controller, pair<int, int>location, char id):Player(controller, location, id){
    this->setHP(50);
    this->setAtk(25);
    this->setDef(25);
    initializePlayer();
}

void Vampire::attack(Dwarf &dwarf) {
    // Vampire is allergic to dwarves loses 5 helf instead of gains
    takeDamage(5);
    stringstream action;
    action << "PC is allergic to dwarves. PC loses 5 health! ";
    int dmg = ceil((100.0/(100 + dwarf.getDef()))*atk);
    dwarf.takeDamage(dmg);
        if (dwarf.getHP() > 0) {
        action << "PC deals " << dmg << " damage to W ("
               << dwarf.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Dragon &dragon) {
    // Vampires gain 5 HP every successful attack
    this->setHP(hp + 5);
    stringstream action;
    action << "PC regains 5 health! ";
    int dmg = ceil((100.0/(100 + dragon.getDef()))*atk);
    dragon.takeDamage(dmg);
    if (dragon.getHP() > 0) {
        action << "PC deals " << dmg << " damage to D ("
               << dragon.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Human &human) {
    // Vampires gain 5 HP every successful attack
    this->setHP(hp + 5);
    stringstream action;
    action << "PC regains 5 health! ";
    int dmg = ceil((100.0/(100 + human.getDef()))*atk);
    human.takeDamage(dmg);
    if (human.getHP() > 0) {
        action << "PC deals " << dmg << " damage to H ("
               << human.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Orcs &orcs) {
    // Vampires gain 5 HP every successful attack
    this->setHP(hp + 5);
    stringstream action;
    action << "PC regains 5 health! ";
    int dmg = ceil((100.0/(100 + orcs.getDef()))*atk);
    orcs.takeDamage(dmg);
    if (orcs.getHP() > 0) {
        action << "PC deals " << dmg << " damage to O ("
               << orcs.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Merchant &merchant) {
    // Vampires gain 5 HP every successful attack
    this->setHP(hp + 5);
    stringstream action;
    action << "PC regains 5 health! ";
    int dmg = ceil((100.0/(100 + merchant.getDef()))*atk);
    merchant.takeDamage(dmg);
    if (merchant.getHP() > 0) {
        action << "PC deals " << dmg << " damage to M ("
               << merchant.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Halfling &halfling) {
    // 50% chance to miss when attaking halflings
    stringstream action;
    srand (time(NULL));
    int miss = rand() % 2;
    // Player doesn't miss
    if (miss == 0) {
        this->setHP(hp + 5);
        action << "PC regains 5 health! ";
        int dmg = ceil((100.0/(100 + halfling.getDef()))*this->getAtk());
        halfling.takeDamage(dmg);
        if (halfling.getHP() > 0) {
            action << "PC deals " << dmg << " damage to L ("
                   << halfling.getHP() << " HP). ";
            controller->setAction(action.str());
        }
    } else if (halfling.getHP() > 0 && miss == 1) {
        action << "PC attacks L. PC misses! " <<"("
               << halfling.getHP() << " HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attack(Elf &elf) {
    // Vampires gain 5 HP every attack
    this->setHP(hp + 5);
    int dmg = ceil((100.0/(100 + elf.getDef()))*atk);
    elf.takeDamage(dmg);
    stringstream action;
    action << "PC regains 5 health! ";
    if (elf.getHP() > 0) {
        action << "PC deals " << dmg << " damage to E ("
               << elf.getHP() << "HP). ";
        controller->setAction(action.str());
    }
}

void Vampire::attackedBy(Enemy &e) {
    e.attack(*this);
}

void Vampire::setHP(int health) {
    hp = health;
    if (hp <= 0) {
        hp = 0;
        dead();
    }
    // Vampires have no max HP
    controller->setHP(hp);
}

Vampire* Vampire::copy () {
    Vampire* tempCharacter = new Vampire (*controller, loc, charID);
    return tempCharacter;
}
