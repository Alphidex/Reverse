add_executable(Reverse)

# Set output directory to project root
set_target_properties(Reverse PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_sources(Reverse PRIVATE
    main.cpp
    glad.c
    stb.cpp

    # Source files
    VBO.cpp
    VAO.cpp
    EBO.cpp
    Utilities.cpp
    Texture.cpp
    Shader.cpp
    Mesh.cpp
    Camera.cpp
    Light.cpp
    Model.cpp
    Program.cpp
    Logger.cpp
    ResourceManager.cpp
    Material.cpp
    Transform.cpp
    Entity.cpp
    Scene.cpp
    MeshRenderer.cpp
)

target_include_directories(Reverse 
    PRIVATE 
        ../external
        ./header)

# Find and link packages
target_link_libraries(Reverse PRIVATE assimp)
target_link_libraries(Reverse PRIVATE glfw)