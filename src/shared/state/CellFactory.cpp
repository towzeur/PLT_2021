#include "CellFactory.h"

using namespace state;

CellFactory::CellFactory::~CellFactory() {
    
}

Cell* const CellFactory::CellFactory::newInstance(char id) {


}

void CellFactory::CellFactory::registerType(char id, ACellAlloc* cell) {
    
}

CellFactory* CellFactory::CellFactory::createDefault() {
    
}

const std::map<char,ACellAlloc*>& CellFactory::CellFactory::getList() const {
    
}

void CellFactory::CellFactory::setList(const std::map<char, ACellAlloc*>& list) {
    
}
