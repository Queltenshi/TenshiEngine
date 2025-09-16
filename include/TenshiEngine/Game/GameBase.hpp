#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Manager/ResourceManager.hpp"
#include "TenshiEngine/Engine/Manager/TileMapManager.hpp"
#include "TenshiEngine/Systems.hpp"
#include "TenshiEngine/Game/Config.hpp"

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
     * Default constructor
     */
    GameBase();

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
    ///Config with data
    Config mConfig;

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
    float mFixedDeltaTime;
    float mVariableDeltaTime;
    sf::Clock mClock;
    float mAccumulator;

    const static std::string name;
};

}
