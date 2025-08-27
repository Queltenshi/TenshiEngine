#pragma once

#include <SFML/System/Vector2.hpp>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with current velocity
 *
 * stores value of the current x and y velocity
 */
struct Velocity : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    Velocity() = default;

    std::string toString() const override{
        return "(value.x: " + std::to_string(value.x) + " | " + " value.y: " + std::to_string(value.y) + ")"; 
    };

    ///Current velocity
    sf::Vector2f value = {0.f, 0.f};

    ///Name of component
    inline static const std::string name = "Velocity";
};

}
}
