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

unsigned int levelMap[] = {
    0, 1, 1, 2, 2, 2, 1, 0, 0, 0, //-----------------------------------------
    1, 1, 1, 1, 2, 0, 1, 1, 0, 0, //-----------------------------------------
    0, 0, 1, 1, 1, 1, 1, 1, 1, 0, //-----------------------------------------
    0, 0, 1, 1, 1, 1, 0, 1, 1, 0, //-----------------------------------------
    0, 3, 3, 3, 0, 1, 1, 5, 5, 0, //-----------------------------------------
    0, 0, 3, 1, 1, 1, 0, 5, 5, 0, //-----------------------------------------
    0, 0, 1, 0, 1, 0, 1, 1, 1, 1, //-----------------------------------------
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, //-----------------------------------------
    0, 1, 1, 4, 4, 4, 4, 0, 0, 0, //-----------------------------------------
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, //-----------------------------------------
};

unsigned int levelEntity[] = {
    3, 3, 3, 3, 1, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 1, 3, //-----------------------------------------
    3, 3, 1, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 1, 3, 3, 3, 3, 3, //-----------------------------------------
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //-----------------------------------------
};

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
  map.load(pathTextureMap, sf::Vector2u(tileWidth, tileHeight), levelMap,
           mapWidth, mapHeight);

  Surface entity;
  entity.load(pathTextureEntity, sf::Vector2u(tileWidth, tileHeight),
              levelEntity, mapWidth, mapHeight);

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

/*
void StateLayer::showWinnerMessage() {
  if (currentState.getWinner() != 0) {
    sf::Text win;
    win.setPosition((window.getSize().x / 2.f) - 150.f,
                    window.getSize().y / 2.f);
    win.setFont(font);
    string str = "Player " + to_string(currentState.getWinner()) + " wins";
    win.setString(str);
    win.setCharacterSize(48);
    win.setFillColor(sf::Color::Red);
    drawables.push_back(move(win));
  }
} */

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

  // add text for players
  for (unsigned int i = 0; i < state.getPlayers().size(); i++) {
    sf::Text player;
    player.setPosition(window.getSize().x - 200.f, i * 200.f);
    player.setFont(font);
    player.setString(state.getPlayers()[i].getName());
    player.setCharacterSize(30);
    /* if (currentState.getTurnOwner() == 1)
     player1.setFillColor(sf::Color::Green);*/
    texts.push(player);

    sf::Text playerInfo;
    playerInfo.setPosition(window.getSize().x - 200.f,
                           player.getPosition().y + 50);
    playerInfo.setFont(font);
    playerInfo.setString("Savings: " + std::to_string(0) + "$\nIncomes: " +
                         std::to_string(0) + "$\nWages: " + std::to_string(0) +
                         "$\nBalance: " + std::to_string(0) + "$");
    playerInfo.setCharacterSize(20);
    texts.push(playerInfo);
  }

  while (!texts.empty()) {
    window.draw(texts.front());
    texts.pop();
  }
  return true;
}

/*  float playerOneBasePos = player1.getPosition().y + 32.f;
  float playerTwoBasePos = player2.getPosition().y + 32.f;

  for (auto &charac : currentState.getCharacters()) {
    if (charac->getPlayerOwner() == 1) {
      sf::Text textStats;
      textStats.setPosition(window.getSize().x - 240.f, playerOneBasePos);
      textStats.setFont(font);
      std::string str = charac->getName() + "\n";
      str += "Health: " +
             std::to_string((charac->getStats().getHealth() <= 0)
                                ? 0
                                : charac->getStats().getHealth()) +
             "\n";
      str += "Moves: " + std::to_string(charac->getCharacterMove()) + "\n";
      str += "Attack dist.: " +
             std::to_string(charac->getCharacterAttackDistance());
      textStats.setString(str);

      if (charac->getStatus() == SELECTED)
        textStats.setFillColor(sf::Color::Green);

      else if (charac->getStatus() == DEATH)
        textStats.setFillColor(sf::Color::Red);

      textStats.setCharacterSize(15); // in pixels, not points!

      playerOneBasePos += 100.f;
      texts.push(textStats);
    } else {
      sf::Text textStats;
      textStats.setPosition(window.getSize().x - 240.f, playerTwoBasePos);
      textStats.setFont(font);
      std::string str = charac->getName() + "\n";
      str += "Health: " +
             std::to_string((charac->getStats().getHealth() <= 0)
                                ? 0
                                : charac->getStats().getHealth()) +
             "\n";
      str += "Moves: " + std::to_string(charac->getCharacterMove()) + "\n";
      str += "Attack dist.: " +
             std::to_string(charac->getCharacterAttackDistance());
      textStats.setString(str);

      if (charac->getStatus() == SELECTED)
        textStats.setFillColor(sf::Color::Green);

      else if (charac->getStatus() == DEATH)
        textStats.setFillColor(sf::Color::Red);

      textStats.setCharacterSize(15); // in pixels, not points!
      playerTwoBasePos += 100.f;
      texts.push(textStats);
    }
    if (charac->getStatus() == SELECTED) {
      sf::Text selectedChar;
      selectedChar.setPosition(window.getSize().y / 2.f + 6.f * 32.f,
                               window.getSize().y - 32.f);
      selectedChar.setFont(font);
      string str = "Selected " + charac->getName() + " (P" +
                   std::to_string(charac->getPlayerOwner()) + ")";
      selectedChar.setString(str);
      selectedChar.setCharacterSize(18);
      selectedChar.setFillColor(sf::Color::Green);
      texts.push(selectedChar);
    }
  }

  sf::Text controls;
  controls.setPosition(16.f, window.getSize().y - 32.f);
  controls.setFont(font);
  controls.setString(
      "Select: ENTER   -   Move: M   -   Attack: A   -   Skip: S");
  controls.setCharacterSize(18);
  controls.setFillColor(sf::Color::White);
  texts.push(controls);

  sf::Text turnInfo;
  turnInfo.setPosition(((window.getSize().x) - 8 * 32.f),
                       window.getSize().y - 32.f);
  turnInfo.setFont(font); // font is a sf::Font

  std::string str = "Turn: " + std::to_string(currentState.getTurn());
  turnInfo.setString(str);
  turnInfo.setCharacterSize(24); // in pixels, not points!
  turnInfo.setFillColor(sf::Color::White);

  texts.push(turnInfo);

  sf::Text turnInfo2;
  turnInfo2.setPosition(((window.getSize().x) - 4 * 32.f),
                        window.getSize().y - 32.f);
  turnInfo2.setFont(font); // font is a sf::Font

  std::string str2 = "Player " + std::to_string(currentState.getTurnOwner());

  turnInfo2.setString(str2);
  turnInfo2.setCharacterSize(24); // in pixels, not points!
  turnInfo2.setFillColor(sf::Color::White);

  texts.push(turnInfo2);

  while (!texts.empty()) {
    window.draw(texts.front());
    texts.pop();
  }
  */
/*return true;
}*/