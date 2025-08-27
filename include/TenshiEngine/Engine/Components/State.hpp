#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with current state
 *
 * stores the current state and direction in which the entity is facing
 */
struct State : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    State() = default;

    enum class CurrentState{IDLE, WALK, JUMP, FALL, HIT};
    enum class Direction{LEFT, RIGHT}; 

    std::string toString() const override{
        return "(currentState: " + stateToString(currentState) + " | " + "direction: " + directionToString(direction) + ")";
    };

    ///current state
    CurrentState currentState = CurrentState::IDLE;

    //current direction in which the entity is facing
    Direction direction = Direction::RIGHT;

    ///Name of component
    inline static const std::string name = "State";

private:
    static std::string stateToString(CurrentState stateType) {
        switch (stateType) {
            case CurrentState::IDLE: return "IDLE";
            case CurrentState::WALK:  return "WALK";
            case CurrentState::JUMP:  return "JUMP";
            case CurrentState::FALL:  return "FALL";
            case CurrentState::HIT: return "HIT";
            default: return "UNKNOWN";
        }
    }

    static std::string directionToString(Direction direction) {
        switch (direction) {
            case Direction::LEFT: return "LEFT";
            case Direction::RIGHT:  return "RIGHT";
            default: return "UNKNOWN";
        }
    }
};

}
}
