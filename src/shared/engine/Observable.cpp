#include "Observable.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

void Observable::registerObserver (Observer* obs){ observers.push_back(obs); }
