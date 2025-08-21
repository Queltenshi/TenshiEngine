#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct Health : public Component{
public:
    Health(): hp(defaultHp), maxHp(hp) {}
    Health(int hp): hp(hp), maxHp(hp){}

    std::string toString() const override;

    int hp;
    int maxHp;

    ///Name of component
    inline static const std::string name = "Health";

private:
    inline static const int defaultHp = 100;
};

}
}
