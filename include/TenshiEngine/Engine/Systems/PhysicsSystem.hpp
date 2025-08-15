#pragma once

#include "System.hpp"

namespace te{
namespace systems{

class PhysicsSystem : public System{
public:
    PhysicsSystem(Registry &registry);

    void update() override; 
};

}
}
