#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with horizontal movement
 *
 * stores value of movement speed for horizontal movement
 */
struct HorizontalMovement : Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    HorizontalMovement() = default;

    /**
     * @brief Constructor 
     *
     * creates the component with given speed
     *
     * @param speed value for movement speed
     */
    HorizontalMovement(float speed): speed(speed){} 

    std::string toString() const override{
        return "(speed: " + std::to_string(speed) + ")";
    }

    ///value for speed
    float speed = 10.f;

    ///Name of component
    inline static const std::string name = "HorizontalMovement";
};

}
}
