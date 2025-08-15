#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <array>
#include <cstdint>
#include <string>

namespace te{
namespace systems{

class InputSystem : public System{
public:
    InputSystem(Registry &registry);

    void update() override; 

private:
    //Key gets loaded from File
    enum class InputType{MOUSE, KEYBOARD};
    struct Key{
        Key(InputType inputType, const std::string keyName, const std::string keyBind)
            :inputType(inputType), keyName(keyName), keyBind(keyBind){}
        InputType inputType;
        std::string keyName;
        std::string keyBind;
    };

    void keyPressed(Key &key, EntityID entityID);
    uint8_t keyNameToCode(std::string &keyName);
    void updateComponent(std::string &keyBind, components::PlayerInputComponent *component, EntityID entityID);

    Key playerUp;
    Key playerDown;
    Key playerLeft;
    Key playerRight;
    Key playerJump;
    Key playerSprint;
    Key playerCrouch;
    Key playerAttack;
    std::array<Key*, 8> keys;
};

}
}
