#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct VelocityComponent : public Component{
public:
    VelocityComponent() = default;

    std::string toString() const override;
    std::string name() const override;
};

}
}
