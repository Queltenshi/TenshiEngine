#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"

namespace te{
namespace systems{

RenderSystem::RenderSystem(Registry &registry, sf::RenderWindow &window) : System(registry, "RenderSystem"), mWindow(window){}

void RenderSystem::update(){
    std::vector<EntityID> entityIDs = mRegistry.view<components::SpriteComponent>();
    for(auto entityID : entityIDs){
        auto &sprite = mRegistry.getComponent<components::SpriteComponent>(entityID)->sprite;
        mWindow.draw(sprite);
    }
}

}
}
