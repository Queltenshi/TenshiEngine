#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "System.hpp"

namespace te{
namespace systems{

class DebugRenderSystem : public System{
public:    
    DebugRenderSystem(Registry &registry, sf::RenderWindow &window);

    void update() override;
};

}
}
