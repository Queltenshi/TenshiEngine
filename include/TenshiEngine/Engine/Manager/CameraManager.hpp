#pragma once

#include "Manager.hpp"
#include "BackgroundManager.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include "TenshiEngine/Engine/Camera/Camera.hpp"

namespace te{
namespace managers{

/**
 * @brief Manager for cameras
 *
 * Creates and updates the cameras for setting the view field
 * Is created automatically in the GameBase
 */
class CameraManager : public Manager{
public:
    /**
     * @brief Creates the manager
     *
     * creates the CameraManager with given windowSize
     *
     * @param registry Pointer to the registry
     * @param backgroundManager Pointer to the backgroundManager
     * @param windowSize Size of window
     */
    void create(Registry *registry, BackgroundManager *backgroundManager, sf::Vector2f windowSize);

    /**
     * @brief updates the active camera
     *
     * updates the current view of active camera
     */
    void update();

    /**
     * @brief Sets the triggerDistance
     *
     * Sets the distance from entity to window which is needed to activate camera movement
     * @param triggerDistance Distance as ratio to windowSize
     */
    void setTriggerDistance(const sf::Vector2f triggerDistance);
    
    /**
     * @brief adds camera
     *
     * Adds camera with given entityID
     * and sets it as activeCamera if there is no other camera
     *
     * @param entityID ID of entity which will be attached to camera 
     */
    void addCamera(EntityID entityID);

    /**
     * @brief adds camera
     *
     * Adds camera with given entityID, and movement direction
     * and sets it as activeCamera if there is no other camera
     *
     * @param entityID ID of entity which will be attached to camera
     * @param movement movement direction in which the camera can be moved
     */
    void addCamera(EntityID entityID, Camera::Movement movement);

    /**
     * @brief sets active camera
     *
     * Sets active camera with given entityID
     * @param entityID ID of entity activated camera 
     */
    void setCamera(EntityID entitiyID);

    /**
     * @brief gets the active camera
     *
     * Returns the active camera
     */
    Camera *getActiveCamera();

private:
    Registry *mRegistry;
    BackgroundManager *mBackgroundManager;
    sf::Vector2f mWindowSize;
    Camera *mActiveCamera;
    std::vector<Camera> mCameras;
    sf::Vector2f mTriggerDistance;

    static const sf::Vector2f defaultTriggerDistance;
    static const std::string name;
};

}
}
