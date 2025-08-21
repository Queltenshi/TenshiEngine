#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"


namespace te{
namespace systems{

RenderSystem::RenderSystem(Registry &registry, sf::RenderWindow &window) : System(registry), mWindow(window){}

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
    }
}

const std::string RenderSystem::name = "RenderSystem";

}
}
