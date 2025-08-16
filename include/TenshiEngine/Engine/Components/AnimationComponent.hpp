#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct AnimationComponent : public Component{
public:
    AnimationComponent(): Component("AnimationComponent"){}

    std::string toString() const override;
};

}
}
