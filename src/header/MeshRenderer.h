/**
 * @file MeshRenderer.h
 * @brief Component for rendering meshes on entities
 * @details Bridges the Entity-Component system with the existing Mesh rendering
 */

#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include <memory>

/**
 * @brief Component that renders a mesh using a material
 * @details Automatically uses the entity's transform for rendering
 */
class MeshRenderer : public Component
{
public:
    /**
     * @brief Constructs a mesh renderer with a mesh and material
     * @param mesh Shared pointer to the mesh to render
     * @param material Shared pointer to the material to use
     */
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    
    /**
     * @brief Renders the mesh with the entity's transform
     * @details Should be called during the render phase, not update
     */
    void render();
    
    /**
     * @brief Sets the mesh to render
     * @param mesh Shared pointer to mesh
     */
    void setMesh(std::shared_ptr<Mesh> mesh);
    
    /**
     * @brief Gets the mesh
     * @return Shared pointer to mesh
     */
    std::shared_ptr<Mesh> getMesh() const { return mesh; }
    
    /**
     * @brief Sets the material to use for rendering
     * @param material Shared pointer to material
     */
    void setMaterial(std::shared_ptr<Material> material);
    
    /**
     * @brief Gets the material
     * @return Shared pointer to material
     */
    std::shared_ptr<Material> getMaterial() const { return material; }
    
    /**
     * @brief Gets the component type name
     * @return "MeshRenderer"
     */
    std::string getTypeName() const override { return "MeshRenderer"; }

private:
    std::shared_ptr<Mesh> mesh;         ///< Mesh to render
    std::shared_ptr<Material> material; ///< Material for rendering
};
