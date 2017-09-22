#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "player.h"
#include "orcs.h"
#include "human.h"
#include "dwarf.h"
#include "dragon.h"
#include "merchant.h"
#include "elf.h"
#include "halfling.h"
#include "controller.h"
#include "treasure.h"
using namespace std;

// 4 param ctor
Player::Player(Controller &controller, pair<int, int>location,
    int maxHealth, char id):Character(controller, location, id), gold(0), maxHP(maxHealth){

    controller.setAction("Player Character has spawned.");
}

// 3 param ctor for Vampires who don't have max HP
Player::Player(Controller &controller, pair<int, int>location,
    char id):Character(controller, location, id), gold(0) {}

void Player::makeMove() {
    controller->setAction("");
}

// Save base def and atk of player
void Player::initializePlayer() {
    baseDef = def;
    baseAtk = atk;
}

// Player attacks enemy of type Human
void Player::attack(Human &human) {
    int dmg = ceil((100.0/(100 + human.getDef()))*this->getAtk());
    if (human.takeDamage(dmg) > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to H ("
               << human.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Dwarf
void Player::attack(Dwarf &dwarf) {
    int dmg = ceil((100.0/(100 + dwarf.getDef()))*this->getAtk());
    if (dwarf.takeDamage(dmg) > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to W ("
               << dwarf.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Merchant
void Player::attack(Merchant &merchant) {
    int dmg = ceil((100.0/(100 + merchant.getDef()))*this->getAtk());
    if (merchant.takeDamage(dmg) > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to M ("
               << merchant.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Dragon
void Player::attack(Dragon &dragon) {
    int dmg = ceil((100.0/(100 + dragon.getDef()))*this->getAtk());
    if (dragon.takeDamage(dmg) > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to D ("
               << dragon.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Elf
void Player::attack(Elf &elf) {
    int dmg = ceil((100.0/(100 + elf.getDef()))*this->getAtk());
    if (elf.takeDamage(dmg) > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to E ("
               << elf.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Halfling
void Player::attack(Halfling &halfling) {
    // 50% chance to miss when attaking halflings
    stringstream action;
    int miss = rand() % 2;
    // Player doesn't miss
    if (miss == 0) {
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
        controller->setAction(controller->getAction() + action.str());
    }
}

// Player attacks enemy of type Orcs
void Player::attack(Orcs &orcs) {
    int dmg = ceil((100.0/(100 + orcs.getDef()))*this->getAtk());
    orcs.takeDamage(dmg);
    if (orcs.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to O ("
               << orcs.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

// setter for hp field
void Player::setHP(const int health) {
    hp = health;
    if (hp <= 0) {
        hp = 0;
        controller->setHP(hp);
        dead();
    }
    if (hp >= maxHP) hp = maxHP;
    controller->setHP(hp);
}

// setter for atk field
void Player::setAtk(const int attack) {
    atk = attack;
    if (atk <= 0) atk = 0;
    controller->setAtk(atk);
}

// setter for def field
void Player::setDef(const int defence) {
    def = defence;
    if (def <= 0) def = 0;
    controller->setDef(def);
}
// setter for gold field
void Player::setGold(const int amount) {
    gold = amount;
    controller->setGold(amount);
}

// getter for gold field
int Player::getGold() {
    return gold;
}

// getter for baseAtk field
int Player::getBaseAtk() {
    return baseAtk;
}

// getter for baseDef field
int Player::getBaseDef() {
    return baseDef;
}

// Player picked up Item of type treasure
void Player::pickUp(Treasure &treasure) {
    int amount = treasure.getAmount();
    stringstream action;
    action << "PC obtained " << amount << " gold. ";
    controller->setAction(controller->getAction() + action.str());
    this->setGold(gold + amount);
}

// Player picked up Item of type WoundDef
void Player::pickUp(WoundDef &wounddef) {
    string action = "PC uses WD. ";
    controller->setAction(controller->getAction() + action);
    this->setDef(def - 5);
}

// Player picked up Item of type WoundAtk
void Player::pickUp(WoundAtk &woundatk) {
    string action = "PC uses WA. ";
    controller->setAction(controller->getAction() + action);
    this->setAtk(atk - 5);
}

// Player picked up Item of type RestoreHealth
void Player::pickUp(RestoreHealth &restorehealth) {
    string action = "PC uses RH. ";
    controller->setAction(controller->getAction() + action);
    this->setHP(hp + 10);
}

// Player picked up Item of type PoisonHealth
void Player::pickUp(PoisonHealth &poisonhealth) {
    string action = "PC uses PH. ";
    controller->setAction(controller->getAction() + action);
    this->setHP(hp - 10);
}

// Player picked up Item of type BoostDef
void Player::pickUp(BoostDef &boostdef) {
    string action = "PC uses BD. ";
    controller->setAction(controller->getAction() + action);
    this->setDef(def + 5);
}

// Player picked up Item of type BoostAtk
void Player::pickUp(BoostAtk &boostatk) {
    string action = "PC uses BA. ";
    controller->setAction(controller->getAction() + action);
    this->setAtk(atk + 5);
}

// Player died
void Player::dead() {
    controller->playerDied();
}
