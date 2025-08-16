#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct JumpComponent : public Component{
public:
    JumpComponent(): Component("JumpComponent"){}

    std::string toString() const override;
};

}
}
