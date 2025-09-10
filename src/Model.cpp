#include<project/Model.h>

void Model::Draw(Shader &shader)
{
    for(unsigned int i = 0; i < Meshes.size(); i++)
        Meshes[i].Draw(shader, "path");
} 

Model::Model(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    Directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::loadModel(string path) {};
void Model::processNode(aiNode *node, const aiScene *scene) {};
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {};
vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                        string typeName) 
{
    vector<Texture> gap {};
    return gap;
};