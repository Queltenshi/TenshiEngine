#pragma once

#include "brofield/SimpleIni.h"
#include "TenshiEngine/Engine/Systems/InputSystem.hpp"

using namespace te::systems;

namespace te{

class Config{
public:
    Config();
    
    std::string getGameName();
    bool isDebugMode();
    bool isFullscreen();
    uint getFPS();
    sf::Vector2u getResolution();
    float getGravityForce();
    std::unordered_map<InputSystem::Action, InputSystem::Key> getKeyBinds();

private:
    void loadFile();
    void saveFile();
    void loadVideoSection();
    void loadInputSection();
    void loadSystemSection();
    template<typename T> T loadValue(const char *section, const char *key, const T defaultValue); 
    std::optional<InputSystem::Key> charToKey(const char* keyName);
    const char* keyToChar(InputSystem::Key inputKey);

    CSimpleIniA mIni;
    std::string mGameName;
    bool mDebugMode;
    bool mFullscreen;
    uint mFPS;
    uint mResolutionWidth;
    uint mResolutionHeight;
    float mGravityForce;
    std::unordered_map<InputSystem::Action, InputSystem::Key> mKeyBinds;

    //Section names
    const static char* videoSection;
    const static char* inputSection;
    const static char* systemSection;

    //Default settings
    const static std::string defaultGameName;
    const static bool defaultDebugMode;
    const static bool defaultFullscreen;
    const static uint defaultFPS;
    const static uint defaultResolutionWidth;
    const static uint defaultResolutionHeight;
    const static float defaultGravityForce;
    
    //Default keyBinds
    const static InputSystem::Key defaultMoveLeft;
    const static InputSystem::Key defaultMoveRight;
    const static InputSystem::Key defaultJump;
    const static InputSystem::Key defaultSprint;
    const static InputSystem::Key defaultCrouch;
    const static InputSystem::Key defaultAttack;

    const static char* fileName;

    const static std::string name;
};

}
