#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct HealthComponent : public Component{
public:
    HealthComponent(): Component("HealthComponent"), hp(defaultHp), maxHp(hp) {}
    explicit HealthComponent(int hp): Component("HealthComponent"), hp(hp), maxHp(hp){}

    std::string toString() const override;

    int hp;
    int maxHp;

private:
    inline static const int defaultHp = 100;
};

}
}
