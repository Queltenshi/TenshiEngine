#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

/**
 * @brief System for updating animation
 *
 * Checks state, animation and then updates
 * the direction and state of texture
 */
class AnimationSystem : public VariableSystem{
public:    
    /**
     * @brief Constructor
     *
     * creates the System
     *
     * @param registry reference to the registry
     * @param deltaTime Variable deltaTime
     */
    AnimationSystem(Registry &registry, float &deltaTime);

    void update(); 

    //Name of system
    static const std::string name;

private:
    void checkDirection(EntityID entityID, components::State *state);
    void checkState(EntityID entityID, components::State *state);
    void updateTexture(EntityID entityID, components::Animation *animation, json &frame); 
};

}
}
