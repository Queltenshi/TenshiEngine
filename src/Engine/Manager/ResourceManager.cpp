#include "TenshiEngine/Engine/Manager/ResourceManager.hpp"

namespace te{
namespace managers{

ResourceManager::ResourceManager(){
    auto defaultTexture = std::make_shared<sf::Texture>();
    if(!defaultTexture->loadFromMemory(DefaultTexture_png, DefaultTexture_png_len)){
        Logger::error(name, "DefaultTexture could not be loaded");
    } 
    else {
        Logger::info(name, "DefaultTexture loaded");
    }
    mTextures.insert({"Default", defaultTexture});
}   


std::shared_ptr<sf::Texture> ResourceManager::addTexture(const std::string &textureName, const std::string &filePath){
    auto it = mTextures.find(textureName);
    if(it != mTextures.end()){
        Logger::warning(name, "Texture " + textureName + " already exist, using default texture");
        return mTextures["Default"];
    }

    auto texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(filePath)){
        Logger::warning(name, "Texture " + textureName + " could not be loaded, using default texture");
        return mTextures["Default"];
    }

    Logger::info(name, "Texture " + textureName + " loaded");
    mTextures.insert({textureName, texture});
    return texture;
}

std::shared_ptr<json> ResourceManager::addJson(const std::string &jsonName, const std::string &filePath){
    auto it = mJsons.find(jsonName);
    if(it != mJsons.end()){
        Logger::error(name, "Json " + jsonName + " already exist");
        return std::make_shared<json>();
    }

    std::ifstream file(filePath);
    if(!file.is_open()){
        Logger::error(name, "Json " + jsonName + " could not be loaded");
        return std::make_shared<json>();
    }

    auto data = std::make_shared<json>();
    *data = json::parse(file);

    mJsons.insert({jsonName, data});
    return data;
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &textureName){
    auto it = mTextures.find(textureName);
    if(it == mTextures.end()){
        Logger::warning(name, "Texture " + textureName + " does not exist, using default texture");
        return mTextures["Default"];
    }
    return mTextures[textureName];
}

std::shared_ptr<json> ResourceManager::getJson(const std::string &jsonName){
    auto it = mJsons.find(jsonName);
    if(it == mJsons.end()){
        Logger::error(name, "Json " + jsonName + " does not exist");
        return std::make_shared<json>();
    }
    return mJsons[jsonName];
}

const std::string ResourceManager::name = "ResourceManager";

}
}
