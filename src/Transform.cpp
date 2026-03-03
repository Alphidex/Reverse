/**
 * @file Transform.cpp
 * @brief Implementation of the Transform component
 */

#include "header/Transform.h"
#include <glm/gtx/euler_angles.hpp>

Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}

Transform::Transform(const glm::vec3& position) 
    : position(position), rotation(0.0f), scale(1.0f) {}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : position(position), rotation(rotation), scale(scale) {}

// ===== Position =====

const glm::vec3& Transform::getPosition() const {
    return position;
}

void Transform::setPosition(const glm::vec3& pos) {
    position = pos;
    matrixDirty = true;
}

void Transform::translate(const glm::vec3& offset) {
    position += offset;
    matrixDirty = true;
}

// ===== Rotation =====

const glm::vec3& Transform::getRotation() const {
    return rotation;
}

void Transform::setRotation(const glm::vec3& rot) {
    rotation = rot;
    matrixDirty = true;
}

void Transform::rotate(float angle, const glm::vec3& axis) {
    // Convert current Euler angles to quaternion
    glm::quat currentQuat = getRotationQuat();
    
    // Create rotation quaternion for the new rotation
    glm::quat rotQuat = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    
    // Combine rotations
    glm::quat newQuat = rotQuat * currentQuat;
    
    // Convert back to Euler angles
    setRotationQuat(newQuat);
}

glm::quat Transform::getRotationQuat() const {
    return glm::quat(glm::radians(rotation));
}

void Transform::setRotationQuat(const glm::quat& quat) {
    // Convert quaternion to Euler angles (in radians, then to degrees)
    glm::vec3 eulerRad = glm::eulerAngles(quat);
    rotation = glm::degrees(eulerRad);
    matrixDirty = true;
}

// ===== Scale =====

const glm::vec3& Transform::getScale() const {
    return scale;
}

void Transform::setScale(const glm::vec3& scaleVec) {
    scale = scaleVec;
    matrixDirty = true;
}

void Transform::setScale(float uniformScale) {
    scale = glm::vec3(uniformScale);
    matrixDirty = true;
}

// ===== Matrix Computation =====

glm::mat4 Transform::getModelMatrix() const {
    if (matrixDirty) {
        // Compute model matrix: Translation * Rotation * Scale
        cachedModelMatrix = glm::mat4(1.0f);
        cachedModelMatrix = glm::translate(cachedModelMatrix, position);
        
        // Apply rotations (Euler angles: pitch, yaw, roll)
        cachedModelMatrix = glm::rotate(cachedModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
        cachedModelMatrix = glm::rotate(cachedModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
        cachedModelMatrix = glm::rotate(cachedModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll
        
        cachedModelMatrix = glm::scale(cachedModelMatrix, scale);
        
        matrixDirty = false;
    }
    return cachedModelMatrix;
}

glm::vec3 Transform::getForward() const {
    glm::quat quat = getRotationQuat();
    return glm::normalize(quat * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Transform::getRight() const {
    glm::quat quat = getRotationQuat();
    return glm::normalize(quat * glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Transform::getUp() const {
    glm::quat quat = getRotationQuat();
    return glm::normalize(quat * glm::vec3(0.0f, 1.0f, 0.0f));
}
