#pragma once
#include <SFML/Graphics.hpp>
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"
#include "TenshiEngine/Engine/Systems/Systems.hpp"
#include "TenshiEngine/Engine/Core/Logger.hpp"

namespace te{

class GameBase{
public:
    GameBase(std::string windowName);

    void run();
    virtual void init();

protected:
    Registry mRegistry;

private:
    sf::RenderWindow mWindow;
    //systems::RenderSystem mRenderSystem;
};

}
