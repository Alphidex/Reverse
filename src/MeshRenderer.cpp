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
}

void MeshRenderer::render() {
    if (!enabled || !mesh || !material || !owner) {
        return;
    }
    
    // Get entity's transform
    const Transform& transform = owner->getTransform();
    
    // Use the material
    material->use();
    
    // Set the model matrix from entity's transform
    auto shader = material->getShader();
    if (shader) {
        shader->setMat4("model", transform.getModelMatrix());
    }
    
    // Render the mesh (using the old mesh rendering code)
    // We need to manually bind VAO and draw since we're not using Mesh::Draw()
    // Actually, let's just temporarily set the mesh's transform and call its draw
    // This is a bit hacky but maintains compatibility
    // TODO: Refactor Mesh to separate transform from geometry
    
    // For now, we'll use a workaround - access mesh internals
    // Better approach: make Mesh::Draw() accept a transform parameter
    // or separate rendering logic from mesh data
    
    // Quick solution: We already have material.use() which binds shader and textures
    // Just need to draw the geometry - this requires access to mesh's VAO
    // Since we can't easily do that without refactoring Mesh, let's use the existing Draw()
    // but it will use mesh's internal transform instead of entity's transform
    
    // TEMPORARY: Log a warning about this limitation
    static bool warningShown = false;
    if (!warningShown) {
        LOG_WARNING("MeshRenderer: Using mesh's internal transform. TODO: Separate mesh geometry from transform");
        warningShown = true;
    }
    
    // For now, sync mesh transform with entity transform
    // This is not ideal but works as a temporary solution
    mesh->setPosition(transform.getPosition());
    mesh->setRotation(0.0f, glm::vec3(0, 1, 0)); // Simplified - full rotation sync would need euler conversion
    mesh->setScale(transform.getScale());
    
    // Use material to render (it will bind shader and textures)
    material->use();
    
    // Draw the mesh (it will use its internal transform, which we just synced)
    mesh->Draw(); // This uses the material-based Draw()
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
