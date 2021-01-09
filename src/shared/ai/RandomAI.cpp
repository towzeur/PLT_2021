#include "AI.h"
#include <time.h>
#include <iostream>


using namespace ai;
using namespace state;
using namespace std;


void RandomAI (){}
bool runAI (){}




int selectCharacter (state::State& state){
    std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();
    std::vector<int> posibleIndex;
    int i=0;
    for(auto cell : cells){
        if ( cell->getEntity().isSoldier()) {
            if ( cell->getPlayerId()==2 ){
                posibleIndex.push_back(i);
            }
        }
        i++;
    }

    int randomNumber = rand() % posibleIndex.size();
    cout << "[";
    for(auto &index : posibleIndex){
        cout << index << ", ";
    }
    cout << "]" << endl;
    return posibleIndex[randomNumber];
}