#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with input states
 *
 * stores the input states of which actions are pressed
 */
struct PlayerInput : public Component{
public:

    /**
     * @brief Constructor
     *
     * creates the component
     */
    PlayerInput() = default;

    std::string toString () const override{
        return "(up: " + utils::boolToString(up) + " | " + 
               "down: " + utils::boolToString(down) + " | " +
               "left: " + utils::boolToString(left) + " | " +
               "right: " + utils::boolToString(right) + " | " +
               "jump: " + utils::boolToString(jump) + " | " +
               "sprint: " + utils::boolToString(sprint) + " | " +
               "crouch: " + utils::boolToString(crouch) + " | " +
               "attack: " + utils::boolToString(attack) + ")";
    };

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool jump = false;
    bool sprint = false;
    bool crouch = false;
    bool attack = false;

    ///Name of component
    inline static const std::string name = "PlayerInput";
};

}
}
