#include "TenshiEngine/Engine/Systems/PhysicsSystem.hpp"

namespace te{
namespace systems{

PhysicsSystem::PhysicsSystem(Registry &registry, float deltaTime) : FixedSystem(registry, deltaTime), mGravity(defaultGravity){}
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
        transform->position += velocity->value * mDeltaTime;
        transform->positionDirty = true;
    }

    //Collision
    const auto & collisionEntityIDs = mRegistry.view<components::Collider>();
    for(int i = 0; i < collisionEntityIDs.size(); i++){
        for(int j = i+1; j < collisionEntityIDs.size(); j++){
            checkCollision(collisionEntityIDs[i], collisionEntityIDs[j]);
        }
    }
}

void PhysicsSystem::updateGravity(EntityID entityID, components::Velocity *velocity){
    auto rigidBody = mRegistry.getComponent<components::Rigidbody>(entityID);

    if(!rigidBody->isStatic){
        float acceleration = mGravity * rigidBody->mass * mDeltaTime;
        velocity->value.y += acceleration; 
    }
}

void PhysicsSystem::checkCollision(EntityID entityID1, EntityID entityID2){
    auto transform1 = mRegistry.getComponent<components::Transform>(entityID1);
    auto transform2 = mRegistry.getComponent<components::Transform>(entityID2);
    auto collider1 = mRegistry.getComponent<components::Collider>(entityID1);
    auto collider2 = mRegistry.getComponent<components::Collider>(entityID2);
    sf::FloatRect rectangle1({transform1->position.x - collider1->size.x * transform1->scale.x * 0.5f, 
                              transform1->position.y - collider1->size.y * transform1->scale.y * 0.5f}, 
                              {collider1->size.x * transform1->scale.x, 
                               collider1->size.y * transform1->scale.y});
    sf::FloatRect rectangle2({transform2->position.x - collider2->size.x * transform2->scale.x * 0.5f, 
                              transform2->position.y - collider2->size.y * transform2->scale.y * 0.5f}, 
                             {collider2->size.x * transform2->scale.x, 
                              collider2->size.y * transform2->scale.y});
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
            if(mRegistry.hasComponent<components::Grounded>(entityID)){
                mRegistry.getComponent<components::Grounded>(entityID)->isGrounded = true;
            }
            velocity->value.y = 0;
        } else{ 
            transform2->position.y += overlapRect.size.y;
            velocity->value.y = 0;
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
