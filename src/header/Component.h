/**
 * @file Component.h
 * @brief Base class for entity components
 * @details Provides interface for component-based entity system
 */

#pragma once

#include <memory>
#include <string>

// Forward declarations
class Entity;

/**
 * @brief Base class for all entity components
 * @details Components add functionality to entities (rendering, physics, scripts, etc.)
 */
class Component
{
public:
    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~Component() = default;
    
    /**
     * @brief Called when component is added to an entity
     * @param owner Pointer to the owning entity
     */
    virtual void onAttach(Entity* owner) { this->owner = owner; }
    
    /**
     * @brief Called when component is removed from an entity
     */
    virtual void onDetach() { owner = nullptr; }
    
    /**
     * @brief Called every frame to update component logic
     * @param deltaTime Time elapsed since last frame in seconds
     */
    virtual void update(float deltaTime) {}
    
    /**
     * @brief Gets the owning entity
     * @return Pointer to owner, or nullptr if not attached
     */
    Entity* getOwner() const { return owner; }
    
    /**
     * @brief Checks if component is enabled
     * @return True if enabled, false otherwise
     */
    bool isEnabled() const { return enabled; }
    
    /**
     * @brief Sets the enabled state of this component
     * @param enabled New enabled state
     */
    void setEnabled(bool enabled) { this->enabled = enabled; }
    
    /**
     * @brief Gets the component type name (for debugging/reflection)
     * @return Type name string
     */
    virtual std::string getTypeName() const { return "Component"; }

protected:
    Entity* owner = nullptr;  ///< Owning entity
    bool enabled = true;      ///< Whether component is active
};
