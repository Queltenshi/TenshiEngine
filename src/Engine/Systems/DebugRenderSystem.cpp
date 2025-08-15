#include "TenshiEngine/Engine/Systems/DebugRenderSystem.hpp"

namespace te{
namespace systems{

DebugRenderSystem::DebugRenderSystem(Registry &registry, sf::RenderWindow &window) : System(registry, "DebugRenderSystem"){

}

void DebugRenderSystem::update(){
    /*std::vector<EntityID> entityIDs = mRegistry.view<components::SpriteComponent>();
    for(auto entityID : entityIDs){
        auto &sprite = mRegistry.getComponent<components::SpriteComponent>(entityID)->sprite;
        mWindow.draw(sprite);
    }*/
}

}
}
