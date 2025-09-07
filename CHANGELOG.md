# Changelog

---

## [0.4.0] - 2025-09-07
### Added
- **Managers**
    - **ResourceManager**: Manages/loads resources: textures and json
    - **TileMapManager**: manages/loads tilesets and levels from files
    - **CameraManager**: Manages cameras, sets the active camera
    - **BackgroundManager**: Manages background image and its movement
- **Camera**: Stores the current view of an attached entity    

### Fixed
- Incorrect collision calculations on corners

### Changed
- **Systems**
    - **RenderSystem**: Now uses active camera for rendering
- **Logger**: Now has textcolor for different loglevels

## [0.3.1] - 2025-08-28
### Added
- **Components**
    - **Collider**: Stores size for collision

### Fixed
- Incorrect scaling
- Incorrect collision detection for jumping entities

### Changed
- **Components**
    - **Transform**: No longer stores size for collision

## [0.3.0] - 2025-08-27
### Added
- **Components**
    - **State**: Stores current state and direction in which the entity is facing
    - **Animation**: Stores data and time used for animations
- **Systems**
    - **AnimationSystem**: Updates animations
- **Prefabs**
    - **PlatformerPlayer**: Creates player for platformer games
- **Json**: Json support via nlohmann/json header

### Fixed
- DeltaTime calculation for systems 

### Changed
- **Registry**: Now has createEntity with optional animations
- **Systems**
    - **RenderSystem**: Now has debug rendering for drawing colliders
    - **MovementSystem**: now updates State

## [0.2.0] - 2025-08-21
### Added
- **Components**
    - **HorizontalMovement**: Stores horizontal movement values
    - **Jump**: Stores jump strength value
    - **Grounded**: checks if the entity is grounded
    - **Velocity**: Stores current velocity
    - **Rigidbody**: Stores mass 
- **Systems**
    - **MovementSystem**: Updates velocity based on input
    - **PhysicsSystem**: Updates velocity and position based on physical calculations
- **Utils**
    - **boolToString**: Converts boolean to string

### Changed
- **GameBase**: Now has fixed framerate for rendering and time for updating systems
- **Registry**: Now has separate method for updating RenderSystem
- **Components**: Now have methods for returning data and names
- **Systems**: Now have names
- **Logger**: Now has macro for logging changed components

## [0.1.0] - 2025-08-15
### Added
- **Core Structure**
    - **GameBase**: Runs game loop and window for rendering
    - **Registry**: Used for managing systems and components
    - **Entity**: Stores entity id
- **Components** 
    - **Transform**: Stores size and position
    - **Sprite**: Stores texture and sprite
    - **PlayerInput**: stores which player actions are pressed
- **Systems**
    - **RenderSystem**: Renders on the window
    - **InputSystem**: Reads input from the system
- **Logger**: Debug log
