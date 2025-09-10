#ifndef MODEL_H
#define MODEL_H

#include<string>
#include<vector>
// External Packages
#include<glad/glad.h>
#include<glfw/glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

// Project Packages
#include<project/Mesh.h>
using std::string;
using std::vector;

class Model
{
public:
    Model(std::string path);
    void Draw(Shader& shader);
private:
    // model data
    vector<Mesh> Meshes;
    string Directory;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                            string typeName);
};

#endif