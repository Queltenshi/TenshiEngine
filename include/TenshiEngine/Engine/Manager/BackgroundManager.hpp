#pragma once

#include "Manager.hpp"
#include <SFML/Graphics.hpp>
#include "TenshiEngine/Engine/Core/Logger.hpp"

namespace te{
namespace managers{

/**
 * @brief Manager for background image
 *
 * Creates and updates the background image
 * Is created automatically in the GameBase
 */
class BackgroundManager : public Manager{
public:
    /**
     * @brief Constructor
     *
     * Default Constructor
     *
     * @param defaultTexture defaultTexture
     */
    BackgroundManager(std::shared_ptr<sf::Texture> defaultTexture);

    /**
     * @brief Creates the manager
     *
     * Creates the TileMapManager
     *
     * @param windowSize Size of window
     */
    void create(sf::Vector2f windowSize);

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
