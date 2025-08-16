#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace te{
namespace components{

/**
 * @brief component with position and scale
 *
 * stores the position and scaling of the sprite
 */
struct TransformComponent : public Component{
public:
    /**
     * @brief Constructor
     *
     * creates the component
     */
    TransformComponent(): Component("TransformComponent"), position(defaultPosition), scale(defaultScale){}

    std::string toString() const override{
        return "TestTransform";
    };

    ///Position of the sprite
    sf::Vector2f position;

    ///Scaling of the sprite
    sf::Vector2f scale;

private:
    inline static const sf::Vector2f defaultPosition{0.f, 0.f};
    inline static const sf::Vector2f defaultScale{1.f, 1.f};
};

}
}
