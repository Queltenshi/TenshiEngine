#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct Animation : public Component{
public:
    Animation() = default;

    std::string toString() const override;

    ///Name of component
    inline static const std::string name = "Animation";
};

}
}
