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
class RenderSystem : public System{
public:

    /**
     * @brief Constructor
     *
     * creates the System
     *
     * @param registry reference to the registry
     * @param window reference to the window
     */
    RenderSystem(Registry &registry, sf::RenderWindow &window);

    void update() override;

private:
    sf::RenderWindow &mWindow;
};

}
}
