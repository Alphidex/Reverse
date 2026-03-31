/**
 * @file MeshRenderer.cpp
 * @brief Implementation of the MeshRenderer component
 */

#include "header/MeshRenderer.h"
#include "header/Entity.h"
#include "header/Logger.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
    : mesh(mesh), material(material) {
    
    if (!mesh) {
        LOG_WARNING("MeshRenderer created with null mesh");
    }
    if (!material) {
        LOG_WARNING("MeshRenderer created with null material");
    }
    
    if (this->mesh && this->material) {
        this->mesh->setMaterial(this->material);
    }
}

void MeshRenderer::render() {
    if (!enabled) {
        return;
    }

    if (!owner) {
        LOG_ERROR("MeshRenderer::render called without owner entity");
        return;
    }

    if (!mesh) {
        LOG_ERROR("MeshRenderer::render called with null mesh");
        return;
    }

    if (!material) {
        LOG_ERROR("MeshRenderer::render called with null material");
        return;
    }
    
    auto shader = material->getShader();
    if (!shader) {
        LOG_ERROR("MeshRenderer::render encountered material with null shader");
        return;
    }

    mesh->setMaterial(material);
    mesh->draw(owner->getTransform().getModelMatrix());
}

void MeshRenderer::setMesh(std::shared_ptr<Mesh> newMesh) {
    mesh = newMesh;
}

void MeshRenderer::setMaterial(std::shared_ptr<Material> newMaterial) {
    material = newMaterial;
    
    // Sync the material with the mesh
    if (mesh && material) {
        mesh->setMaterial(material);
    }
}
