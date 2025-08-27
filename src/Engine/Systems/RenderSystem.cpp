#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"
#include <SFML/Graphics/RectangleShape.hpp>


namespace te{
namespace systems{

RenderSystem::RenderSystem(Registry &registry, float &deltaTime, sf::RenderWindow &window) : VariableSystem(registry, deltaTime), mWindow(window){}

void RenderSystem::update(){
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
        if(Logger::currentLevel == LogLevel::DEBUG){
            sf::RectangleShape collider(transform->size);
            collider.setOrigin(collider.getSize() / 2.f);
            collider.setPosition(transform->position);
            collider.setFillColor(sf::Color(0, 0, 0, 0));
            collider.setOutlineThickness(-2.f);
            mWindow.draw(collider);
        }
    }
}

const std::string RenderSystem::name = "RenderSystem";

}
}
