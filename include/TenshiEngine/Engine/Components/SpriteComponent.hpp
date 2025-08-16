#pragma once

#include <SFML/Graphics.hpp>
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
struct SpriteComponent : public Component{
public:
    /**
     * @brief Constructor
     *
     * creates the component with given texture
     *
     * @param texture texture for the sprite
     */
    explicit SpriteComponent(sf::Texture &texture): Component("SpriteComponent"), texture(texture), sprite(texture){}

    ///Texture for the sprite
    sf::Texture &texture;

    ///Sprite used for rendering
    sf::Sprite sprite;
    
    std::string toString() const override{
        return "Dabu";
    }
};

}
}
