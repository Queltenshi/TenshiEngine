#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TenshiEngine/Engine/Systems/System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

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
     * creates the System
     *
     * @param registry reference to the registry
     * @param deltaTime reference to the frame delta time
     * @param window reference to the window
     */
    RenderSystem(Registry &registry, float &deltaTime, sf::RenderWindow &window);

    void update();

    ///Name of system
    static const std::string name;

private:
    sf::RenderWindow &mWindow;
};

}
}
