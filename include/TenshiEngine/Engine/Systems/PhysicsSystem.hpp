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
     * @param registry reference to the registry
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
    void checkCollision(EntityID entityID1, EntityID entityID2);
    void correctPosition(EntityID entityID, components::Transform *transform1, components::Transform *transform2, sf::FloatRect overlapRect);

    float mGravity;

    inline static const float defaultGravity = 25.f;
};

}
}
