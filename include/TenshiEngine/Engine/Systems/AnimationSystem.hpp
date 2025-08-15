#pragma once

#include "System.hpp"

namespace te{
namespace systems{

class AnimationSystem : public System{
public:    
    AnimationSystem(Registry &registry);

    void update() override; 
};

}
}
