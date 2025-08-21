#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with jump strength
 *
 * stores value of jumping strength
 */
struct Jump : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    Jump() = default;

    /**
     * @brief Constructor 
     *
     * creates the component with given strength
     *
     * @param strength value of jumping strength
     */
    Jump(float strength): strength(strength){}

    std::string toString() const override{
        return "(strength: " + std::to_string(strength) + ")";
    }

    ///value of jumping strength
    float strength = 16.f;

    ///Name of component
    inline static const std::string name = "Jump";
};

}
}
