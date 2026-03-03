/**
 * @file Scene.h
 * @brief Scene manager for entity lifecycle and organization
 * @details Manages collections of entities and provides scene-level operations
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "Entity.h"

/**
 * @brief Manages a collection of entities
 * @details Provides entity creation, destruction, and scene-wide operations
 */
class Scene
{
public:
    /**
     * @brief Constructs a scene with a name
     * @param name Scene name (for debugging/identification)
     */
    Scene(const std::string& name = "Scene");
    
    /**
     * @brief Destructor - cleans up all entities
     */
    ~Scene();
    
    // ===== Entity Management =====
    
    /**
     * @brief Creates a new entity in the scene
     * @param name Entity name
     * @return Shared pointer to the created entity
     */
    std::shared_ptr<Entity> createEntity(const std::string& name = "Entity");
    
    /**
     * @brief Adds an existing entity to the scene
     * @param entity Shared pointer to entity
     */
    void addEntity(std::shared_ptr<Entity> entity);
    
    /**
     * @brief Removes an entity from the scene
     * @param entity Shared pointer to entity to remove
     * @return True if removed, false if not found
     */
    bool removeEntity(std::shared_ptr<Entity> entity);
    
    /**
     * @brief Finds an entity by name
     * @param name Entity name to search for
     * @return Shared pointer to entity, or nullptr if not found
     */
    std::shared_ptr<Entity> findEntityByName(const std::string& name) const;
    
    /**
     * @brief Gets all entities in the scene
     * @return Vector of entity pointers
     */
    const std::vector<std::shared_ptr<Entity>>& getEntities() const { return entities; }
    
    /**
     * @brief Removes all entities from the scene
     */
    void clear();
    
    /**
     * @brief Gets the number of entities in the scene
     * @return Entity count
     */
    size_t getEntityCount() const { return entities.size(); }
    
    // ===== Scene Properties =====
    
    /**
     * @brief Gets the scene name
     * @return Scene name string
     */
    const std::string& getName() const { return name; }
    
    /**
     * @brief Sets the scene name
     * @param name New name
     */
    void setName(const std::string& name) { this->name = name; }
    
    // ===== Lifecycle Methods =====
    
    /**
     * @brief Updates all active entities in the scene
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void update(float deltaTime);
    
    /**
     * @brief Called when scene is loaded/activated
     */
    virtual void onLoad();
    
    /**
     * @brief Called when scene is unloaded/deactivated
     */
    virtual void onUnload();

private:
    std::string name;                                  ///< Scene name
    std::vector<std::shared_ptr<Entity>> entities;    ///< All entities in the scene
    size_t entityCounter = 0;                          ///< Counter for unique entity IDs
};
