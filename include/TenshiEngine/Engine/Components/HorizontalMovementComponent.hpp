#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct HorizontalMovementComponent : Component{
public:
    HorizontalMovementComponent(): Component("HorizontalMovementComponent"){}
    
    std::string toString() const override;
};

}
}
