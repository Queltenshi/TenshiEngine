#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdint>
#include <string>

namespace te{
namespace systems{

/**
 * @brief System for input handling
 *
 * Checks the pressed keys from the system and
 * changes the inputComponents depending on Hotkeys
 */
class InputSystem : public VariableSystem{
public:

    /**
     * @brief Constructor
     *
     * creates the System
     *
     * @param registry reference to the registry
     * @param deltaTime reference to the frame delta time
     */
    InputSystem(Registry &registry, float &deltaTime);

    void update() override; 

    ///Name of system
    static const std::string name;

private:
    //Key gets loaded from File
    enum class InputType{MOUSE, KEYBOARD};
    struct Key{
        Key(InputType inputType, const std::string keyName, const std::string keyBind)
            :inputType(inputType), keyName(keyName), keyBind(keyBind){}
        InputType inputType;
        std::string keyName;
        std::string keyBind;
        uint8_t keyCode;
    };

    void keyPressed(Key &key, EntityID entityID);
    uint8_t keyNameToCode(std::string &keyName);
    void updatePlayerInput(std::string &keyBind, components::PlayerInput *inputComponent, EntityID entityID);

    Key keys[8];
};

}
}
