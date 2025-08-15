#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct PlayerStateComponent : public Component{
public:
    PlayerStateComponent() = default;

    std::string toString() const override;
    std::string name() const override;
};

}
}
