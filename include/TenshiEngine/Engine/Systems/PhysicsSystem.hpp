#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

/**
 * @brief System for physical calculations
 *
 * Checks velocity, rigidBody, collider and then calculates
 * new velocity and new sprite position
 */
class PhysicsSystem : public FixedSystem{
public:
    /**
     * @brief Constructor
     *
     * creates the System with defaultGravity(10.f)
     *
     * @param registry Reference to the registry
     * @param deltaTime Fixed deltaTime
     */
    PhysicsSystem(Registry &registry, const float deltaTime);

    /**
     * @brief Constructor
     *
     * creates the System with given gravity
     *
     * @param registry reference to the registry
     * @param deltaTime deltaTime
     * @param gravity value of gravity
     */
    PhysicsSystem(Registry &registry, float deltaTime, float gravity);

    void update(); 

    ///Name of system
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

    static const float defaultGravity;
};

}
}
