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

const int tile_width = 72;
const int tile_height = 84;

unsigned int level[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3,
    3, 3, 3, 3, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 1,
};

StateLayer::StateLayer(state::State &state, sf::RenderWindow &window,
                       std::string env)
    : window(window), currentState(state) {
  font.loadFromFile("res/fonts/BalsamiqSans-Bold.ttf");

  std::unique_ptr<TileSet> tilesetMapCell(new TileSet(TileSetID::MAP, env));
  tilesets.push_back(move(tilesetMapCell));
}

void StateLayer::registerAlertMessage(std::string message) {
  // wrap text
  int n = message.rfind(' ', 30);
  if (n != std::string::npos) {
    message.at(n) = '\n';
  }

  timeLastAlertMsg = std::time(nullptr);
  alertMessage = message;
}

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
    // draw mapcells
    window.draw(*surface[0]);

    printText();
    //    showWinnerMessage();
    window.draw(rectangle);
    window.draw(message);
    window.display();
  }
}

std::vector<std::unique_ptr<TileSet>> &StateLayer::getTilesets() {
  std::vector<std::unique_ptr<TileSet>> &refTileSets = tilesets;
  return refTileSets;
}

std::vector<std::unique_ptr<Surface>> &StateLayer::getSurfaces() {
  std::vector<std::unique_ptr<Surface>> &refSurfaces = surface;
  return refSurfaces;
}

void StateLayer::initSurfaces(state::State &state) {
  Surface map;
  map.load("res/texture/tileset.png", sf::Vector2u(tile_width, tile_height),
           level, 10, 10);
  std::unique_ptr<Surface> ptrMap(new Surface(map));

  if (surface.size() != 0) {
    while (surface.size() != 0) {
      surface.pop_back();
    }
  }

  surface.push_back(move(ptrMap));
}

void StateLayer::stateChanged(const state::EventState &e, state::State &state) {
  if (e.eventState == EventStateId::MAP_CHANGED) {
    std::cout << "STATE CHANGED EVENT: map changed" << endl;
    initSurfaces(state);
    draw(window);
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

void StateLayer::draw(sf::RenderWindow &window) {
  window.clear();
  // draw mapcells
  window.draw(*surface[0]);

  for (auto &d : drawables) {
    window.draw(d);
  }

  window.display();
}

bool StateLayer::printText() {
  std::queue<sf::Text> texts;

  sf::Text player1;
  player1.setPosition(window.getSize().x - 240.f, 0.f);
  player1.setFont(font);
  player1.setString("Player 1");
  /* if (currentState.getTurnOwner() == 1)
     player1.setFillColor(sf::Color::Green);*/
  texts.push(player1);

  sf::Text player2;
  player2.setPosition(window.getSize().x - 240.f, (window.getSize().y / 2));
  player2.setFont(font);
  player2.setString("Player 2");
  /*  if (currentState.getTurnOwner() == 2)
      player2.setFillColor(sf::Color::Green);*/
  texts.push(player2);

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
  return true;
}