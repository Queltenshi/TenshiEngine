#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct GroundedComponent : public Component{
public:
    GroundedComponent(): Component("GroundedComponent"){}

    std::string toString() const override;
};

}
}
