#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TenshiEngine/Engine/Systems/System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Manager/CameraManager.hpp"
#include "TenshiEngine/Engine/Manager/BackgroundManager.hpp"
#include "TenshiEngine/Engine/Camera/Camera.hpp"

namespace te{

namespace systems{

/**
 * @brief System for rendering the sprite
 *
 * Does rendering of the sprite in the window
 */
class RenderSystem : public VariableSystem{
public:

    /**
     * @brief Constructor
     *
     * creates the System with given window and cameraManager
     *
     * @param registry reference to the registry
     * @param deltaTime reference to the frame delta time
     * @param window reference to the window
     * @param cameraManager reference to the cameraManager
     */
    RenderSystem(Registry &registry, float &deltaTime, sf::RenderWindow &window, managers::CameraManager &cameraManager, managers::BackgroundManager &backgroundManager);

    void update();

    ///Name of system
    static const std::string name;

private:
    sf::RenderWindow &mWindow;
    managers::CameraManager &mCameraManager;
    managers::BackgroundManager &mBackgroundManager;
};

}
}
