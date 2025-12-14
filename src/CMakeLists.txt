add_executable(Reverse)

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
    Drawable.cpp
    Program.cpp
    Interface.cpp
)

target_include_directories(Reverse 
    PRIVATE 
        ../external
        ./header)

# Find and link packages
target_link_libraries(Reverse PRIVATE assimp)
target_link_libraries(Reverse PRIVATE glfw)