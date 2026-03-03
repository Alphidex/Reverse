# Entity/Component System Usage Guide

## Overview

The Entity/Component System provides a modern, flexible architecture for managing game objects. It replaces manual object management with a structured, component-based approach.

## Architecture

### Core Classes

1. **Transform** - Spatial transformation component (position, rotation, scale)
2. **Component** - Base class for all components
3. **Entity** - GameObject that holds components
4. **Scene** - Container and manager for all entities
5. **MeshRenderer** - Component for rendering meshes on entities

## Usage Examples

### Creating a Scene

```cpp
#include "header/Scene.h"

// Create a scene
Scene mainScene("GameScene");
```

### Creating Entities

```cpp
// Create an entity
auto player = mainScene.createEntity("Player");

// Set transform
player->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
player->getTransform().setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
player->getTransform().setScale(glm::vec3(1.5f, 1.5f, 1.5f));
```

### Adding Components

```cpp
// Create materials and meshes first
auto material = std::make_shared<Material>(shader);
material->addTexture(texture);

auto mesh = std::make_shared<Mesh>(vertices, indices, material);

// Add MeshRenderer component
auto renderer = player->addComponent<MeshRenderer>(mesh, material);

// Components can be enabled/disabled
renderer->setEnabled(false);  // Stop rendering
renderer->setEnabled(true);   // Resume rendering
```

### Getting Components

```cpp
// Get a component by type
auto renderer = entity->getComponent<MeshRenderer>();
if (renderer) {
    renderer->setMaterial(newMaterial);
}

// Check if entity has a component
if (entity->hasComponent<MeshRenderer>()) {
    // Do something
}
```

### Transform System

```cpp
Transform& transform = entity->getTransform();

// Position
transform.setPosition(glm::vec3(10.0f, 5.0f, 0.0f));
transform.translate(glm::vec3(1.0f, 0.0f, 0.0f)); // Move relative

// Rotation (Euler angles in degrees)
transform.setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
transform.rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around axis

// Scale
transform.setScale(glm::vec3(2.0f, 2.0f, 2.0f));
transform.setScale(2.0f); // Uniform scale

// Get direction vectors
glm::vec3 forward = transform.getForward();
glm::vec3 right = transform.getRight();
glm::vec3 up = transform.getUp();

// Get model matrix
glm::mat4 modelMatrix = transform.getModelMatrix();
```

### Scene Management

```cpp
Scene scene("MainScene");

// Create multiple entities
auto cube1 = scene.createEntity("Cube1");
auto cube2 = scene.createEntity("Cube2");
auto plane = scene.createEntity("Ground");

// Find entity by name
auto foundEntity = scene.findEntityByName("Cube1");

// Get all entities
for (const auto& entity : scene.getEntities()) {
    // Process each entity
}

// Remove entity
scene.removeEntity(cube2);

// Clear all entities
scene.clear();

// Get entity count
size_t count = scene.getEntityCount();
```

### Update Loop

```cpp
while (running) {
    float deltaTime = calculateDeltaTime();
    
    // Update all entities and their components
    scene.update(deltaTime);
    
    // Render all visible entities
    for (const auto& entity : scene.getEntities()) {
        if (entity->isActive()) {
            auto renderer = entity->getComponent<MeshRenderer>();
            if (renderer && renderer->isEnabled()) {
                renderer->render();
            }
        }
    }
}
```

### Entity State Management

```cpp
// Enable/disable entire entity
entity->setActive(false);  // Entity and all components inactive
entity->setActive(true);   // Re-enable

// Check state
bool active = entity->isActive();

// Rename entity
entity->setName("NewName");
std::string name = entity->getName();
```

## Creating Custom Components

You can extend the system by creating custom components:

```cpp
// CustomComponent.h
#pragma once
#include "Component.h"

class CustomComponent : public Component {
public:
    CustomComponent(/* params */) {
        // Initialize
    }
    
    void update(float deltaTime) override {
        // Update logic runs every frame
    }
    
    void onAttach(Entity* owner) override {
        Component::onAttach(owner);
        // Called when added to entity
    }
    
    void onDetach() override {
        // Called when removed from entity
        Component::onDetach();
    }
    
    std::string getTypeName() const override {
        return "CustomComponent";
    }
    
private:
    // Component data
};

// Usage:
auto customComp = entity->addComponent<CustomComponent>(/* params */);
```

## Best Practices

1. **Use Scenes for Organization**
   - Separate scenes for different game states (menu, gameplay, pause)
   - Load/unload scenes as needed

2. **Component Composition**
   - Keep components focused on single responsibilities
   - Combine multiple components for complex behaviors

3. **Transform Access**
   - Cache transform references if accessing frequently
   - Use getModelMatrix() sparingly (it's cached internally)

4. **Entity Naming**
   - Use descriptive names for easier debugging
   - Include type or role in the name: "Enemy_Goblin_01"

5. **Component Communication**
   - Components can access their owner: `getOwner()`
   - Get sibling components: `owner->getComponent<OtherComponent>()`

## Example: Complete Object Setup

```cpp
// Create entity with all components
auto enemy = scene.createEntity("Enemy_Orc");

// Setup transform
enemy->getTransform().setPosition(glm::vec3(10.0f, 0.0f, 5.0f));
enemy->getTransform().setRotation(glm::vec3(0.0f, 180.0f, 0.0f));

// Setup rendering
auto orcMesh = std::make_shared<Mesh>(vertices, indices, orcMaterial);
auto renderer = enemy->addComponent<MeshRenderer>(orcMesh, orcMaterial);

// Add custom components (when you create them)
// auto ai = enemy->addComponent<AIComponent>(aiConfig);
// auto health = enemy->addComponent<HealthComponent>(100.0f);
// auto physics = enemy->addComponent<PhysicsComponent>();
```

## Migration from Old System

### Before (Manual Management)
```cpp
Mesh cube(vertices, indices, textures);
cube.setPosition(glm::vec3(2.0f, 0.0f, 0.0f));
cube.Draw(*shader, "model");
```

### After (Entity System)
```cpp
auto cubeEntity = scene.createEntity("Cube");
cubeEntity->getTransform().setPosition(glm::vec3(2.0f, 0.0f, 0.0f));

auto mesh = std::make_shared<Mesh>(vertices, indices, material);
auto renderer = cubeEntity->addComponent<MeshRenderer>(mesh, material);

// In render loop
renderer->render();
```

## Benefits

1. **Organization** - Logical grouping of objects in scenes
2. **Flexibility** - Easy to add/remove functionality via components
3. **Scalability** - Handles hundreds of entities efficiently
4. **Maintainability** - Clean separation of concerns
5. **Extensibility** - Create custom components without modifying core code

## Current Limitations & Future Improvements

### Current State
- Transform is separate from Mesh (requires syncing in MeshRenderer)
- No built-in parent-child hierarchy (scene graph)
- Components are updated but don't have render callbacks

### Planned Improvements
1. Integrate Transform directly into Mesh rendering
2. Add parent-child entity relationships (scene graph)
3. Add more components (Physics, Audio, Scripts, etc.)
4. Component lifecycle callbacks (start, enable, disable)
5. Scene serialization (save/load)
6. Entity prefabs/templates

## Summary

The Entity/Component System provides:
- ✅ Scene management for organizing entities
- ✅ Transform component for spatial data
- ✅ Component-based architecture for extensibility
- ✅ MeshRenderer for easy mesh rendering
- ✅ Type-safe component access
- ✅ Flexible entity lifecycle management

This foundation makes it easy to build complex game objects from simple, reusable components!
