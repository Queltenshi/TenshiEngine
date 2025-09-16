#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TenshiEngine/Engine/Systems/System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Manager/CameraManager.hpp"
#include "TenshiEngine/Engine/Manager/BackgroundManager.hpp"
#include "TenshiEngine/Engine/Camera/Camera.hpp"

namespace te{

namespace systems{

class RenderSystem : public VariableSystem{
public:

    RenderSystem(Registry &registry, float &deltaTime, sf::RenderWindow &window, managers::CameraManager &cameraManager, managers::BackgroundManager &backgroundManager);

    void update();

    static const std::string name;

private:
    sf::RenderWindow &mWindow;
    managers::CameraManager &mCameraManager;
    managers::BackgroundManager &mBackgroundManager;
};

}
}
