#include "TenshiEngine/Game/Config.hpp"

namespace te{

Config::Config():
    mGameName(defaultGameName),
    mDebugMode(defaultDebugMode),
    mFullscreen(defaultFullscreen),
    mFPS(defaultFPS),
    mResolutionWidth(defaultResolutionWidth),
    mResolutionHeight(defaultResolutionHeight),
    mGravityForce(defaultGravityForce),
    mKeyBinds({
            {InputSystem::Action::MOVELEFT, defaultMoveLeft},
            {InputSystem::Action::MOVERIGHT, defaultMoveRight},
            {InputSystem::Action::JUMP, defaultJump},
            {InputSystem::Action::SPRINT, defaultSprint},
            {InputSystem::Action::CROUCH, defaultCrouch},
            {InputSystem::Action::ATTACK, defaultAttack}}){

    loadFile();

    loadVideoSection();
    loadInputSection();
    loadSystemSection();

    saveFile();
}

void Config::loadFile(){
    mIni.SetUnicode();
    SI_Error rc = mIni.LoadFile(fileName);
    if (rc < 0) {
        Logger::info(name, "Creating " + std::string(fileName) + ":");
        Logger::info(name, "----------------");
        return;
    }

    Logger::info(name, std::string(fileName) + " loaded:");
        Logger::info(name, "----------------");
}

void Config::saveFile(){
    SI_Error rc = mIni.SaveFile(fileName);
    if (rc < 0) {
        Logger::error(name, std::string(fileName) + " could not be saved");
        return;
    }

    Logger::info(name, "----------------");
    Logger::info(name, std::string(fileName) + " saved");
}

void Config::loadVideoSection(){
    Logger::info(name, "[" + std::string(videoSection) + "]");
    mResolutionWidth = loadValue(videoSection, "ResolutionWidth", defaultResolutionWidth);
    mResolutionHeight = loadValue(videoSection, "ResolutionHeight", defaultResolutionHeight);
    mFPS = loadValue(videoSection, "FPS", defaultFPS);
    mFullscreen = loadValue(videoSection, "Fullscreen", defaultFullscreen);
    Logger::info(name, "");
    Logger::info(name, "");
}

void Config::loadInputSection(){
    Logger::info(name, "[" + std::string(inputSection) + "]");
    mKeyBinds[InputSystem::Action::MOVELEFT] = loadValue(inputSection, "MoveLeft", defaultMoveLeft);
    mKeyBinds[InputSystem::Action::MOVERIGHT] = loadValue(inputSection, "MoveRight", defaultMoveRight);
    mKeyBinds[InputSystem::Action::JUMP] = loadValue(inputSection, "Jump", defaultJump);
    mKeyBinds[InputSystem::Action::SPRINT] = loadValue(inputSection, "Sprint", defaultSprint);
    mKeyBinds[InputSystem::Action::CROUCH] = loadValue(inputSection, "Crouch", defaultCrouch);
    mKeyBinds[InputSystem::Action::ATTACK] = loadValue(inputSection, "Attack", defaultAttack);
    Logger::info(name, "");
    Logger::info(name, "");
}

void Config::loadSystemSection(){
    Logger::info(name, "[" + std::string(systemSection) + "]");
    mGameName = loadValue(systemSection, "GameName", defaultGameName);
    mGravityForce = loadValue(systemSection, "GravityForce", defaultGravityForce);
    mDebugMode = loadValue(systemSection, "DebugMode", defaultDebugMode);
    Logger::info(name, "");
}

template<typename T> T Config::loadValue(const char *section, const char *key, const T defaultValue){
    T value;
    if constexpr (std::is_same_v<T, uint>){
        value = mIni.GetLongValue(section, key, defaultValue);
        mIni.SetLongValue(section, key, value);
    }
    else if constexpr (std::is_same_v<T, float>){
        value = mIni.GetDoubleValue(section, key, defaultValue);
        mIni.SetDoubleValue(section, key, value);
    }
    else if constexpr (std::is_same_v<T, bool>){
        value = mIni.GetBoolValue(section, key, defaultValue);
        mIni.SetBoolValue(section, key, value);
    }
    else if constexpr (std::is_same_v<T, std::string>){
        value = mIni.GetValue(section, key, defaultValue.c_str());
        mIni.SetValue(section, key, value.c_str());
    }
    else if constexpr (std::is_same_v<T, InputSystem::Key>){
        const char* defaultKeyName = keyToChar(defaultValue);
        const char* keyName = mIni.GetValue(section, key, defaultKeyName);

        std::optional optionalValue = charToKey(keyName);
        if(optionalValue){
            value = optionalValue.value();
        }
        else{
            value = defaultValue;
            keyName = defaultKeyName;
        }

        mIni.SetValue(section, key, keyName);
    }

    //Log message
    std::string logMessage = std::string(key) + ": ";
    if constexpr (std::is_same_v<T, std::string>){
        logMessage += value;
    }
    else if constexpr (std::is_same_v<T, InputSystem::Key>){
        logMessage += keyToChar(value);
    }
    else if constexpr (std::is_same_v<T, bool>){
        logMessage += utils::boolToString(value);
    }
    else{
        logMessage += std::to_string(value);
    }
    Logger::info(name, logMessage);

    return value;
}

std::optional<InputSystem::Key> Config::charToKey(const char* keyName){
    if(std::string(keyName) == "Q"){
        return InputSystem::Key::Q;
    }
    else if(std::string(keyName) == "W"){
        return InputSystem::Key::W;
    }
    else if(std::string(keyName) == "E"){
        return InputSystem::Key::E;
    }
    else if(std::string(keyName) == "R"){
        return InputSystem::Key::R;
    }
    else if(std::string(keyName) == "T"){
        return InputSystem::Key::T;
    }
    else if(std::string(keyName) == "Z"){
        return InputSystem::Key::Z;
    }
    else if(std::string(keyName) == "U"){
        return InputSystem::Key::U;
    }
    else if(std::string(keyName) == "I"){
        return InputSystem::Key::I;
    }
    else if(std::string(keyName) == "O"){
        return InputSystem::Key::O;
    }
    else if(std::string(keyName) == "P"){
        return InputSystem::Key::P;
    }
    else if(std::string(keyName) == "A"){
        return InputSystem::Key::A;
    }
    else if(std::string(keyName) == "S"){
        return InputSystem::Key::S;
    }
    else if(std::string(keyName) == "D"){
        return InputSystem::Key::D;
    }
    else if(std::string(keyName) == "F"){
        return InputSystem::Key::F;
    }
    else if(std::string(keyName) == "G"){
        return InputSystem::Key::G;
    }
    else if(std::string(keyName) == "H"){
        return InputSystem::Key::H;
    }
    else if(std::string(keyName) == "J"){
        return InputSystem::Key::J;
    }
    else if(std::string(keyName) == "K"){
        return InputSystem::Key::K;
    }
    else if(std::string(keyName) == "L"){
        return InputSystem::Key::L;
    }
    else if(std::string(keyName) == "Y"){
        return InputSystem::Key::Y;
    }
    else if(std::string(keyName) == "X"){
        return InputSystem::Key::X;
    }
    else if(std::string(keyName) == "C"){
        return InputSystem::Key::C;
    }
    else if(std::string(keyName) == "V"){
        return InputSystem::Key::V;
    }
    else if(std::string(keyName) == "B"){
        return InputSystem::Key::B;
    }
    else if(std::string(keyName) == "N"){
        return InputSystem::Key::N;
    }
    else if(std::string(keyName) == "M"){
        return InputSystem::Key::M;
    }
    else if(std::string(keyName) == "0"){
        return InputSystem::Key::NUM0;
    }
    else if(std::string(keyName) == "1"){
        return InputSystem::Key::NUM1;
    }
    else if(std::string(keyName) == "2"){
        return InputSystem::Key::NUM2;
    }
    else if(std::string(keyName) == "3"){
        return InputSystem::Key::NUM3;
    }
    else if(std::string(keyName) == "4"){
        return InputSystem::Key::NUM4;
    }
    else if(std::string(keyName) == "5"){
        return InputSystem::Key::NUM5;
    }
    else if(std::string(keyName) == "6"){
        return InputSystem::Key::NUM6;
    }
    else if(std::string(keyName) == "7"){
        return InputSystem::Key::NUM7;
    }
    else if(std::string(keyName) == "8"){
        return InputSystem::Key::NUM8;
    }
    else if(std::string(keyName) == "9"){
        return InputSystem::Key::NUM9;
    }
    else if(std::string(keyName) == "Space"){
        return InputSystem::Key::SPACE;
    }
    else if(std::string(keyName) == "LShift"){
        return InputSystem::Key::L_SHIFT;
    }
    else if(std::string(keyName) == "LControl"){
        return InputSystem::Key::L_CONTROL;
    }
    else if(std::string(keyName) == "MouseLeft"){
        return InputSystem::Key::MOUSE_LEFT;
    }
    else if(std::string(keyName) == "MouseRight"){
        return InputSystem::Key::MOUSE_RIGHT;
    }
    return {};
}

const char* Config::keyToChar(InputSystem::Key inputKey){
    if (inputKey == InputSystem::Key::A) {
        return "A";
    } 
    else if (inputKey == InputSystem::Key::B) {
        return "B";
    } 
    else if (inputKey == InputSystem::Key::C) {
        return "C";
    } 
    else if (inputKey == InputSystem::Key::D) {
        return "D";
    } 
    else if (inputKey == InputSystem::Key::E) {
        return "E";
    } 
    else if (inputKey == InputSystem::Key::F) {
        return "F";
    } 
    else if (inputKey == InputSystem::Key::G) {
        return "G";
    } 
    else if (inputKey == InputSystem::Key::H) {
        return "H";
    } 
    else if (inputKey == InputSystem::Key::I) {
        return "I";
    } 
    else if (inputKey == InputSystem::Key::J) {
        return "J";
    } 
    else if (inputKey == InputSystem::Key::K) {
        return "K";
    } 
    else if (inputKey == InputSystem::Key::L) {
        return "L";
    } 
    else if (inputKey == InputSystem::Key::M) {
        return "M";
    } 
    else if (inputKey == InputSystem::Key::N) {
        return "N";
    } 
    else if (inputKey == InputSystem::Key::O) {
        return "O";
    } 
    else if (inputKey == InputSystem::Key::P) {
        return "P";
    } 
    else if (inputKey == InputSystem::Key::Q) {
        return "Q";
    } 
    else if (inputKey == InputSystem::Key::R) {
        return "R";
    } 
    else if (inputKey == InputSystem::Key::S) {
        return "S";
    } 
    else if (inputKey == InputSystem::Key::T) {
        return "T";
    } 
    else if (inputKey == InputSystem::Key::U) {
        return "U";
    } 
    else if (inputKey == InputSystem::Key::V) {
        return "V";
    } 
    else if (inputKey == InputSystem::Key::W) {
        return "W";
    } 
    else if (inputKey == InputSystem::Key::X) {
        return "X";
    } 
    else if (inputKey == InputSystem::Key::Y) {
        return "Y";
    } 
    else if (inputKey == InputSystem::Key::Z) {
        return "Z";
    }
    else if (inputKey == InputSystem::Key::NUM0) {
        return "0";
    } 
    else if (inputKey == InputSystem::Key::NUM1) {
        return "1";
    } 
    else if (inputKey == InputSystem::Key::NUM2) {
        return "2";
    } 
    else if (inputKey == InputSystem::Key::NUM3) {
        return "3";
    } 
    else if (inputKey == InputSystem::Key::NUM4) {
        return "4";
    } 
    else if (inputKey == InputSystem::Key::NUM5) {
        return "5";
    } 
    else if (inputKey == InputSystem::Key::NUM6) {
        return "6";
    } 
    else if (inputKey == InputSystem::Key::NUM7) {
        return "7";
    } 
    else if (inputKey == InputSystem::Key::NUM8) {
        return "8";
    } 
    else if (inputKey == InputSystem::Key::NUM9) {
        return "9";
    } 
    else if (inputKey == InputSystem::Key::SPACE) {
        return "Space";
    } 
    else if (inputKey == InputSystem::Key::L_SHIFT) {
        return "LShift";
    } 
    else if (inputKey == InputSystem::Key::L_CONTROL) {
        return "LControl";
    } 
    else if (inputKey == InputSystem::Key::MOUSE_LEFT) {
        return "MouseLeft";
    }
    else if (inputKey == InputSystem::Key::MOUSE_RIGHT) {
        return "MouseRight";
    }
    return "";
}

std::string Config::getGameName(){
    return mGameName;
}

bool Config::isDebugMode(){
    return mDebugMode;
}

bool Config::isFullscreen(){
    return mFullscreen;
}

uint Config::getFPS(){
    return mFPS;
}

sf::Vector2u Config::getResolution(){
    return {mResolutionWidth, mResolutionHeight};
}

float Config::getGravityForce(){
    return mGravityForce;
}

std::unordered_map<InputSystem::Action, InputSystem::Key> Config::getKeyBinds(){
    return mKeyBinds;
}

//Section names
const char* Config::videoSection = "Video";
const char* Config::inputSection = "Input";
const char* Config::systemSection = "System";

//Default Settings
const std::string Config::defaultGameName = "Game";
const bool Config::defaultDebugMode = false;
const bool Config::defaultFullscreen = false;
const uint Config::defaultFPS = 60u;
const uint Config::defaultResolutionWidth = 1920u;
const uint Config::defaultResolutionHeight = 1080u;
const float Config::defaultGravityForce = 25.f;

//Default keyBinds
const InputSystem::Key Config::defaultMoveLeft = InputSystem::Key::A;
const InputSystem::Key Config::defaultMoveRight = InputSystem::Key::D;
const InputSystem::Key Config::defaultJump = InputSystem::Key::SPACE;
const InputSystem::Key Config::defaultSprint = InputSystem::Key::L_SHIFT;
const InputSystem::Key Config::defaultCrouch = InputSystem::Key::L_CONTROL;
const InputSystem::Key Config::defaultAttack = InputSystem::Key::MOUSE_LEFT;

const char* Config::fileName = "Config.ini";

const std::string Config::name = "Config";
}
