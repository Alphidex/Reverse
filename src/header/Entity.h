/**
 * @file Entity.h
 * @brief Entity/GameObject class for component-based architecture
 * @details Manages components and provides basic entity functionality
 */

#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include "Transform.h"
#include "Component.h"

/**
 * @brief Represents a game object/entity in the scene
 * @details Entity-Component pattern - entities are containers for components
 */
class Entity
{
public:
    /**
     * @brief Constructs an entity with a name
     * @param name Entity name (for debugging/identification)
     */
    Entity(const std::string& name = "Entity");
    
    /**
     * @brief Virtual destructor for cleanup
     */
    virtual ~Entity();
    
    // ===== Component Management =====
    
    /**
     * @brief Adds a component to this entity
     * @tparam T Component type (must derive from Component)
     * @tparam Args Constructor argument types
     * @param args Arguments to forward to component constructor
     * @return Shared pointer to the added component
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        const std::type_index type(typeid(T));
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->onAttach(this);

        auto existing = componentMap.find(type);
        if (existing != componentMap.end() && existing->second) {
            existing->second->onDetach();
        }

        componentMap[type] = component;
        
        return component;
    }
    
    /**
     * @brief Gets a component of the specified type
     * @tparam T Component type
     * @return Shared pointer to component, or nullptr if not found
     */
    template<typename T>
    std::shared_ptr<T> getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        auto it = componentMap.find(std::type_index(typeid(T)));
        if (it != componentMap.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }
    
    /**
     * @brief Checks if entity has a component of the specified type
     * @tparam T Component type
     * @return True if component exists, false otherwise
     */
    template<typename T>
    bool hasComponent() const {
        return componentMap.find(std::type_index(typeid(T))) != componentMap.end();
    }
    
    /**
     * @brief Removes a component of the specified type
     * @tparam T Component type
     * @return True if removed, false if not found
     */
    template<typename T>
    bool removeComponent() {
        auto it = componentMap.find(std::type_index(typeid(T)));
        if (it == componentMap.end()) {
            return false;
        }

        if (it->second) {
            it->second->onDetach();
        }
        componentMap.erase(it);
        return true;
    }
    
    /**
     * @brief Gets all components
    * @return Map of component type to component pointer
     */
    const std::unordered_map<std::type_index, std::shared_ptr<Component>>& getComponents() const { return componentMap; }
    
    // ===== Transform Access =====
    
    /**
     * @brief Gets the entity's transform
     * @return Reference to transform
     */
    Transform& getTransform() { return transform; }
    const Transform& getTransform() const { return transform; }
    
    // ===== Entity Properties =====
    
    /**
     * @brief Gets the entity name
     * @return Entity name string
     */
    const std::string& getName() const { return name; }
    
    /**
     * @brief Sets the entity name
     * @param name New name
     */
    void setName(const std::string& name) { this->name = name; }
    
    /**
     * @brief Gets the active state
     * @return True if active, false if inactive
     */
    bool isActive() const { return active; }
    
    /**
     * @brief Sets the active state
     * @param active New active state
     */
    void setActive(bool active) { this->active = active; }
    
    // ===== Lifecycle Methods =====
    
    /**
     * @brief Updates all components
     * @param deltaTime Time elapsed since last frame in seconds
     */
    virtual void update(float deltaTime);
    
    /**
     * @brief Called when entity is destroyed
     */
    virtual void onDestroy();

private:
    std::string name;                                                    ///< Entity name
    bool active = true;                                                  ///< Active state
    Transform transform;                                                 ///< Entity transform
    std::unordered_map<std::type_index, std::shared_ptr<Component>> componentMap; ///< Fast component lookup
};
