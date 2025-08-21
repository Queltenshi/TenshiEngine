#pragma once

#include <iostream>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct PlayerState : public Component{
public:
    PlayerState() = default;

    std::string toString() const override;

    ///Name of component
    inline static const std::string name = "PlayerState";
};

}
}
