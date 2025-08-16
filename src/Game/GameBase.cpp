#include "TenshiEngine/Game/GameBase.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace te{

GameBase::GameBase(std::string windowName)
    : mWindow(sf::VideoMode({800, 600}), windowName){ //mWindow(sf::VideoMode::getDesktopMode(), windowName, sf::State::Fullscreen)
    
}

void GameBase::init(){
    mRegistry.addSystem<systems::RenderSystem>(mWindow);
    mRegistry.addSystem<systems::InputSystem>();
}

void GameBase::run(){
    while (mWindow.isOpen())
    {
        while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                mWindow.close();
        }
        mWindow.clear();
        mRegistry.updateSystems();        
        mWindow.display();
    }
}

}
