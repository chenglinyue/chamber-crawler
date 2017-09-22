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

Player::Player(Controller &controller, pair<int, int>location,
    int maxHealth, char id):Character(controller, location, id), gold(0), maxHP(maxHealth){

    controller.setAction("Player Character has spawned.");
}

// One param ctor for Vampires who don't have max HP
Player::Player(Controller &controller, pair<int, int>location,
    char id):Character(controller, location, id), gold(0){}

void Player::makeMove() {
    controller->setAction("");
}

void Player::initializePlayer() {
    baseDef = def;
    baseAtk = atk;
}

void Player::attack(Human &human) {
    int dmg = ceil((100.0/(100 + human.getDef()))*this->getAtk());
    human.takeDamage(dmg);
    if (human.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to H ("
               << human.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

void Player::attack(Dwarf &dwarf) {
    int dmg = ceil((100.0/(100 + dwarf.getDef()))*this->getAtk());
    dwarf.takeDamage(dmg);
    if (dwarf.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to W ("
               << dwarf.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

void Player::attack(Merchant &merchant) {
    int dmg = ceil((100.0/(100 + merchant.getDef()))*this->getAtk());
    merchant.takeDamage(dmg);
    if (merchant.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to M ("
               << merchant.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

void Player::attack(Dragon &dragon) {
    int dmg = ceil((100.0/(100 + dragon.getDef()))*this->getAtk());
    dragon.takeDamage(dmg);
    if (dragon.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to D ("
               << dragon.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

void Player::attack(Elf &elf) {
    int dmg = ceil((100.0/(100 + elf.getDef()))*this->getAtk());
    elf.takeDamage(dmg);
    if (elf.getHP() > 0) {
        stringstream action;
        action << "PC deals " << dmg << " damage to E ("
               << elf.getHP() << " HP). ";
        controller->setAction(controller->getAction() + action.str());
    }
}

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

void Player::setAtk(const int attack) {
    atk = attack;
    if (atk <= 0) atk = 0;
    controller->setAtk(atk);
}

void Player::setDef(const int defence) {
    def = defence;
    if (def <= 0) def = 0;
    controller->setDef(def);
}

void Player::setGold(const int amount) {
    gold = amount;
    controller->setGold(amount);
}

int Player::getGold() {
    return gold;
}

int Player::getBaseAtk() {
    return baseAtk;
}

int Player::getBaseDef() {
    return baseDef;
}

void Player::pickUp(Treasure &treasure) {
    int amount = treasure.getAmount();
    stringstream action;
    action << "PC obtained " << amount << " gold. ";
    controller->setAction(controller->getAction() + action.str());
    this->setGold(gold + amount);
}

void Player::pickUp(WoundDef &wounddef) {
    string action = "PC uses WD. ";
    controller->setAction(controller->getAction() + action);
    this->setDef(def - 5);
}

void Player::pickUp(WoundAtk &woundatk) {
    string action = "PC uses WA. ";
    controller->setAction(controller->getAction() + action);
    this->setAtk(atk - 5);
}

void Player::pickUp(RestoreHealth &restorehealth) {
    string action = "PC uses RH. ";
    controller->setAction(controller->getAction() + action);
    this->setHP(hp + 10);
}

void Player::pickUp(PoisonHealth &poisonhealth) {
    string action = "PC uses PH. ";
    controller->setAction(controller->getAction() + action);
    this->setHP(hp - 10);
}

void Player::pickUp(BoostDef &boostdef) {
    string action = "PC uses BD. ";
    controller->setAction(controller->getAction() + action);
    this->setDef(def + 5);
}

void Player::pickUp(BoostAtk &boostatk) {
    string action = "PC uses BA. ";
    controller->setAction(controller->getAction() + action);
    this->setAtk(atk + 5);
}

void Player::dead() {
    cout << "PLAYER DEAD" << endl;
    controller->playerDied();
}
