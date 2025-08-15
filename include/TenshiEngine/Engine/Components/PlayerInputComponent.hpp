#pragma once

#include <string>
#include <unordered_map>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct PlayerInputComponent : public Component{
public:
    PlayerInputComponent() = default;

    std::string toString () const override{
        return "(up: " + boolToString(up) + " | " + 
               "down: " + boolToString(down) + " | " +
               "left: " + boolToString(left) + " | " +
               "right: " + boolToString(right) + " | " +
               "jump: " + boolToString(jump) + " | " +
               "sprint: " + boolToString(sprint) + " | " +
               "crouch: " + boolToString(crouch) + " | " +
               "attack: " + boolToString(attack) + 
               ")";
    };

    std::string name() const override{
        return "PlayerInputComponent";
    };

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool jump = false;
    bool sprint = false;
    bool crouch = false;
    bool attack = false;

private:
    std::string boolToString(bool boolean) const{
        if(boolean)
            return "true";
        return "false";
    };
};

}
}
