#include "TenshiEngine/Engine/Systems/PhysicsSystem.hpp"

namespace te{
namespace systems{

PhysicsSystem::PhysicsSystem(Registry &registry) : System(registry), mGravity(defaultGravity){}
PhysicsSystem::PhysicsSystem(Registry &registry, float gravity) : System(registry), mGravity(gravity){}

void PhysicsSystem::update(){
    const auto & entityIDs = mRegistry.view<components::Rigidbody>();
    for(auto entityID: entityIDs){
        if(mRegistry.hasComponent<components::Velocity>(entityID)){
            if(mRegistry.hasComponent<components::Grounded>(entityID)){
                mRegistry.getComponent<components::Grounded>(entityID)->isGrounded = false;
            }
            auto transform  = mRegistry.getComponent<components::Transform>(entityID);
            auto velocity = mRegistry.getComponent<components::Velocity>(entityID);

            updateGravity(entityID, velocity);
            transform->position += velocity->value;
            transform->positionDirty = true;
        }
    }

    for(int i = 0; i < entityIDs.size(); i++){
        for(int j = i+1; j < entityIDs.size(); j++){
            updateCollision(entityIDs[i], entityIDs[j]);
        }
    }
}

void PhysicsSystem::updateGravity(EntityID entityID, components::Velocity *velocity){
    auto rigidBody = mRegistry.getComponent<components::Rigidbody>(entityID);

    if(!rigidBody->isStatic){
        float acceleration = mGravity * rigidBody->mass * 0.0007;
        velocity->value.y += acceleration; 
    }
}

void PhysicsSystem::updateCollision(EntityID entityID1, EntityID entityID2){
    auto transform1 = mRegistry.getComponent<components::Transform>(entityID1);
    auto transform2 = mRegistry.getComponent<components::Transform>(entityID2);
    sf::FloatRect rectangle1(transform1->position - transform1->size * 0.5f, transform1->size);
    sf::FloatRect rectangle2(transform2->position - transform2->size * 0.5f, transform2->size);
    auto intersection = rectangle1.findIntersection(rectangle2); 

    if(intersection){
        sf::FloatRect overlapRect = *intersection;
        auto rigidBody1 = mRegistry.getComponent<components::Rigidbody>(entityID1);
        auto rigidBody2 = mRegistry.getComponent<components::Rigidbody>(entityID2);
        if(!rigidBody1->isStatic){
            correctPosition(entityID1, transform2, transform1, overlapRect);
        } else if(!rigidBody2->isStatic){
            correctPosition(entityID2, transform1, transform2, overlapRect);
        }
    }
}

void PhysicsSystem::correctPosition(EntityID entityID, components::Transform *transform1, components::Transform *transform2, sf::FloatRect overlapRect){
   auto velocity = mRegistry.getComponent<components::Velocity>(entityID);

    if(overlapRect.size.x > overlapRect.size.y){
        if(transform2->position.y < transform1->position.y){
            transform2->position.y -= overlapRect.size.y;
        } else{ 
            transform2->position.y += overlapRect.size.y;
        }
        velocity->value.y = 0;
        if(mRegistry.hasComponent<components::Grounded>(entityID)){
            mRegistry.getComponent<components::Grounded>(entityID)->isGrounded = true;
        }
    } else{
        if(transform2->position.x < transform1->position.x){
            transform2->position.x -= overlapRect.size.x;
        } else{ 
            transform2->position.x += overlapRect.size.x;
        }
        velocity->value.x = 0;
    }
    transform2->positionDirty = true;
}

const std::string PhysicsSystem::name = "PhysicsSystem";

}
}
