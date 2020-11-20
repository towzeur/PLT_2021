#include "BuySoldierCommand.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

BuySoldierCommand::BuySoldierCommand(state::Soldier& target,Territory territory){
    int savings = territory.getSavings();
    int soldierPrice = Soldier.getPrice();

    if (savings>=soldierPrice){
        // able to buy a soldier
        Soldier soldier = Soldier();
    }
    else{
        std::cout << "Unable to purchase a soldier."
    }
}

void BuySoldierCommand::execute (state::State& state){}