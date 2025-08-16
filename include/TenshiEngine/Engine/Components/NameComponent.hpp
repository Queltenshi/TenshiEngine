#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct NameComponent : public Component{
public:
    explicit NameComponent(const std::string &characterName): Component("NameComponent"), characterName(characterName){}

    std::string toString() const override;

    std::string characterName;
};

}
}
