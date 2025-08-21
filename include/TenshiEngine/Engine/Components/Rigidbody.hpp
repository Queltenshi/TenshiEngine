#pragma once

#include <TenshiEngine/Engine/Utils/boolToString.hpp>
#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with physical attributes
 *
 * stores value of mass
 */
struct Rigidbody : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    Rigidbody() = default;

    /**
     * @brief Constructor
     *
     * creates the component with given mass
     * @param mass value of mass
     */
    Rigidbody(float mass): mass(mass){}

    std::string toString() const override{
        return "(mass: "  + std::to_string(mass) + " | " + "isStatic: " + utils::boolToString(isStatic) + ")";
    };

    ///value of mass
    float mass = 100.f;

    ///stores if the object is static or not
    bool isStatic = false;

    ///Name of component
    inline static const std::string name = "Rigidbody";
};

}
}
