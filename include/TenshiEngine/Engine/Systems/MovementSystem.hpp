#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

/**
 * @brief System for calculating velocity
 *
 * Checks playerInput, horizonzalMovement, jump, grounded, velocity 
 * and then calculates new velocity 
 */
class MovementSystem : public FixedSystem{
public:
    /**
     * @brief Constructor
     *
     * creates the System
     *
     * @param registry reference to the registry
     * @param deltaTime Fixed deltaTime
     */
    MovementSystem(Registry &registry, const float deltaTime);

    void update(); 

    ///Name of system
    static const std::string name;

private:
    void updateVelocity(EntityID entityID);
    float updateHorizontalMovement(EntityID entityID, components::PlayerInput *playerInput, components::HorizontalMovement *horizontalMovement);
    void updateState(EntityID entityID, components::Velocity *velocity);
    float updateJump(EntityID entityID, components::PlayerInput *playerInput, components::Velocity *velocity);
};

}
}
