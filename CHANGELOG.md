# Changelog

---

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
