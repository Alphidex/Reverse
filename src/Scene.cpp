/**
 * @file Scene.cpp
 * @brief Implementation of the Scene class
 */

#include "header/Scene.h"
#include "header/Logger.h"
#include <algorithm>

Scene::Scene(const std::string& name) : name(name) {
    LOG_INFO("Scene created: " + name);
}

Scene::~Scene() {
    clear();
}

// ===== Entity Management =====

std::shared_ptr<Entity> Scene::createEntity(const std::string& name) {
    std::string entityName = name;
    if (entityName.empty()) {
        entityName = "Entity_" + std::to_string(entityCounter++);
    }
    
    auto entity = std::make_shared<Entity>(entityName);
    entities.push_back(entity);
    
    LOG_DEBUG("Entity created in scene '" + this->name + "': " + entityName);
    return entity;
}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
    if (entity) {
        entities.push_back(entity);
        LOG_DEBUG("Entity added to scene '" + name + "': " + entity->getName());
    }
}

bool Scene::removeEntity(std::shared_ptr<Entity> entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        LOG_DEBUG("Entity removed from scene '" + name + "': " + (*it)->getName());
        entities.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Entity> Scene::findEntityByName(const std::string& name) const {
    for (const auto& entity : entities) {
        if (entity->getName() == name) {
            return entity;
        }
    }
    return nullptr;
}

void Scene::clear() {
    LOG_INFO("Clearing scene: " + name + " (" + std::to_string(entities.size()) + " entities)");
    entities.clear();
    entityCounter = 0;
}

// ===== Lifecycle Methods =====

void Scene::update(float deltaTime) {
    // Update all active entities
    for (auto& entity : entities) {
        if (entity && entity->isActive()) {
            entity->update(deltaTime);
        }
    }
}

void Scene::onLoad() {
    LOG_INFO("Scene loaded: " + name);
}

void Scene::onUnload() {
    LOG_INFO("Scene unloaded: " + name);
}
