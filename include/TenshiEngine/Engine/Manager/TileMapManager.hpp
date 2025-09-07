#pragma once

#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <memory>

namespace te{
namespace managers{

/**
 * @brief Manager for creating tile maps
 *
 * loads leveldata and spritesheets from files and
 * creates tile maps from them
 */
class TileMapManager{
public:
    /**
     * @brief Constructor
     *
     * creates the Manager
     *
     * @param registry Reference to the registry
     */
    TileMapManager(Registry &registry);

    /**
     * @brief Loads the tileset
     *
     * Loads the tileset with given texture and json file
     *
     * @param tilesetTexture Texture of the tileset
     * @param tilesetData Json data of the tileset
     */
    void loadTileset(std::shared_ptr<sf::Texture> tilesetTexture, std::shared_ptr<json> tilesetData);

    /**
     * @brief loads the level
     *
     * loads the level with given given json file path
     *
     * @param levelData Json data of the tileset
     */
    void loadLevel(std::shared_ptr<json> levelData);

private:
    std::vector<std::vector<int>> loadLevel(sf::Vector2i levelSize, std::shared_ptr<json> levelData);
    void createEntities(std::vector<std::vector<int>> &level, sf::Vector2i levelSize);

    Registry &mRegistry;
    std::shared_ptr<sf::Texture> mTilesetTexture;
    sf::Vector2i mTileSize;
    std::vector<int> mColliders;

    static const std::string name;
};

}
}
