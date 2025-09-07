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
    Sprite(std::shared_ptr<sf::Texture> texture): texture(std::move(texture)), sprite(*this->texture){
        sprite.setOrigin({sprite.getTextureRect().size.x / 2.f, sprite.getTextureRect().size.y / 2.f});
    }

    /**
     * @brief Constructor
     *
     * creates the component with given texture and animationRectangle
     * sets it to the sprite
     *
     * @param texture texture for the sprite
     * @param animationRectangle rectangle for setting the texture to default animation
     */
    Sprite(std::shared_ptr<sf::Texture> texture, sf::IntRect &animationRectangle): texture(std::move(texture)), sprite(*this->texture){
        sprite.setTextureRect(animationRectangle);
        sprite.setOrigin({sprite.getTextureRect().size.x / 2.f, sprite.getTextureRect().size.y / 2.f});
    }

    ///Texture for the sprite
    std::shared_ptr<sf::Texture> texture;

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
