#pragma once

#include <string>
#include <unordered_map>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with input states
 *
 * stores the input states of which actions are pressed
 */
struct PlayerInputComponent : public Component{
public:

    /**
     * @brief Constructor
     *
     * creates the component
     */
    PlayerInputComponent(): Component("PlayerInputComponent"){}

    std::string toString () const override{
        return "(up: " + utils::boolToString(up) + " | " + 
               "down: " + utils::boolToString(down) + " | " +
               "left: " + utils::boolToString(left) + " | " +
               "right: " + utils::boolToString(right) + " | " +
               "jump: " + utils::boolToString(jump) + " | " +
               "sprint: " + utils::boolToString(sprint) + " | " +
               "crouch: " + utils::boolToString(crouch) + " | " +
               "attack: " + utils::boolToString(attack) + 
               ")";
    };

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool jump = false;
    bool sprint = false;
    bool crouch = false;
    bool attack = false;
};

}
}
