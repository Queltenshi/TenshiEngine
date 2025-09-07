#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace te{

namespace systems{

RenderSystem::RenderSystem(Registry &registry, float &deltaTime, sf::RenderWindow &window, managers::CameraManager &cameraManager, managers::BackgroundManager &backgroundManager)
    : VariableSystem(registry, deltaTime), mWindow(window), mCameraManager(cameraManager), mBackgroundManager(backgroundManager){}

void RenderSystem::update(){
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mBackgroundManager.getBackground());

    if(auto* camera = mCameraManager.getActiveCamera()){
        mWindow.setView(camera->view);
    }

    std::vector<EntityID> entityIDs = mRegistry.view<components::Sprite>();
    for(auto entityID : entityIDs){
        auto sprite = mRegistry.getComponent<components::Sprite>(entityID);
        auto transform = mRegistry.getComponent<components::Transform>(entityID);

        if(transform->positionDirty){
            sprite->sprite.setPosition(transform->position);
            transform->positionDirty = false;
        }

        if(transform->scaleDirty){
            sprite->sprite.setScale(transform->scale);
            transform->scaleDirty = false;
        }
       
        mWindow.draw(sprite->sprite);

        //Debug rendering
        if(Logger::currentLevel == LogLevel::DEBUG && mRegistry.hasComponent<components::Collider>(entityID)){
            auto collider = mRegistry.getComponent<components::Collider>(entityID);
            sf::RectangleShape colliderRect({collider->size.x * transform->scale.x, collider->size.y * transform->scale.y});
            colliderRect.setOrigin(colliderRect.getSize() / 2.f);
            colliderRect.setPosition(transform->position);
            colliderRect.setFillColor(sf::Color(0, 0, 0, 0));
            colliderRect.setOutlineThickness(-2.f);
            mWindow.draw(colliderRect);
        }
    }
}

const std::string RenderSystem::name = "RenderSystem";

}
}
