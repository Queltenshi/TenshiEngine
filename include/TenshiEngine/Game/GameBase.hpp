#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Manager/CameraManager.hpp"
#include "TenshiEngine/Engine/Manager/ResourceManager.hpp"
#include "TenshiEngine/Engine/Manager/TileMapManager.hpp"
#include "TenshiEngine/Systems.hpp"

namespace te{

/**
 * @brief Base class for a game
 *
 * This class creates a Base for creating and starting the Game.
 *
 * Usage: 
 * - Inherit from GameBase
 * - Override init() and call Parent init to load game objects and logic
 * - Call run() to start the game loop
 */
class GameBase{
public:

    /**
     * @brief Constructor
     *
     * creates a window with given title and windowSize
     *
     * @param windowName Title of the window to be created
     * @param windowSize Size of the window to be created
     */
    GameBase(std::string windowName, sf::Vector2u windowSize);

    /**
     * @brief starts the game loop
     *
     * keeps the window open and handles rendering and game updates
     */
    void run();

    /**
     * @brief Intializes game objects
     * 
     * this method should be overriden and called in derived classes
     * to register custom game logic and system
     */
    virtual void init();

protected:
    /// Registry used for managing entities, components and systems
    Registry mRegistry;

    ///CameraManager used for managing camera
    managers::CameraManager mCameraManager;

    ///ResourceManager used for managing resources
    managers::ResourceManager mResourceManager;

    ///TileMapManager used for loading tilesets and levels
    managers::TileMapManager mTileMapManager;

    ///BackgroundManager used for managing the background
    managers::BackgroundManager mBackgroundManager;
private:
    sf::RenderWindow mWindow;
    const float mFixedDeltaTime;
    float mVariableDeltaTime;
    sf::Clock mClock;
    float mAccumulator;
};

}
