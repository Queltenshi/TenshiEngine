#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{
namespace systems{

class AnimationSystem : public VariableSystem{
public:    
    AnimationSystem(Registry &registry, float &deltaTime);

    void update(); 

    static const std::string name;

private:
    void checkDirection(EntityID entityID, components::State *state);
    void checkState(EntityID entityID, components::State *state);
    void updateTexture(EntityID entityID, components::Animation *animation, json &frame); 
};

}
}
