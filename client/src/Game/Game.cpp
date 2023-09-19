#include "Game.hpp"

using namespace game;
using namespace components;
using namespace entity;

Game::Game() :
    _parallax1("./client/assets/parallax/background.png", {0, 0}, 120),
    _parallax2("./client/assets/parallax/background2.png", {0, 0}, 150),
    _player1("./client/assets/player.png", {200, 200}, 100),
    _manager(loader::Loader())
{
    this->_window.create(sf::VideoMode(1920, 1080), "R-TYPE");
    this->_lastTime = NOW;
    this->_player1.setTexture(this->_manager.getTexture(loader::Loader::toLoad::Player));
}

Game::~Game()
{
}

int Game::MainLoop()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->_screenSize = {desktop.width, desktop.height};

    while (this->_window.isOpen()) {
        long currentTime = NOW;
        float deltaTime = (currentTime - _lastTime) / 1000.0f;
        _lastTime = currentTime;

        this->EventLoop(this->_window, this->_player1, deltaTime, this->_screenSize);
        this->_window.clear();
        this->_parallax1.update(deltaTime);
        this->_parallax1.draw(this->_window);
        this->_parallax2.update(deltaTime);
        this->_parallax2.draw(this->_window);

        this->_player1.update(deltaTime);
        this->_player1.draw(this->_window);

        this->_window.display();
    }
    return 0;
}
