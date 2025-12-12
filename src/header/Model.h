#pragma once

#include<map>
#include<string>
#include<vector>
// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

// Project Packages
#include "Mesh.h"
using std::string, std::vector, std::map;

class Model
{
public:
    Model(string path);
    void Draw(Shader& shader);

private:
    vector<Mesh> meshes;
    string directory;
    map<string, Texture> loadedTextures;
    
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};