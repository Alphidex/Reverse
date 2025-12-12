add_executable(Reverse)

target_sources(Reverse PRIVATE
    main.cpp
    glad.c
    stb.cpp
    Shader.cpp
    Optional.cpp
    EBO.cpp
    VAO.cpp
    VBO.cpp
    Texture.cpp
    Mesh.cpp
    Camera.cpp
    Light.cpp
    Model.cpp
    Program.cpp
    Interface.cpp
    Drawable.cpp
)

target_include_directories(Reverse 
    PRIVATE 
        ../external
        ./header)

# Find and link packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)