#include "TenshiEngine/Engine/Systems/MovementSystem.hpp"

namespace te{
namespace systems{

MovementSystem::MovementSystem(Registry &registry) : System(registry){}

void MovementSystem::update(){
    const auto &entityIDs = mRegistry.view<components::Velocity>();
    for(auto entityID : entityIDs){
        updateVelocity(entityID);
    }
}

void MovementSystem::updateVelocity(EntityID entityID){
    auto velocity = mRegistry.getComponent<components::Velocity>(entityID);
    sf::Vector2f newVelocity = velocity->value;

    if(mRegistry.hasComponent<components::HorizontalMovement>(entityID)){
        auto horizontalMovement = mRegistry.getComponent<components::HorizontalMovement>(entityID);

        if(mRegistry.hasComponent<components::PlayerInput>(entityID)){
            auto playerInput = mRegistry.getComponent<components::PlayerInput>(entityID);

            newVelocity.x = updateHorizontalMovement(playerInput, horizontalMovement);
            
            if(mRegistry.hasComponent<components::Jump>(entityID)){
                newVelocity.y = updateJump(entityID, playerInput, velocity);
            }
        }
    }

    if(velocity->value != newVelocity){
        velocity->value = newVelocity;
        LOG_DEBUG_COMPONENT_CHANGED(name, velocity->name, velocity, entityID);
    }
}

float MovementSystem::updateHorizontalMovement(components::PlayerInput *playerInput, components::HorizontalMovement *horizontalMovement){
    if(playerInput->left){
        playerInput->left = false;
        return -1.f * horizontalMovement->speed;
    }

    if (playerInput->right){
        playerInput->right = false;
        return 1.f * horizontalMovement->speed;
    }

    return 0.f;
}

float MovementSystem::updateJump(EntityID entityID, components::PlayerInput *playerInput, components::Velocity *velocity){
    auto jump = mRegistry.getComponent<components::Jump>(entityID);

    if(playerInput->jump){
        if(!mRegistry.hasComponent<components::Grounded>(entityID) || mRegistry.getComponent<components::Grounded>(entityID)->isGrounded){
            return -jump->strength;
        }
        playerInput->jump = false; 
    }
    return velocity->value.y;
}

const std::string MovementSystem::name = "MovementSystem";

}
}
