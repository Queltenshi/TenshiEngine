# Changelog

---

## [0.2.0] - 2025-08-21
### Added
- ***New Components*** 
    - **HorizontalMovement**: Stores horizontal movement values
    - **Jump**: Stores jump strength value
    - **Grounded**: checks if the entity is grounded
    - **Velocity**: Stores current velocity
    - **Rigidbody**: Stores mass 
- ***New Systems***
    - **MovementSystem**: Reads HorizontalMovement, Jump, Grounded, Velocity and updates Velocity 
    - **PhysicsSystem**: Reads Velocity, Rigidbody, calculates gravity, detects collision, corrects position and updates Velocity, Transform
- ***New Util***
    - **boolToString**: Converts boolean to string

### Changed
- **Components**: Now have toString method for returning data and static name
- **Systems**: Now have static name
- **Logger**: Now has macro for logging changed components
- **Registry**: Now has separate function for updating RenderSystem
- **GameBase**: Now has fixed framerate for rendering and time for updating systems

## [0.1.0] - 2025-08-15
### Added
- Core structure: GameBase, Registry, Entity
- Initial Components: TransformComponent, SpriteComponent, PlayerInputComponent
- Initial Systems: RenderSystem, InputSystem
- Logger system: Debug Log
