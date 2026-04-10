/**
 * @file Config.h
 * @brief Centralized configuration constants for the Reverse Engine
 * @details Contains all magic numbers, settings, and tunable parameters organized by subsystem
 */

#pragma once

namespace Config {

    /**
     * @brief Window and display configuration
     */
    namespace Window {
        constexpr int DEFAULT_WIDTH = 800;
        constexpr int DEFAULT_HEIGHT = 800;
        constexpr int OPENGL_MAJOR_VERSION = 4;
        constexpr int OPENGL_MINOR_VERSION = 6;
        constexpr bool ENABLE_VSYNC = true;
        constexpr const char* WINDOW_TITLE = "Reverse";
    }

    /**
     * @brief Camera system configuration
     */
    namespace Camera {
        // Movement speeds
        constexpr float BASE_MOVEMENT_SPEED = 30.0f;
        constexpr float SPRINT_MOVEMENT_SPEED = 400.0f;
        
        // Mouse settings
        constexpr float MOUSE_SENSITIVITY = 5.0f;
        
        // Field of view
        constexpr float DEFAULT_FOV = 45.0f;
        constexpr float MIN_FOV = 1.0f;
        constexpr float MAX_FOV = 45.0f;
        constexpr float SCROLL_FOV_STEP = 2.0f;
        
        // View frustum
        constexpr float DEFAULT_NEAR_PLANE = 0.1f;
        constexpr float DEFAULT_FAR_PLANE = 1000.0f;
        constexpr float DEFAULT_ASPECT_RATIO = 4.0f / 3.0f;
        
        // Rotation limits
        constexpr float MAX_PITCH = 89.0f;
        constexpr float MIN_PITCH = -89.0f;
        constexpr float DEFAULT_YAW = -90.0f;
        constexpr float DEFAULT_PITCH = 0.0f;
    }

    /**
     * @brief Rendering configuration
     */
    namespace Rendering {
        constexpr float NEAR_PLANE = 0.1f;
        constexpr float FAR_PLANE = 6000.0f;
        
        // Clear color (background)
        constexpr float CLEAR_COLOR_R = 0.2f;
        constexpr float CLEAR_COLOR_G = 0.3f;
        constexpr float CLEAR_COLOR_B = 0.3f;
        constexpr float CLEAR_COLOR_A = 1.0f;
    }

    /**
     * @brief Shader file paths
     */
    namespace Shaders {
        constexpr const char* DEFAULT_VERTEX = "shader/default.vert";
        constexpr const char* DEFAULT_FRAGMENT = "shader/default.frag";
        constexpr const char* INTERFACE_VERTEX = "shader/interface.vert";
        constexpr const char* INTERFACE_FRAGMENT = "shader/interface.frag";
        constexpr const char* LIGHT_VERTEX = "shader/light.vert";
        constexpr const char* LIGHT_FRAGMENT = "shader/light.frag";
    }

    /**
     * @brief Resource paths
     */
    namespace Resources {
        constexpr const char* TEXTURE_DIR = "resource/textures/";
        constexpr const char* MODEL_DIR = "resource/models/";
        constexpr const char* SHADER_DIR = "shader/";
    }

    /**
     * @brief Texture settings
     */
    namespace Textures {
        constexpr bool FLIP_VERTICALLY_ON_LOAD = true;
    }

    /**
     * @brief Debug settings
     */
    namespace Debug {
        constexpr bool PRINT_CAMERA_POSITION = false;
        constexpr bool PRINT_FPS = true;
        constexpr bool ENABLE_WIREFRAME = false;
    }

    /**
     * @brief Logging system configuration
     */
    namespace Logging {
        constexpr bool ENABLE_FILE_LOGGING = false;
        constexpr const char* LOG_FILE_PATH = "reverse.log";
        constexpr bool USE_COLORS = true;
        
        // Default log level (0=DEBUG, 1=INFO, 2=WARNING, 3=ERROR)
        // Set to INFO for normal operation, DEBUG for development
        constexpr int DEFAULT_LOG_LEVEL = 0; // INFO
    }

} // namespace Config
