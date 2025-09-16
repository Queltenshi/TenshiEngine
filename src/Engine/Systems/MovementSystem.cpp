#include "TenshiEngine/Engine/Systems/MovementSystem.hpp"

namespace te{
namespace systems{

MovementSystem::MovementSystem(Registry &registry, float deltaTime) : FixedSystem(registry, deltaTime){}

void MovementSystem::update(){
    const auto &entityIDs = mRegistry.view<components::Velocity>();
    for(auto entityID : entityIDs){
        updateVelocity(entityID);
    }
}

void MovementSystem::updateVelocity(EntityID entityID){
    auto velocity = mRegistry.getComponent<components::Velocity>(entityID);
    auto oldValue = velocity->value;

    if(mRegistry.hasComponent<components::HorizontalMovement>(entityID)){
        auto horizontalMovement = mRegistry.getComponent<components::HorizontalMovement>(entityID);

        if(mRegistry.hasComponent<components::Steering>(entityID)){
            auto playerInput = mRegistry.getComponent<components::Steering>(entityID);

            velocity->value.x = updateHorizontalMovement(entityID, playerInput, horizontalMovement);
            if(mRegistry.hasComponent<components::Jump>(entityID)){
                velocity->value.y = updateJump(entityID, playerInput, velocity);
            }
        }
        updateState(entityID, velocity);
    }

    if(velocity->value != oldValue){
        LOG_DEBUG_COMPONENT_CHANGED(name, velocity->name, velocity, entityID);
    }
}

float MovementSystem::updateHorizontalMovement(EntityID entityID, components::Steering *playerInput, components::HorizontalMovement *horizontalMovement){
    float newMovement = 0.f;
    if(playerInput->left){
        newMovement = -horizontalMovement->speed;
        playerInput->left = false;
    } 
    else if (playerInput->right){
        newMovement = horizontalMovement->speed;
        playerInput->right = false;
    }

    return newMovement;
}

void MovementSystem::updateState(EntityID entityID, components::Velocity *velocity){
    if (mRegistry.hasComponent<components::State>(entityID)) {
        auto state = mRegistry.getComponent<components::State>(entityID);
        auto oldState = state->currentState;
        auto oldDirection = state->direction;

        if(velocity->value.y == 0 && velocity->value.x != 0){
            state->currentState = components::State::CurrentState::WALK;
        }
        else if(velocity->value.y > 0){
            state->currentState = components::State::CurrentState::FALL;
        }
        else if(velocity->value.y < 0){
            state->currentState = components::State::CurrentState::JUMP;
        }
        else if(state->currentState != components::State::CurrentState::JUMP){
            state->currentState = components::State::CurrentState::IDLE;
        }

        if(velocity->value.x < 0){
            state->direction = components::State::Direction::LEFT;
        }
        else if(velocity->value.x > 0){
            state->direction = components::State::Direction::RIGHT;
        }
        
        if(state->currentState != oldState || state->direction != oldDirection){
            LOG_DEBUG_COMPONENT_CHANGED(name, state->name, state, entityID);
        }
    }
}

float MovementSystem::updateJump(EntityID entityID, components::Steering *playerInput, components::Velocity *velocity){
    auto jump = mRegistry.getComponent<components::Jump>(entityID);
    float newVelocityY = velocity->value.y;

    if(playerInput->jump){
        if(mRegistry.hasComponent<components::Grounded>(entityID) && mRegistry.getComponent<components::Grounded>(entityID)->isGrounded){
            newVelocityY = -jump->strength;
        }
        playerInput->jump = false; 
    }

    return newVelocityY;
}

const std::string MovementSystem::name = "MovementSystem";

}
}
