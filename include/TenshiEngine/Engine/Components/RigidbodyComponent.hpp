#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct RigidbodyComponent : public Component{
public:
    RigidbodyComponent(): Component("RigidbodyComponent"), mass(defaultMass){}
    explicit RigidbodyComponent(float mass): Component("RigidbodyComponent"), mass(mass){}

    std::string toString() const override;

    float mass;

private:
    inline static const float defaultMass = 10.f;
};

}
}
