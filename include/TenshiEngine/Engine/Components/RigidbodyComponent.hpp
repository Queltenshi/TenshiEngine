#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct RigidbodyComponent : public Component{
public:
    RigidbodyComponent(): mass(defaultMass){}
    explicit RigidbodyComponent(float mass): mass(mass){}

    std::string toString() const override;
    std::string name() const override;

    float mass;

private:
    inline static const float defaultMass = 10.f;
};

}
}
