#pragma once

#include "System.hpp"
namespace te{
namespace systems{

class MovementSystem : public System{
public:
    MovementSystem(Registry &registry);

    void update() override; 
};

}
}
