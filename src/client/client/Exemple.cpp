#include "Exemple.h"

namespace client {

void Exemple::setX (int x) {
    // Create an object from "shared" library
    state::Exemple y {};
    y.setX(x);

    this->x = x;
}

}

