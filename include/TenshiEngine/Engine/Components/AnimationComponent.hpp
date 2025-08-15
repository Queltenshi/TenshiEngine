#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct AnimationComponent : public Component{
public:
    AnimationComponent() = default;

    std::string toString() const override;
    std::string name() const override;
};

}
}
