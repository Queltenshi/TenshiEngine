#include "TenshiEngine/Engine/Manager/TileMapManager.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <string>
#include <vector>

namespace te{
namespace managers{

TileMapManager::TileMapManager(Registry &registry): mRegistry(registry), mTileSize(0, 0){}

void TileMapManager::loadTileset(std::shared_ptr<sf::Texture> tilesetTexture, std::shared_ptr<json> tilesetData){
    mTilesetTexture = std::move(tilesetTexture);
    
    if(tilesetData->empty()){
        Logger::error(name, "tileSetData is empty");
        return;
    }

    if(!tilesetData->contains("tilewidth")){
        Logger::error(name, "No tilewidth in tileSetData found");
        return;
    } 
    mTileSize.x = tilesetData->at("tilewidth");

    if(!tilesetData->contains("tileheight")){
        Logger::error(name, "No tileheight in tileSetData found");
        return;
    } 
    mTileSize.y = tilesetData->at("tileheight");

    //Load colliders
    if(!tilesetData->contains("tiles") || tilesetData->at("tiles").empty()){
        Logger::error(name, "No tiles in tileSetData found");
        return;
    }
    for(auto tile : tilesetData->at("tiles")){
        if(!tile.contains("properties") || tile["properties"].empty()){
            Logger::error(name, "No properties in tileSetData tile found");
            return;
        }
        auto properties = tile["properties"];

        for(auto propertie : properties){
            if(!propertie.contains("name") || propertie["name"] != "collider"){
                return;
            }
            if(!propertie.contains("value") && propertie["value"] != "true"){
                Logger::error(name, "No value in tileSetData tile propertie found");
                return;
            }
            if(!tile.contains("id")){
                Logger::error(name, "No id in tileSetData tile found");
                return;
            }
        }
        mColliders.push_back(tile["id"].get<int>() + 1);
    }

    std::string colliders;
    for(auto collider: mColliders){
        colliders += " " + std::to_string(collider);
    }
    Logger::info(name, "Tileset created: (tilesize.x: " + std::to_string(mTileSize.y) + " | " +
                                         "tilesize.y: " + std::to_string(mTileSize.y) + " | " + 
                                         "collider IDs:" + colliders + ")");
}

void TileMapManager::loadLevel(std::shared_ptr<json> levelData){
    if(mTileSize == sf::Vector2i(0, 0)){
        Logger::error(name, "tileSetSize is 0");
        return;
    }

    sf::Vector2i levelSize;
    if(!levelData->contains("width")){
        Logger::error(name, "No width in levelData found");
        return;
    } 
    levelSize.x = levelData->at("width");

    if(!levelData->contains("height")){
        Logger::error(name, "No height in levelData found");
        return;
    } 
    levelSize.y = levelData->at("height");

    if(!levelData->contains("layers") || levelData->at("layers").empty() || !levelData->at("layers")[0].contains("data")){
        Logger::error(name, "No data in levelData found");
        return;
    }

    std::vector<std::vector<int>> level = loadLevel(levelSize, levelData);
    createEntities(level, levelSize);
}

std::vector<std::vector<int>> TileMapManager::loadLevel(sf::Vector2i levelSize, std::shared_ptr<json> levelData){
    std::vector<std::vector<int>> level;
    std::string logInfo;
    for(int i = 0; i < levelSize.y; i++){
        std::vector<int> levelRow;
        for(int j = 0; j < levelSize.x; j++){
            levelRow.push_back(levelData->at("layers")[0]["data"][i * levelSize.x + j]);
            logInfo += std::to_string(levelRow[j]);
        }
        level.push_back(levelRow);
        logInfo += "\n";
    }
    Logger::info(name, "level created: (levelSize.x: " + std::to_string(levelSize.x) + " | " +
                                      "(levelSize.y: " + std::to_string(levelSize.y) + ")\n" +
            logInfo);
    return level;
}

void TileMapManager::createEntities(std::vector<std::vector<int>> &level, sf::Vector2i levelSize){
    sf::IntRect tileRect;
    tileRect.size = mTileSize;
    tileRect.position = {0, 0};

    for(int i = 0; i < levelSize.y; i++){
        for(int j = 0; j < levelSize.x; j++){
            if(level[i][j] == 0){
                continue;
            }

            auto tile = mRegistry.createEntity(mTilesetTexture, mTileSize);
            auto sprite = mRegistry.getComponent<components::Sprite>(tile.id);
            for(auto collider : mColliders){
                if(level[i][j] == collider){
                    mRegistry.addComponent(tile.id, components::Collider(sprite->sprite.getGlobalBounds().size));
                    auto rigidbody = mRegistry.addComponent(tile.id, components::Rigidbody());
                    rigidbody->isStatic = true;
                }
            }

            auto transform = mRegistry.getComponent<components::Transform>(tile.id);
            float positionX = static_cast<float>(j * mTileSize.x + mTileSize.x / 2.f);
            float positionY = static_cast<float>(i * mTileSize.y + mTileSize.y / 2.f);
            transform->position = {positionX, positionY};

            tileRect.position = {level[i][j] * mTileSize.x - mTileSize.x, 0};
            sprite->sprite.setTextureRect(tileRect);
        }
    }

}

const std::string TileMapManager::name = "TileMapManager";

}
}
