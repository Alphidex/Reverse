/**
 * @file Entity.cpp
 * @brief Implementation of the Entity class
 */

#include "header/Entity.h"
#include "header/Logger.h"

Entity::Entity(const std::string& name) : name(name) {
    LOG_DEBUG("Entity created: " + name);
}

Entity::~Entity() {
    onDestroy();
}

void Entity::update(float deltaTime) {
    if (!active) {
        return;
    }
    
    // Update all enabled components
    for (auto& component : components) {
        if (component && component->isEnabled()) {
            component->update(deltaTime);
        }
    }
}

void Entity::onDestroy() {
    LOG_DEBUG("Entity destroyed: " + name);
    
    // Detach all components
    for (auto& component : components) {
        if (component) {
            component->onDetach();
        }
    }
    
    components.clear();
    componentMap.clear();
}
