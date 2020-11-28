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

void Player::addTerrotory(Territory &territory) {
  this->territories.push_back(territory);
}

std::vector<Territory> &Player::getTerritories() { return this->territories; }