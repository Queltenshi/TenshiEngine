#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <TenshiEngine/Engine/Utils/boolToString.hpp>

namespace te{
namespace components{

/**
 * @brief component with position and scale
 *
 * stores the position and scaling of the sprite
 */
struct Transform : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    Transform() = default;

    /**
     * @brief Constructor
     *
     * creates the component with given scale
     *
     * @param scale scaling of sprite
     */
    Transform(sf::Vector2f scale): scale(scale){}

    std::string toString() const override{
        return "(position.x: " + std::to_string(position.x) + " | " +
               "position.y: " + std::to_string(position.y) + " | " +
               "scale.x: " + std::to_string(scale.x) + " | " +
               "scale.y: " + std::to_string(scale.y) + " | " +
               "positionDirty: " + utils::boolToString(positionDirty) + " | " +
               "scaleDirty: " + utils::boolToString(scaleDirty) + ")";
    };

    ///Position of the sprite
    sf::Vector2f position = {0.f, 0.f};

    ///Scaling of sprite
    sf::Vector2f scale = {1.f, 1.f};

    ///checks if position was changed
    bool positionDirty = true;

    ///checks if scaling was changed
    bool scaleDirty = true;

    ///Name of component
    inline static const std::string name = "Transform";
};

}
}
