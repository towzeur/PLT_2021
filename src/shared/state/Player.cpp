#include "Player.h"

using namespace state;

int Player::instanceCount = 0;
Player::Player() { this->uid = instanceCount++; }

Player::~Player() {}

int Player::getUid() { return uid; }

std::string Player::getName() { return name; }

void Player::setName(std::string name) { this->name = name; }

bool Player::isPlaying() { return status == PlayerStatus::PLAYING; }

PlayerStatus Player::getStatus() { return status; }

void Player::setStatus(PlayerStatus status) { this->status = status; }

/**
 * @brief create a territory and return it
 *
 */
std::shared_ptr<state::Territory> Player::createTerritory() {
  std::shared_ptr<state::Territory> newTerritory(new state::Territory);
  this->territories.push_back(newTerritory);
  return newTerritory;
}

std::vector<std::shared_ptr<Territory>> Player::getTerritories() {
  return territories;
}