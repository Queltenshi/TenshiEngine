#include "TenshiEngine/Engine/Systems/AnimationSystem.hpp"

namespace te{
namespace systems{

AnimationSystem::AnimationSystem(Registry &registry, float &deltaTime) : VariableSystem(registry, deltaTime){

}

void AnimationSystem::update(){
    const auto &entityIDs = mRegistry.view<components::Animation, components::State>();
    for(auto entityID : entityIDs){
        auto state = mRegistry.getComponent<components::State>(entityID);
        checkDirection(entityID, state);
        checkState(entityID, state);
    }
}

void AnimationSystem::checkDirection(EntityID entityID, components::State *state){
    auto transform = mRegistry.getComponent<components::Transform>(entityID);
    auto oldScale = transform->scale;
    
    switch (state->direction) {
        case components::State::Direction::LEFT :
            transform->scale = {-std::abs(transform->scale.x), std::abs(transform->scale.y)}; 
            transform->scaleDirty = true;
            break;

        case components::State::Direction::RIGHT :
            transform->scale = {std::abs(transform->scale.x), std::abs(transform->scale.y)}; 
            transform->scaleDirty = true;
            break;

        default:
            LOG_DEBUG(name, "Unknown direction");
    }

    if(transform->scale != oldScale){
        LOG_DEBUG_COMPONENT_CHANGED(name, transform->name, transform, entityID);
    }
}

void AnimationSystem::checkState(EntityID entityID, components::State *state){
    auto animation = mRegistry.getComponent<components::Animation>(entityID);
    auto animationData = animation->textureData["animations"];

    animation->elapsedTime += mDeltaTime;

    if(static_cast<int>(animation->currentAnimation) != static_cast<int>(state->currentState)){
        animation->currentAnimation = static_cast<components::Animation::CurrentAnimation>(state->currentState);
        animation->iterator = 0;
        LOG_DEBUG_COMPONENT_CHANGED(name, animation->name, animation, entityID);
        animation->elapsedTime = 0;
    }

    switch(state->currentState){
        case components::State::CurrentState::IDLE :
            if(animationData.contains("idle")){
                auto idleFrame = animationData["idle"];
                updateTexture(entityID, animation, idleFrame);
            }
            break;

        case components::State::CurrentState::WALK :
            if(animationData.contains("walk")){
                auto walkFrame = animationData["walk"];
                updateTexture(entityID, animation, walkFrame);
            }
            break;
            
        case components::State::CurrentState::JUMP :
            if(animationData.contains("jump")){
                auto jumpFrame = animationData["jump"];
                updateTexture(entityID, animation, jumpFrame);
            }
            break;

        case components::State::CurrentState::FALL :
            if(animationData.contains("fall")){
                auto fallFrame = animationData["fall"];
                updateTexture(entityID, animation, fallFrame);
            }
            break;

        case components::State::CurrentState::HIT :
            if(animationData.contains("hit")){
                auto hitFrame = animationData["hit"];
                updateTexture(entityID, animation, hitFrame);
            }
            break;

        default:
            LOG_DEBUG(name, "Unknown currentState");
    }

    auto sprite = mRegistry.getComponent<components::Sprite>(entityID);
    sprite->sprite.setTextureRect(animation->rectangle);
}

void AnimationSystem::updateTexture(EntityID entityID, components::Animation *animation, json &frame){
    if(animation->elapsedTime > animation->switchTime){
        animation->iterator++;

        if(animation->iterator == frame.size()){
            animation->iterator = 0;
        } 
        animation->elapsedTime = 0;
    }

    animation->rectangle.position = {frame[animation->iterator]["x"], frame[animation->iterator]["y"]};
    animation->rectangle.size = {frame[animation->iterator]["w"], frame[animation->iterator]["h"]};
}

const std::string AnimationSystem::name = "AnimationSystem";

}

}
