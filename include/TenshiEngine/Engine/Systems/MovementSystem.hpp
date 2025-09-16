#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

class MovementSystem : public FixedSystem{
public:
    MovementSystem(Registry &registry, const float deltaTime);

    void update(); 

    static const std::string name;

private:
    void updateVelocity(EntityID entityID);
    float updateHorizontalMovement(EntityID entityID, components::Steering *playerInput, components::HorizontalMovement *horizontalMovement);
    void updateState(EntityID entityID, components::Velocity *velocity);
    float updateJump(EntityID entityID, components::Steering *playerInput, components::Velocity *velocity);
};

}
}
