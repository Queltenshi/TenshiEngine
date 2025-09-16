#include "TenshiEngine/Engine/Systems/PhysicsSystem.hpp"
#include <string>

namespace te{
namespace systems{

PhysicsSystem::PhysicsSystem(Registry &registry, float deltaTime, float gravity) : FixedSystem(registry, deltaTime), mGravity(gravity){}

void PhysicsSystem::update(){
    //Velocity
    const auto & entityIDs = mRegistry.view<components::Velocity, components::Rigidbody>();
    for(auto entityID: entityIDs){
        if(mRegistry.hasComponent<components::Grounded>(entityID)){
            mRegistry.getComponent<components::Grounded>(entityID)->isGrounded = false;
        }

        auto velocity = mRegistry.getComponent<components::Velocity>(entityID);
        auto transform  = mRegistry.getComponent<components::Transform>(entityID);

        updateGravity(entityID, velocity);
    }
    checkCollision();
}

void PhysicsSystem::updateGravity(EntityID entityID, components::Velocity *velocity){
    auto rigidBody = mRegistry.getComponent<components::Rigidbody>(entityID);

    if(!rigidBody->isStatic){
        float acceleration = mGravity * rigidBody->mass * mDeltaTime;
        velocity->value.y += acceleration; 
    }
}

void PhysicsSystem::checkCollision(){
    const auto & movingEntitiesIDs = mRegistry.view<components::Collider, components::Velocity>();
    for(auto movingEntityID : movingEntitiesIDs){
        auto transform = mRegistry.getComponent<components::Transform>(movingEntityID);
        auto collider = mRegistry.getComponent<components::Collider>(movingEntityID);
        sf::FloatRect rect = getWorldBounds(transform, collider);

        checkXCollisions(transform, rect, movingEntityID);
        checkYCollisions(transform, rect, movingEntityID);

        transform->positionDirty = true;
    }
}

void PhysicsSystem::checkXCollisions(components::Transform *transform, sf::FloatRect &rect, EntityID movingEntityID){
    auto velocity = mRegistry.getComponent<components::Velocity>(movingEntityID);
    transform->position.x += velocity->value.x * mDeltaTime;
    rect.position.x += velocity->value.x * mDeltaTime;
    
    const auto & otherEntityIDs = mRegistry.view<components::Collider>();
    for(auto otherEntityID : otherEntityIDs){
        if(otherEntityID == movingEntityID){
            continue;
        }
       
        auto otherTransform = mRegistry.getComponent<components::Transform>(otherEntityID);
        auto otherCollider = mRegistry.getComponent<components::Collider>(otherEntityID);
        sf::FloatRect otherRect = getWorldBounds(otherTransform, otherCollider);

        auto intersection = rect.findIntersection(otherRect);
        sf::FloatRect intersectionRect = *intersection;

        if(intersection){
            if(mRegistry.hasComponent<components::Rigidbody>(movingEntityID) && mRegistry.hasComponent<components::Rigidbody>(otherEntityID) && mRegistry.getComponent<components::Rigidbody>(otherEntityID)->isStatic){
                correctXPosition(velocity, transform, intersectionRect, rect);
            }
        }
    }
}

void PhysicsSystem::checkYCollisions(components::Transform *transform, sf::FloatRect &rect, EntityID movingEntityID){
    auto velocity = mRegistry.getComponent<components::Velocity>(movingEntityID);
    transform->position.y += velocity->value.y * mDeltaTime;
    rect.position.y += velocity->value.y * mDeltaTime;

    const auto & otherEntityIDs = mRegistry.view<components::Collider>();
    for(auto otherEntityID : otherEntityIDs){
        if(otherEntityID == movingEntityID){
            continue;
        }
        
        auto otherTransform = mRegistry.getComponent<components::Transform>(otherEntityID);
        auto otherCollider = mRegistry.getComponent<components::Collider>(otherEntityID);
        sf::FloatRect otherRect = getWorldBounds(otherTransform, otherCollider);

        auto intersection = rect.findIntersection(otherRect);
        sf::FloatRect intersectionRect = *intersection;

        if(intersection){
            if(mRegistry.hasComponent<components::Rigidbody>(movingEntityID) && mRegistry.hasComponent<components::Rigidbody>(otherEntityID) && mRegistry.getComponent<components::Rigidbody>(otherEntityID)->isStatic){
                correctYPosition(velocity, transform, intersectionRect, rect, movingEntityID);
            }
        }
    }
}

void PhysicsSystem::correctXPosition(components::Velocity *velocity, components::Transform *transform, sf::FloatRect intersectionRect, sf::FloatRect &rect){
    if(velocity->value.x > 0){
        transform->position.x -= intersectionRect.size.x + 0.0001f;
        rect.position.x -= intersectionRect.size.x + 0.0001f;
    }
    else{
        transform->position.x += intersectionRect.size.x;
        rect.position.x += intersectionRect.size.x;
    }
    velocity->value.x = 0.f;
}

void PhysicsSystem::correctYPosition(components::Velocity *velocity, components::Transform *transform, sf::FloatRect intersectionRect, sf::FloatRect &rect, EntityID movingEntityID){
    if(velocity->value.y > 0){
        transform->position.y -= intersectionRect.size.y + 0.0001f;
        rect.position.y -= intersectionRect.size.y + 0.0001f;
        if(mRegistry.hasComponent<components::Grounded>(movingEntityID)){
            auto grounded = mRegistry.getComponent<components::Grounded>(movingEntityID);
            grounded->isGrounded = true;
        }
    }else{
        transform->position.y += intersectionRect.size.y;
        rect.position.y += intersectionRect.size.y;
    }
    velocity->value.y = 0.f;
}

sf::FloatRect PhysicsSystem::getWorldBounds(components::Transform *transform, components::Collider *collider){
    return sf::FloatRect ({transform->position.x - (collider->size.x * transform->scale.x * 0.5f), 
                           transform->position.y - (collider->size.y * transform->scale.y * 0.5f)}, 
                          {collider->size.x * transform->scale.x, 
                           collider->size.y * transform->scale.y});
}

const std::string PhysicsSystem::name = "PhysicsSystem";

}
}
