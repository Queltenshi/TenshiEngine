#pragma once

#include "TenshiEngine/Engine/Core/Logger.hpp"
#include "TenshiEngine/Assets/Textures/DefaultTexture.h"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace te{
namespace managers{

/**
 * @brief Manager for resources
 *
 * stores different types of resources
 */
class ResourceManager{
public:
    /**
     * @brief Constructor
     *
     * creates the Manager
     */
    ResourceManager();

    /**
     * @brief Adds new texture
     *
     * Adds and returns new texture with given name and filePath
     *
     * @param name Name of texture
     * @param filePath Filepath to texture
     */
    std::shared_ptr<sf::Texture> addTexture(const std::string &name, const std::string &filePath);

    /**
     * @brief Adds new Json
     *
     * Adds and returns new json with given name and filePath
     *
     * @param name Name of json
     * @param filePath Filepath to json
     */
    std::shared_ptr<json> addJson(const std::string &name, const std::string &filePath);

    /**
     * @brief gets texture
     *
     * returns texture with given name
     *
     * @param name Name of texture
     */
    std::shared_ptr<sf::Texture> getTexture(const std::string &name);

    /**
     * @brief gets json
     *
     * returns json with given name
     *
     * @param name Name of json
     */
    std::shared_ptr<json> getJson(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTextures;
    std::unordered_map<std::string, std::shared_ptr<json>> mJsons;

    static const std::string name;
};

}
}
