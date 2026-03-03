# Shader Uniform Manager & Material System

## Overview

The enhanced Shader class now includes:
- **Automatic uniform location caching** - No more repeated `glGetUniformLocation` calls
- **Type-safe uniform setters** - Clean, easy-to-use API for setting uniforms
- **Material class** - Bundles shaders, textures, and material properties

## Features

### 1. Type-Safe Uniform Setters

Instead of the old way:
```cpp
// OLD: Manual uniform location lookup and setting
glUniform1i(glGetUniformLocation(shader.getID(), "myTexture"), 0);
glUniform3fv(glGetUniformLocation(shader.getID(), "lightPos"), 1, glm::value_ptr(position));
glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
```

Use the new way:
```cpp
// NEW: Clean, type-safe API
shader->setInt("myTexture", 0);
shader->setVec3("lightPos", position);
shader->setMat4("model", modelMatrix);
```

### 2. Uniform Location Caching

The Shader class automatically caches uniform locations internally. The first call to any setter looks up the location, subsequent calls use the cached value. This significantly improves performance when setting uniforms multiple times per frame.

### 3. Available Uniform Setters

```cpp
// Integer
shader->setInt("textureSampler", 0);

// Float
shader->setFloat("time", 1.5f);

// Vec2
shader->setVec2("resolution", glm::vec2(800, 600));
shader->setVec2("resolution", 800.0f, 600.0f);

// Vec3
shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

// Vec4
shader->setVec4("color", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));
shader->setVec4("color", 1.0f, 0.5f, 0.2f, 1.0f);

// Mat3
shader->setMat3("normalMatrix", normalMatrix);

// Mat4
shader->setMat4("model", modelMatrix);
shader->setMat4("view", viewMatrix);
shader->setMat4("projection", projectionMatrix);
```

## Material System

### Creating a Material

```cpp
#include "header/Material.h"

// Create material with a shader
auto myMaterial = std::make_shared<Material>(myShader);

// Add textures
myMaterial->addTexture(diffuseTexture);
myMaterial->addTexture(specularTexture);

// Set material properties
myMaterial->setDiffuseColor(glm::vec3(1.0f, 0.8f, 0.6f));
myMaterial->setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));
myMaterial->setShininess(64.0f);
myMaterial->setAlpha(1.0f);
```

### Using a Material

```cpp
// Activate the material (binds shader, textures, and sets properties)
myMaterial->use();

// Now draw your geometry
mesh->Draw();
```

### Material Properties

Materials support common PBR-like properties:

- **Diffuse Color** - Base color of the material
- **Specular Color** - Color of specular highlights
- **Ambient Color** - Ambient lighting contribution
- **Shininess** - Specular exponent (1-128)
- **Alpha** - Opacity value (0.0 = transparent, 1.0 = opaque)

### Expected Shader Uniforms

When using the Material system, your fragment shader should expect these uniforms:

```glsl
struct Material {
    sampler2D diffuse;    // Diffuse texture
    sampler2D specular;   // Specular texture (optional)
    sampler2D normal;     // Normal map (optional)
    
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;
    float shininess;
    float alpha;
};

uniform Material material;
```

## Benefits

1. **Performance**: Uniform locations are cached, eliminating redundant lookups
2. **Type Safety**: Compile-time checking of uniform types
3. **Cleaner Code**: Less boilerplate, more readable
4. **Encapsulation**: Material bundles related rendering state
5. **Flexibility**: Easy to swap materials on the fly

## Migration Guide

### Old Code
```cpp
shader->Enable();
glUniform3fv(glGetUniformLocation(shader->getID(), "dirLight.direction"), 1, glm::value_ptr(dir));
glUniform3fv(glGetUniformLocation(shader->getID(), "dirLight.ambient"), 1, glm::value_ptr(ambient));
glUniform3fv(glGetUniformLocation(shader->getID(), "dirLight.diffuse"), 1, glm::value_ptr(diffuse));
```

### New Code
```cpp
shader->Enable();
shader->setVec3("dirLight.direction", dir);
shader->setVec3("dirLight.ambient", ambient);
shader->setVec3("dirLight.diffuse", diffuse);
```

## Next Steps

Consider updating your existing code progressively:
1. Replace manual `glGetUniformLocation` + `glUniform*` calls with the new setters
2. Create Material instances for different object types
3. Refactor mesh/model rendering to use Materials

## Notes

- Uniform location caching is thread-safe for read operations
- Missing uniforms will log a warning but won't crash
- The Material class is designed to work with the existing ResourceManager
