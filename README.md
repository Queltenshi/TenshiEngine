# TenshiEngine
### Game Engine for 2D Games with EntityComponentSystem (ECS)
### Written in C++/SFML

---

## Features
- **Entity Component System** - Dynamically add or modify components to entities at runtime
- **Systems** - Process and update Entities by reading/writing their components
- **SFML Rendering** - 2D Rendering with Sprites/Textures
- **Logger** - Console Logger with Debug Log
- **GameBase** - A ready-to-use game loop and render window setup
- **Prefabs** - Ready to use entities with components

---
## Components / Systems
**A little graph to show what systems and components are in development and how they communicate with each other**

![graph](Images/Components_Systems.png)

---

## Documentation
You can find the latest API documentation here: [TenshiEngine API Docs](https://Queltenshi.github.io/TenshiEngine/)

---

## Installation:
**Requirements**:
- C++ 17+
- [SFML](https://www.sfml-dev.org/) 3.0+
- [CMake](https://cmake.org/) 3.16+

**Linux**:
```bash
git clone https://github.com/Queltenshi/TenshiEngine.git
cd TenshiEngine
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
sudo cmake --install . --prefix /usr/local

```

---

## Quick Start
**main.cpp**
``` cpp
#include <Game.h>

int main(){
    Game game;
    game.init();
    game.run();
    return 0;
}
```

**Game.cpp**
``` cpp
#include <TenshiEngine/Game/GameBase.hpp>
#include <TenshiEngine/Game/Prefabs.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Game : public te::GameBase {
public:
    Game();
    
    void init(){
        GameBase::init();

        std::ifstream file("Path/to/json");
        mPlayerTextureData = json::parse(file);
        if(!mPlayerTexture.loadFromFile("Path/to/Texture"))
            std::cout << "Texture could not be loaded" << std::endl;
        mPlayer = te::Prefabs::PlatformerPlayer(mRegistry, mPlayerTexture, mPlayerTextureData);

        if(!mGroundTexture.loadFromFile("Path/to/Texture"))
            std::cout << "Texture could not be loaded" << std::endl;
        mGround = mRegistry.createEntity(mGroundTexture);
        mRegistry.addComponent(mGround.id, te::components::Rigidbody());
        mRegistry.getComponent<te::components::Transform>(mGround.id)->position = {0.f, 800.f};
        mRegistry.getComponent<te::components::Rigidbody>(mGround.id)->isStatic = true;

}

private:
    sf::Texture mPlayerTexture;
    json mPlayerTextureData;
    te::Entity mPlayer;

    sf::Texture mGroundTexture;
    te::Entity mGround;
};
```

**texture.json**
```json
{
  "texture": "texture.png",
  "animations": {
    "hit": [
      {"x":0,"y":0,"w":222,"h":500}
    ],
    "idle": [
      {"x":0,"y":1000,"w":130,"h":500}
    ],
    "jump": [
      {"x":0,"y":500,"w":139,"h":500}
    ],
    "fall": [
      {"x":0,"y":2000,"w":139,"h":500}
    ],
    "walk": [
      {"x":0,"y":1000,"w":130,"h":500},
      {"x":0,"y":1500,"w":174,"h":477}
    ]
  }
}
```

---

## Contributing
This project is currently maintained solely by the author.  
External contributions, pull requests, or forks are welcome for personal use or experimentation,  
but they will **not be merged** into the main repository at this time.

---

## Changelog
See the full changelog [here](CHANGELOG.md).

---

## License
This project is licensed under the GNU GPL v3 

It uses:
- [SFML](https://www.sfml-dev.org/) - licensed under the zlib/libpng license
- [nlohmann/json](https://github.com/nlohmann/json) – licensed under the MIT license
