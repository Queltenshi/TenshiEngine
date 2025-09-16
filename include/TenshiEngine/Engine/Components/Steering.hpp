#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with steering actions
 *
 * stores which steering actions are activated
 */
struct Steering : public Component{
public:
    /**
     * @brief Constructor
     *
     * creates the component
     */
    Steering() = default;


    std::string toString () const override{
        return "(left: " + utils::boolToString(left) + " | " +
               "right: " + utils::boolToString(right) + " | " +
               "jump: " + utils::boolToString(jump) + " | " +
               "sprint: " + utils::boolToString(sprint) + " | " +
               "crouch: " + utils::boolToString(crouch) + " | " +
               "attack: " + utils::boolToString(attack) + ")";
    };

    bool left = false;
    bool right = false;
    bool jump = false;
    bool sprint = false;
    bool crouch = false;
    bool attack = false;

    ///Name of component
    inline static const std::string name = "Steering";
};

}
}
