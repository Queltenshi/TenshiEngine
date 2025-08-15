#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct NameComponent : public Component{
public:
    explicit NameComponent(const std::string &characterName): characterName(characterName){}

    std::string toString() const override;
    std::string name() const override;

    std::string characterName;
};

}
}
