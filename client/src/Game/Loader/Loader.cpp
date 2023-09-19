#include "Loader.hpp"

using namespace game;
using namespace loader;

Loader::Loader()
{
    loadTexture("./client/assets/parallax/background.png", {0, 0}, Loader::toLoad::ParallaxFirstbkg);
    loadTexture("./client/assets/parallax/background2.png", {0, 0}, Loader::toLoad::ParallaxSecondbkg);
    loadTexture("./client/assets/player.png", {200, 200}, Loader::toLoad::Player);
}

Loader::~Loader()
{
}

void Loader::loadTexture(const std::string path, sf::Vector2f pos, toLoad type)
{
    if (this->_textures.find(type) != this->_textures.end())
        return; //😘

    this->_textures[type] = std::make_unique<sf::Texture>();
    this->_textures[type]->loadFromFile(path);
}

const sf::Texture &Loader::getTexture(toLoad type) const
{
    if (this->_textures.find(type) == this->_textures.end())
        throw client::MyError("Loader", "Texture not found");
    return *this->_textures.at(type);
}
