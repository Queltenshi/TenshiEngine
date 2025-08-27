#pragma once

#include "State.hpp"
#include "TenshiEngine/Engine/Components/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Rect.hpp>

using json = nlohmann::json;

namespace te{
namespace components{

/**
 * @brief component with animation data
 *
 * stores time and data for animations
 */
struct Animation : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component with given textureData and
     * sets rectangle to idle
     *
     * @param textureData json data used for animation
     */
    Animation(json &textureData): textureData(textureData){
        auto idleFrame = textureData["animations"]["idle"][0];
        rectangle.size = {idleFrame["w"], idleFrame["h"]};
        rectangle.position = {idleFrame["x"], idleFrame["y"]};
    }

    enum class CurrentAnimation{IDLE, WALK, JUMP, FALL, HIT};

    std::string toString() const override{
        return "(iterator: " + std::to_string(iterator) + " | " + 
               "elapsedTime: " + std::to_string(elapsedTime) + " | " + 
               "switchTime: " + std::to_string(switchTime) + " | " + 
               "currentAnimation: " + animationToString(currentAnimation) + ")"; 
    }

    ///Iterator for current animation
    int iterator = 0;

    ///Elapsed time, which is used for next animation
    float elapsedTime = 0.f;

    ///Time for next animation
    float switchTime = 0.2f;

    ///Current rectangle of sprite sheet
    sf::IntRect rectangle;

    ///Json data used for animation
    json &textureData;

    ///Current animation
    CurrentAnimation currentAnimation = CurrentAnimation::IDLE;

    ///Name of component
    inline static const std::string name = "Animation";

private:
    static std::string animationToString(CurrentAnimation currentAnimation) {
        switch (currentAnimation) {
            case CurrentAnimation::IDLE: return "IDLE";
            case CurrentAnimation::WALK:  return "WALK";
            case CurrentAnimation::JUMP:  return "JUMP";
            case CurrentAnimation::FALL:  return "FALL";
            case CurrentAnimation::HIT: return "HIT";
            default: return "UNKNOWN";
        }
    }
};

}
}
