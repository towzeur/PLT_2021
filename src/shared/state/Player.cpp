#include "Player.h"

using namespace state;

int Player::instanceCount = 0;

Player::Player() { this->uid = instanceCount++; }

Player::~Player() {}

int Player::getUid() { return uid; }

std::string Player::getName() { return name; }

void Player::setName(std::string name) { this->name = name; }

bool Player::getPlaying() { return playing; }

void Player::setPlaying(bool playing) { this->playing = playing; }

PlayerStatus Player::getStatus() { return status; }

void Player::setStatus(PlayerStatus status) { this->status = status; }

Player *const Player::clone() {}

void Player::addTerritory(std::unique_ptr<Territory> territory) {
  printf("a\n");
  this->territories.push_back(move(territory));
  printf("b\n");
}

std::vector<std::unique_ptr<Territory>> Player::getTerritories() {
  return move(territories);
}