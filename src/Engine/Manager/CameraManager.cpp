#include "TenshiEngine/Engine/Manager/CameraManager.hpp"

namespace te{
namespace managers{

CameraManager::CameraManager(Registry &registry, BackgroundManager &backgroundManager, sf::Vector2f windowSize):
    mRegistry(registry), mBackgroundManager(backgroundManager), mWindowSize(windowSize), mActiveCamera(nullptr), mTriggerDistance(defaultTriggerDistance){
}

void CameraManager::update(){
    if(mCameras.size() == 0){
        return;
    }

    sf::Vector2f oldCameraPosition = mActiveCamera->position;
    sf::Vector2f &cameraPosition = mActiveCamera->position;
    auto &entityPosition = mRegistry.getComponent<components::Transform>(mActiveCamera->entityID)->position;

    if(mActiveCamera->movement != Camera::Movement::VERTICAL){
        if(entityPosition.x < cameraPosition.x - (mWindowSize.x * mTriggerDistance.x)){
            cameraPosition.x = entityPosition.x + (mWindowSize.x * mTriggerDistance.x);
        }
        else if(entityPosition.x > cameraPosition.x + (mWindowSize.x * mTriggerDistance.x)){
            cameraPosition.x = entityPosition.x - (mWindowSize.x * mTriggerDistance.x);
        }
    }

    if(mActiveCamera->movement != Camera::Movement::HORIZONTAL){
        if(entityPosition.y < cameraPosition.y - (mWindowSize.y * mTriggerDistance.y)){
            cameraPosition.y = entityPosition.y + (mWindowSize.y * mTriggerDistance.y);
        }
        else if(entityPosition.y > cameraPosition.y + (mWindowSize.y * mTriggerDistance.y)){
            cameraPosition.y = entityPosition.y - (mWindowSize.y * mTriggerDistance.y);
        }
    }

    if(cameraPosition != oldCameraPosition){
        mActiveCamera->view.setCenter(cameraPosition);
        sf::Vector2f move = oldCameraPosition - cameraPosition;
        mBackgroundManager.update(move);
    }
}

void CameraManager::setTriggerDistance(const sf::Vector2f triggerDistance){
    mTriggerDistance = triggerDistance;
}

void CameraManager::addCamera(EntityID entityID){
    auto transform = mRegistry.getComponent<components::Transform>(entityID);
    sf::Vector2f position = {transform->position.x, static_cast<float>(mWindowSize.y) / 2.f}; 
    Camera camera(position, mWindowSize, entityID);
    Logger::info(name, "Camera created: " + camera.toString());
    mCameras.push_back(camera);

    if(mCameras.size() == 1){
        mActiveCamera = &mCameras.front();
    }
}

void CameraManager::addCamera(EntityID entityID, Camera::Movement movement){
    auto transform = mRegistry.getComponent<components::Transform>(entityID);
    sf::Vector2f position = {transform->position.x, static_cast<float>(mWindowSize.y) / 2.f}; 
    Camera camera(position, mWindowSize, entityID, movement);
    Logger::info(name, "Camera created: " + camera.toString());
    mCameras.push_back(camera);

    if(mCameras.size() == 1){
        mActiveCamera = &mCameras.front();
    }
}

void CameraManager::setCamera(EntityID entityID){
    for(auto &camera : mCameras){
        if(camera.entityID == entityID){
            mActiveCamera = &camera; 
            return;
        }
    }
    Logger::error(name, "No Camera found with given entityID: " + std::to_string(entityID));
}

Camera *CameraManager::getActiveCamera(){
    return mActiveCamera;
}

const sf::Vector2f CameraManager::defaultTriggerDistance = {1/5.f, 1/4.f};
const std::string CameraManager::name = "CameraManager";

}
}
