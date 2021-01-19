#include "RandomAI.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "state.h"
#include "utils.h"

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;


int RandomAI::selectCharacter (state::State& state){
    std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();
    std::vector<int> posibleIndex;
    int i=0;
    for(auto cell : cells){
        if (cell->isAccessible()) {
        state::AccessibleCell *ac = (state::AccessibleCell *)cell.get();
        int sid = ac->getEntity().getEntityTypeId();
            if (sid == state::EntityTypeId::SOLDIER) {
                if ( ac->getPlayerId()==2 ){
                    posibleIndex.push_back(i);
                }
                       
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