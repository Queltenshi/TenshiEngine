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
class PhysicsSystem : public System{
public:
    /**
     * @brief Constructor
     *
     * creates the System with defaultGravity(10.f)
     *
     * @param registry reference to the registry
     */
    PhysicsSystem(Registry &registry);

    /**
     * @brief Constructor
     *
     * creates the System with given gravity
     *
     * @param registry reference to the registry
     * @param gravity value of gravity
     */
    PhysicsSystem(Registry &registry, float gravity);

    void update() override; 

    ///Name of system
    static const std::string name;

private:
    void updateGravity(EntityID entityID, components::Velocity *velocity);
    void updateCollision(EntityID entityID1, EntityID entityID2);
    void correctPosition(EntityID entityID, components::Transform *transform1, components::Transform *transform2, sf::FloatRect overlapRect);

    float mGravity;

    inline static const float defaultGravity = 10.f;
};

}
}
