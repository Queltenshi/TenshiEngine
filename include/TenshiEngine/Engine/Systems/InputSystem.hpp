#pragma once

#include "System.hpp"
#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdint>


namespace te{
namespace systems{

class InputSystem : public VariableSystem{
public:
    enum class Action{MOVELEFT, MOVERIGHT, JUMP, SPRINT, CROUCH, ATTACK};
    enum class Key{Q, W, E, R, T, Z, U, I, O, P, A, S, D, F, G, H, J, K, L, Y, X, C, V, B, N, M, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0, SPACE, L_SHIFT, L_CONTROL, MOUSE_LEFT, MOUSE_RIGHT};

    InputSystem(Registry &registry, float &deltaTime, std::unordered_map<Action, Key> configKeyBinds);

    void update() override; 

    static const std::string name;

private:
    enum class InputType{MOUSE, KEYBOARD};
    struct KeyBind{
        KeyBind(InputType inputType, Action action, Key key)
            :inputType(inputType), action(action), key(key){}
        InputType inputType;
        Key key;
        Action action;
        uint8_t keyCode;
    };

    void keyPressed(KeyBind &keyBind, EntityID entityID);
    uint8_t keyToCode(Key key);
    void updateSteering(Action &action, components::Steering *steering, EntityID entityID);

    std::vector<KeyBind> keyBinds;
};

}
}
