#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

class PhysicsSystem : public FixedSystem{
public:
    PhysicsSystem(Registry &registry, const float deltaTime, const float gravity);

    void update(); 

    static const std::string name;

private:
    void updateGravity(EntityID entityID, components::Velocity *velocity);
    void checkCollision();
    void checkXCollisions(components::Transform *transform, sf::FloatRect &rect, EntityID movingEntityID);
    void checkYCollisions(components::Transform *transform, sf::FloatRect &rect, EntityID movingEntityID);
    void correctXPosition(components::Velocity *velocity, components::Transform *transform, sf::FloatRect intersectionRect, sf::FloatRect &rect);
    void correctYPosition(components::Velocity *velocity, components::Transform *transform, sf::FloatRect intersectionRect, sf::FloatRect &rect, EntityID movingEntityID);
    sf::FloatRect getWorldBounds(components::Transform *transform, components::Collider *collider);

    float mGravity;
};

}
}
