#include "Player.h"

using namespace state;

int Player::instanceCount = 1;

Player::Player() { this->uid = instanceCount++; }

Player::~Player() { Player::instanceCount = 1; }

int Player::getUid() { return uid; }

std::string Player::getName() { return name; }

void Player::setName(std::string name) { this->name = name; }

bool Player::getPlaying() { return playing; }

void Player::setPlaying(bool playing) { this->playing = playing; }

PlayerStatus Player::getStatus() { return status; }

void Player::setStatus(PlayerStatus status) { this->status = status; }

void Player::addTerritory(std::shared_ptr<Territory> territory) {
  this->territories.push_back(territory);
}

std::vector<std::shared_ptr<Territory>> Player::getTerritories() {
  return territories;
}