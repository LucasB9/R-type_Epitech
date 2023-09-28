#pragma once

#include "../Registry.hpp"
#include "../Components/Components.hpp"

namespace ECS {
    namespace systems {
        class PositionSystem {
            public:
            /**
             * @brief Update the position of each entity with a position and a velocity component
             * 
             * @param ecs 
             */
                void update(Registry &ecs) {
                    auto &positionComponents = ecs.get_components<components::PositionComponent>();
                    auto &velocityComponents = ecs.get_components<components::VelocityComponent>();

                    for (size_t i = 0; i < positionComponents.size() && i < velocityComponents.size(); ++i) {
                        auto &position = positionComponents[i];
                        auto &velocity = velocityComponents[i];

                        if (position && velocity) {
                            float newX = position->getX() + velocity->getDX();
                            float newY = position->getY() + velocity->getDY();
                            position->setX(newX);
                            position->setY(newY);
                            velocity->setDX(0);
                            velocity->setDY(0);
                        }
                    }
                }
        };
    }
}
