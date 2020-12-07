#include "AudioEngine.h"
#include <SFML/Graphics.hpp>

using namespace render;

AudioEngine::AudioEngine() { // sf::SoundBuffer buffer;
}

void AudioEngine::play(std::string filepath) {
  // sf::SoundBuffer buffer;
  if (!buffer.loadFromFile(filepath)) {
    return;
  }
  // sf::Sound sound;
  sound.setBuffer(buffer);
  sound.play();
}
