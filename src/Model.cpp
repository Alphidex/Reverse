#include<project/Model.h>

void Model::Draw(Shader &shader)
{
    for(unsigned int i = 0; i < Meshes.size(); i++)
        Meshes[i].Draw(shader, "model");
} 

Model::Model(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_SplitLargeMeshes | aiProcess_OptimizeMeshes);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    Directory = path.substr(0, path.find_last_of('/')) + "/";

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) 
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        Meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
};
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) 
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        // Positions
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;
        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector; 
        // TexCoords
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoord = vec;
        }
        else
            vertex.TexCoord = glm::vec2(0.0f, 0.0f);  

        vertices.push_back(vertex);
    }
    // Indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    } 
    // Material
    if(mesh->mMaterialIndex >= 0) // does the mesh contain materials?
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                            aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material, 
                                            aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    } 

    return Mesh(vertices, indices, textures);
};

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) 
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        Texture texture;
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string path = Directory + std::string(str.C_Str());
        if (loadedTextures.count(path) > 0)
        {
            texture = loadedTextures[path];
        }
        else
        {
            texture = Texture(path.c_str(), typeName.c_str());
            loadedTextures[path] = texture;
        }
        textures.push_back(texture);
    }
    return textures;
}