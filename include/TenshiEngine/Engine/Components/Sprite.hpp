#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with sprite/texture
 *
 * stores a sprite and texture
 */
struct Sprite : public Component{
public:
    /**
     * @brief Constructor
     *
     * creates the component with given texture and
     * sets it to the sprite
     *
     * @param texture texture for the sprite
     */
    Sprite(sf::Texture &texture): texture(texture), sprite(texture){
        sprite.setOrigin(sprite.getGlobalBounds().size / 2.f);
    }

    ///Texture for the sprite
    sf::Texture &texture;

    ///Sprite used for rendering
    sf::Sprite sprite;

    std::string toString() const override{
        return "";
    }

    ///Name of component
    inline static const std::string name = "Sprite";
};

}
}
