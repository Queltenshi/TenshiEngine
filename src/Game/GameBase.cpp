#include "TenshiEngine/Game/GameBase.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace te{

GameBase::GameBase(std::string windowName)
    : mWindow(sf::VideoMode({1920, 1080}), windowName), mDeltaTime(1.f / 60.f), mAccumulator(0.f), mMaxUpdatesPerFrame(5){ //mWindow(sf::VideoMode::getDesktopMode(), windowName, sf::State::Fullscreen)
    
}

void GameBase::init(){
    mWindow.setFramerateLimit(60);
    mRegistry.addSystem<systems::RenderSystem>(mWindow);
    mRegistry.addSystem<systems::InputSystem>();
    mRegistry.addSystem<systems::MovementSystem>();
    mRegistry.addSystem<systems::PhysicsSystem>();
}

void GameBase::run(){
    int frame = 0;
    while (mWindow.isOpen())
    {
        float frameTime = mClock.restart().asSeconds();
        if (mAccumulator > mDeltaTime * mMaxUpdatesPerFrame)
            mAccumulator = mDeltaTime * mMaxUpdatesPerFrame;

        mAccumulator += frameTime;

        while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                mWindow.close();
        }

        int updates = 0;
        while(mAccumulator >= mDeltaTime && updates < mMaxUpdatesPerFrame){
            mRegistry.updateSystems();        
            mAccumulator -= mDeltaTime;
            updates++;
        }
        
        mWindow.clear();
        mRegistry.updateRenderSystem();
        mWindow.display();
    }
}

}
