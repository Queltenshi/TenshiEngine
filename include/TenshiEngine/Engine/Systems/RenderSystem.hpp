#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TenshiEngine/Engine/Systems/System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

class RenderSystem : public System{
public:    
    RenderSystem(Registry &registry, sf::RenderWindow &window);

    void update() override;

private:
    sf::RenderWindow &mWindow;
};

}
}
