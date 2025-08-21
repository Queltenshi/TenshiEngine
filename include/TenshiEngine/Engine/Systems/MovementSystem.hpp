#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <SFML/System/Vector2.hpp>

namespace te{
namespace systems{

/**
 * @brief System for calculating velocity
 *
 * Checks playerInput, horizonzalMovement, jump, grounded, velocity 
 * and then calculates new velocity 
 */
class MovementSystem : public System{
public:
    /**
     * @brief Constructor
     *
     * creates the System
     *
     * @param registry reference to the registry
     */
    MovementSystem(Registry &registry);

    void update() override; 

    ///Name of system
    static const std::string name;

private:
    void updateVelocity(EntityID entityID);
    float updateHorizontalMovement(components::PlayerInput *playerInput, components::HorizontalMovement *horizontalMovement);
    float updateJump(EntityID entityID, components::PlayerInput *playerInput, components::Velocity *velocity);
};

}
}
