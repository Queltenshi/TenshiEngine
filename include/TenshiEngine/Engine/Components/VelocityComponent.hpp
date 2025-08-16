#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct VelocityComponent : public Component{
public:
    VelocityComponent(): Component("VelocityComponent"){}

    std::string toString() const override;
};

}
}
