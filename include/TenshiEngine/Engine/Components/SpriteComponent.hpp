#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

struct SpriteComponent : public Component{
public:
    explicit SpriteComponent(sf::Texture &texture): texture(texture), sprite(texture){}

    sf::Texture &texture;
    sf::Sprite sprite;
    
    std::string toString() const override{
        return "Dabu";
    }
    std::string name() const override{
        return "SpriteComponent";
    }
};

}
}
