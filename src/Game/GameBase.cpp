#include "TenshiEngine/Game/GameBase.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace te{

GameBase::GameBase(): mBackgroundManager(mResourceManager.getTexture("Default")), mFixedDeltaTime(1.f / 60.f), mVariableDeltaTime(0.f), mAccumulator(0.f){}

void GameBase::init(){
    if(mConfig.isFullscreen()){
        mWindow.create(sf::VideoMode(mConfig.getResolution()), mConfig.getGameName(), sf::State::Fullscreen);
    }
    else{
        mWindow.create(sf::VideoMode(mConfig.getResolution()), mConfig.getGameName());
    }
    mWindow.setFramerateLimit(mConfig.getFPS());
    if(mConfig.getFPS() < 60u){
        mFixedDeltaTime = 1.f /  mConfig.getFPS();
    }
    Logger::info(name, "Window created: (title: " + mConfig.getGameName() + " | " +
                                        "width: " + std::to_string(mWindow.getSize().x) + " | " +
                                        "height: " + std::to_string(mWindow.getSize().y) + " | " +
                                        "fullscreen: " + utils::boolToString(mConfig.isFullscreen()) + " | " +
                                        "FPS: " + std::to_string(mConfig.getFPS()) + ")");

    Logger::debugMode = mConfig.isDebugMode();

    mBackgroundManager.create(static_cast<sf::Vector2f>(mConfig.getResolution()));
    mCameraManager.create(&mRegistry, &mBackgroundManager, static_cast<sf::Vector2f>(mConfig.getResolution()));
    mTileMapManager.create(&mRegistry); 

    mRegistry.addSystem<systems::RenderSystem>(mVariableDeltaTime, mWindow, mCameraManager, mBackgroundManager);
    mRegistry.addSystem<systems::InputSystem>(mVariableDeltaTime, mConfig.getKeyBinds());
    mRegistry.addSystem<systems::MovementSystem>(mFixedDeltaTime);
    mRegistry.addSystem<systems::PhysicsSystem>(mFixedDeltaTime, mConfig.getGravityForce());
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

const std::string GameBase::name = "GameBase";

}
