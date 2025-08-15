#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct ColliderComponent : public Component{
public:
    ColliderComponent() = default;

    std::string toString() const override;
    std::string name() const override;
};

}
}
