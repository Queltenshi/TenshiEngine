#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace te{
namespace components{

struct TransformComponent : public Component{
public:
    TransformComponent(): position(defaultPosition), scale(defaultScale){}

    std::string toString() const override{
        return "TestTransform";
    };
    std::string name() const override{
        return "TransformComponent";
    };

    sf::Vector2f position;
    sf::Vector2f scale;

private:
    inline static const sf::Vector2f defaultPosition{0.f, 0.f};
    inline static const sf::Vector2f defaultScale{1.f, 1.f};
};

}
}
