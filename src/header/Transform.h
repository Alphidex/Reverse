/**
 * @file Transform.h
 * @brief Transform component for position, rotation, and scale
 * @details Encapsulates spatial transformation data and computes model matrices
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * @brief Represents spatial transformation (position, rotation, scale)
 * @details Provides methods to manipulate and compute transformation matrices
 */
class Transform
{
public:
    /**
     * @brief Default constructor - identity transform at origin
     */
    Transform();
    
    /**
     * @brief Constructs transform with position
     * @param position Initial position
     */
    Transform(const glm::vec3& position);
    
    /**
     * @brief Constructs transform with position, rotation, and scale
     * @param position Initial position
     * @param rotation Initial rotation (Euler angles in degrees)
     * @param scale Initial scale
     */
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    
    // ===== Position =====
    
    /**
     * @brief Gets the position
     * @return Position vector
     */
    const glm::vec3& getPosition() const;
    
    /**
     * @brief Sets the position
     * @param position New position
     */
    void setPosition(const glm::vec3& position);
    
    /**
     * @brief Translates by an offset
     * @param offset Translation offset
     */
    void translate(const glm::vec3& offset);
    
    // ===== Rotation =====
    
    /**
     * @brief Gets the rotation (Euler angles in degrees)
     * @return Rotation vector (pitch, yaw, roll)
     */
    const glm::vec3& getRotation() const;
    
    /**
     * @brief Sets the rotation (Euler angles in degrees)
     * @param rotation New rotation (pitch, yaw, roll)
     */
    void setRotation(const glm::vec3& rotation);
    
    /**
     * @brief Rotates around an axis
     * @param angle Rotation angle in degrees
     * @param axis Rotation axis (normalized)
     */
    void rotate(float angle, const glm::vec3& axis);
    
    /**
     * @brief Gets the rotation quaternion
     * @return Rotation as quaternion
     */
    glm::quat getRotationQuat() const;
    
    /**
     * @brief Sets rotation from quaternion
     * @param quat Rotation quaternion
     */
    void setRotationQuat(const glm::quat& quat);
    
    // ===== Scale =====
    
    /**
     * @brief Gets the scale
     * @return Scale vector
     */
    const glm::vec3& getScale() const;
    
    /**
     * @brief Sets the scale
     * @param scale New scale
     */
    void setScale(const glm::vec3& scale);
    
    /**
     * @brief Sets uniform scale (same on all axes)
     * @param scale Uniform scale value
     */
    void setScale(float scale);
    
    // ===== Matrix Computation =====
    
    /**
     * @brief Computes the model matrix from position, rotation, and scale
     * @return Model transformation matrix
     */
    glm::mat4 getModelMatrix() const;
    
    /**
     * @brief Gets the forward direction vector
     * @return Forward vector (negative Z in local space)
     */
    glm::vec3 getForward() const;
    
    /**
     * @brief Gets the right direction vector
     * @return Right vector (positive X in local space)
     */
    glm::vec3 getRight() const;
    
    /**
     * @brief Gets the up direction vector
     * @return Up vector (positive Y in local space)
     */
    glm::vec3 getUp() const;

private:
    glm::vec3 position{0.0f, 0.0f, 0.0f};      ///< Position in world space
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};      ///< Rotation (Euler angles in degrees)
    glm::vec3 scale{1.0f, 1.0f, 1.0f};         ///< Scale on each axis
    
    mutable bool matrixDirty = true;           ///< Flag to track if matrix needs recomputation
    mutable glm::mat4 cachedModelMatrix;       ///< Cached model matrix
};
