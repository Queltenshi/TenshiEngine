#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct PlayerStateComponent : public Component{
public:
    PlayerStateComponent(): Component("PlayerStateComponent"){}

    std::string toString() const override;
};

}
}
