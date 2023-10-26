#pragma once

#include "../ECS/Components/Components.hpp"
#include "../ECS/Registry.hpp"
#include <memory>

namespace game {
    class Factory {
        public:
        /**
         * @brief Construct a new Factory object
         *
         */
            Factory(ECS::Registry &registry);
        /**
         * @brief Destroy the Factory object
         *
         */
            ~Factory();
            entity_t createButton(float x, float y, const std::shared_ptr<sf::Texture> &texture, const sf::Vector2f &scale, std::function<void()> callback);
            entity_t createLooserScreen(float x, float y, const std::shared_ptr<sf::Texture> &texture);
        /**
         * @brief Create a Player object
         *
         * @param x
         * @param y
         * @param texture
         * @return entity_t
         */
            entity_t createPlayer(float x, float y, const std::shared_ptr<sf::Texture> &texture);
        /**
         * @brief Create a Parallax object
         *
         * @param x
         * @param y
         * @param texture
         * @param scrollSpeed
         * @return entity_t
         */
            entity_t createParallax(float x, float y, const std::shared_ptr<sf::Texture> &texture, float scrollSpeed, float ratio = 1.0f);
        /**
         * @brief Create a Missile object
         *
         * @param x
         * @param y
         * @param texture
         * @return entity_t
         */
            entity_t createMissile(float x, float y, const std::shared_ptr<sf::Texture> &texture);
        /**
         * @brief Create a Ennemi object
         *
         * @param x
         * @param y
         * @param texture
         * @return entity_t
         */
            entity_t createEnnemi(float x, float y, const std::shared_ptr<sf::Texture> &texture);
            entity_t createEnnemi4frames(float x, float y, const std::shared_ptr<sf::Texture> &texture, float scale);
            entity_t createBlackband(sf::IntRect rect, const std::shared_ptr<sf::Texture> &texture);

            entity_t createPlayerLife(float x, float y, const std::shared_ptr<sf::Texture> &texture, float scale);
            entity_t createScoreCoche(float x, float y, const std::shared_ptr<sf::Texture> &texture, float scale);

            entity_t createMusic(const std::string &musicPath, float volume = 100.0f, bool loop = false);
            entity_t createStrobe(const std::shared_ptr<sf::Texture> &texture, float x, float y);
        private:
            ECS::Registry &_registry;
    };
}