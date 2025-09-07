#pragma once

#include <SFML/Graphics.hpp>
#include "TenshiEngine/Engine/Core/Logger.hpp"

namespace te{
namespace managers{

/**
 * @brief Manager for background image
 *
 * Creates and updates the background image
 */
class BackgroundManager{
public:
    /**
     * @brief Constructor
     *
     * creates the BackgroundManager with given defaultTexture windowSize
     *
     * @param defaultTexture defaultTexture
     * @param windowSize Size of window
     */
    BackgroundManager(std::shared_ptr<sf::Texture> defaultTexture, sf::Vector2f windowSize);

    /**
     * @brief Sets the background
     *
     * Sets the background with given texture and
     * sets parallaxFactor to 0.f
     *
     * @param texture texture for background
     */
    void setBackground(std::shared_ptr<sf::Texture> texture);

    /**
     * @brief Sets the background
     *
     * Sets the background with given texture, movement and parallaxFactor
     *
     * @param texture texture for background
     * @param parallaxFactor factor for the moving speed
     */
    void setBackground(std::shared_ptr<sf::Texture> texture, float parallaxFactor);

    /**
     * @brief Gets the background
     *
     * Gets a reference to the current background
     */
    sf::Sprite &getBackground();
    
    /**
     * @brief Updates the background
     *
     * Updates the background position if camera has moved and movement is true
     *
     * @param move Value of movement
     */
    void update(sf::Vector2f &move);

private:
    sf::Vector2f changeScale();

    sf::Vector2f mWindowSize;
    std::shared_ptr<sf::Texture> mTexture;
    sf::Sprite mBackground;
    float mParallaxFactor;

    static const std::string name;
};

}
}
