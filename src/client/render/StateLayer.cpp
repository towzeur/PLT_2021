#include "../render.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unistd.h>
using namespace render;
using namespace std;
using namespace state;

#define SURFACE_MAP 0
#define SURFACE_ENTITY 1

// Constructor
StateLayer::StateLayer(state::State &state, sf::RenderWindow &window,
                       std::string env)
    : window(window), currentState(state) {

  // load a font file (ttf)
  font.loadFromFile("res/fonts/BalsamiqSans-Bold.ttf");
}

// Load a string in alertMessage
void StateLayer::registerAlertMessage(std::string message) {
  // wrap text
  unsigned int n = message.rfind(' ', 30);
  if (n != std::string::npos) {
    message.at(n) = '\n';
  }

  timeLastAlertMsg = std::time(nullptr);
  alertMessage = message;
}

// Show the string load by registerAlertMessage
void StateLayer::showAlertMessage(time_t epoch) {
  if ((epoch - timeLastAlertMsg) < 3) {
    // define a 220x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(220, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(50, 50);

    // text
    sf::Text message;
    message.setPosition(
        {rectangle.getPosition().x + 10, rectangle.getPosition().y + 10});
    message.setFont(font);
    message.setCharacterSize(10);
    message.setString(alertMessage);

    window.clear();
    // draw map
    window.draw(*surfaces[0]);

    //    printText();

    window.draw(rectangle);
    window.draw(message);
    window.display();
  }
}

// Get a vector which contain all the surfaces
std::vector<std::unique_ptr<Surface>> &StateLayer::getSurfaces() {
  std::vector<std::unique_ptr<Surface>> &refSurfaces = surfaces;
  return refSurfaces;
}

// Initialise all surfaces:
void StateLayer::initSurfaces(state::State &state) {
  // create and load a surface
  Surface map;
  map.load(pathTextureMap, sf::Vector2u(tileWidth, tileHeight),
           state.getBoard(), state.getBoard().getNCol(),
           state.getBoard().getNRow(), SURFACE_MAP);
  Surface entity;
  entity.load(pathTextureEntity, sf::Vector2u(tileWidth, tileHeight),
              state.getBoard(), state.getBoard().getNCol(),
              state.getBoard().getNRow(), SURFACE_ENTITY);

  // create a unique_pointer which point on a new instance of surface created
  // before
  std::unique_ptr<Surface> ptrMap(new Surface(map));

  std::unique_ptr<Surface> ptrEntity(new Surface(entity));

  // empty surfaces
  if (surfaces.size() != 0) {
    while (surfaces.size() != 0) {
      surfaces.pop_back();
    }
  }

  // load vector surfaces with the new surfaces
  surfaces.push_back(move(ptrMap));
  surfaces.push_back(move(ptrEntity));
}

// Check if the state have changed
void StateLayer::stateChanged(const state::EventState &e, state::State &state) {
  if (e.eventState == EventStateId::MAP_CHANGED) {
    std::cout << "STATE CHANGED EVENT: map changed" << endl;
    initSurfaces(state);
    draw(window, state);
  }
}

// Draw all surfaces and drawables and display them
void StateLayer::draw(sf::RenderWindow &window, state::State &state) {
  window.clear();
  // draw mapcells
  window.draw(*surfaces[0]);

  window.draw(*surfaces[1]);

  for (auto &d : drawables) {
    window.draw(d);
  }

  printText(state);

  window.display();
}

// Print text on the HUD
bool StateLayer::printText(state::State &state) {
  // queue (fifo) which will contain all the text to display on the HUD
  std::queue<sf::Text> texts;
  std::vector<std::shared_ptr<state::Player>> players = state.getPlayers();

  // add text for players
  for (unsigned int i = 0; i < players.size(); i++) {
    std::vector<std::shared_ptr<state::Territory>> territories =
        players[i]->getTerritories();
    std::shared_ptr<state::Territory> selectedTerritory(new state::Territory);
    selectedTerritory->setIncome(0);
    selectedTerritory->setSavings(0);
    selectedTerritory->setWages(0);
    selectedTerritory->setBalance(0);
    for (auto &t : move(territories)) {
      if (t->isSelected()) {
        selectedTerritory = t;
        break;
      }
    }
    sf::Text player;
    player.setPosition(window.getSize().x - 350.f + i % 2 * 200,
                       ((int)i / 2) * 200.f + 50);
    player.setFont(font);
    player.setString(players[i]->getName());
    player.setCharacterSize(30);
    if (players[i]->getStatus() == state::PlayerStatus::PLAYING) {
      player.setFillColor(sf::Color::Green);
    } else if (players[i]->getStatus() == state::PlayerStatus::LOST) {
      player.setFillColor(sf::Color::Red);
    }
    texts.push(player);

    sf::Text playerInfo;
    playerInfo.setPosition(player.getPosition().x, player.getPosition().y + 50);
    playerInfo.setFont(font);
    playerInfo.setString(
        "Savings: " + std::to_string(selectedTerritory->getSavings()) +
        "$\nIncomes: " + std::to_string(selectedTerritory->getIncome()) +
        "$\nWages: " + std::to_string(selectedTerritory->getWages()) +
        "$\nBalance: " + std::to_string(selectedTerritory->getBalance()) + "$");
    playerInfo.setCharacterSize(20);
    texts.push(playerInfo);
  }

  sf::Text shop;
  shop.setPosition(window.getSize().x - 350.f, window.getSize().y - 200.f);
  shop.setFont(font);
  shop.setString("SHOP:\nPEASANT  CASTLE\n");
  shop.setCharacterSize(30);
  shop.setFillColor(sf::Color::Blue);
  texts.push(shop);

  while (!texts.empty()) {
    window.draw(texts.front());
    texts.pop();
  }
  return true;
}

int StateLayer::getTileHeight() const { return this->tileHeight; }