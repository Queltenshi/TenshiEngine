#include "TenshiEngine/Game/GameBase.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace te{

GameBase::GameBase(std::string windowName, sf::Vector2u windowSize)
    : mWindow(sf::VideoMode(windowSize), windowName), 
      mCameraManager(mRegistry, mBackgroundManager, static_cast<sf::Vector2f>(windowSize)), 
      mTileMapManager(mRegistry), 
      mBackgroundManager(mResourceManager.getTexture("Default"), static_cast<sf::Vector2f>(windowSize)),
      mFixedDeltaTime(1.f / 60.f), 
      mVariableDeltaTime(0.f), 
      mAccumulator(0.f){ //mWindow(sf::VideoMode::getDesktopMode(), windowName, sf::State::Fullscreen)
    
}

void GameBase::init(){
    mWindow.setFramerateLimit(60);
    mRegistry.addSystem<systems::RenderSystem>(mVariableDeltaTime, mWindow, mCameraManager, mBackgroundManager);
    mRegistry.addSystem<systems::InputSystem>(mVariableDeltaTime);
    mRegistry.addSystem<systems::MovementSystem>(mFixedDeltaTime);
    mRegistry.addSystem<systems::PhysicsSystem>(mFixedDeltaTime);
    mRegistry.addSystem<systems::AnimationSystem>(mVariableDeltaTime);
}

void GameBase::run(){
    while (mWindow.isOpen())
    {
        mVariableDeltaTime = mClock.restart().asSeconds();
        mAccumulator += mVariableDeltaTime;

        while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                mWindow.close();
        }


        while(mAccumulator >= mFixedDeltaTime){
            mRegistry.updateFixedSystems();        
            mAccumulator -= mFixedDeltaTime;
        }

        mCameraManager.update();
        mRegistry.updateVariableSystems();

        mWindow.clear();
        mRegistry.updateRenderSystem();
        mWindow.display();
    }
}

}
