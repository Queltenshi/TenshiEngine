#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct ColliderComponent : public Component{
public:
    ColliderComponent(): Component("ColliderComponent"){}

    std::string toString() const override;
};

}
}
