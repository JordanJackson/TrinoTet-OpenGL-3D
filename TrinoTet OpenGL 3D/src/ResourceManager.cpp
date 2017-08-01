#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "SOIL.h"


// Instantiate static variables
std::map<std::string, Texture>		ResourceManager::Textures;
std::map<std::string, Shader>		ResourceManager::Shaders;
std::map<std::string, Model>		ResourceManager::Models;
std::map<std::string, Mesh>			ResourceManager::Meshes;


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ProcessNode(const aiScene* scene, aiNode& node)
{
	for (int i = 0; i < node.mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node.mMeshes[i]];
		ResourceManager::LoadMesh(mesh->mName.C_Str(), *mesh);
	}

	for (int i = 0; i < node.mNumChildren; ++i)
	{
		ProcessNode(scene, *node.mChildren[i]);
	}
	std::cout << std::endl;
}

// Loads a model from file via Assimp importer
Model ResourceManager::LoadModel(const GLchar* file)
{
	const aiScene* scene;
	Assimp::Importer importer;

	aiMatrix4x4 globalInverseTransform;

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures;

	scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
	ProcessNode(scene, *scene->mRootNode);

	return Model();
}

// Retrieves a stored model
Model ResourceManager::GetModel(std::string name)
{
	return Model();
}

Mesh ResourceManager::LoadMesh(const char* name, const aiMesh& node)
{
	std::vector<Vertex> vertices;
	vertices.reserve(node.mNumVertices);

	for (int i = 0; i < node.mNumVertices; ++i)
	{
		aiVector3D nodePos = node.mVertices[i];
		aiVector3D nodeNorm = node.mNormals[i];
		aiVector3D nodeTex = node.mTextureCoords[0][i];

		vertices.push_back(Vertex(
			glm::vec3(nodePos.x, nodePos.y, nodePos.z),
			glm::vec3(nodeNorm.x, nodeNorm.y, nodeNorm.z),
			glm::vec2(nodeTex.x, nodeTex.y)
		));
	}
	

	std::vector<GLuint> indices;
	indices.reserve(node.mNumFaces * 3);
	
	for (int i = 0; i < node.mNumFaces; ++i)
	{
		aiFace face = node.mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// bones
	// materials
	Mesh mesh(vertices, indices);
	ResourceManager::Meshes.insert(std::pair<std::string, Mesh>(name, mesh));

	return mesh;
}

Mesh ResourceManager::GetMesh(std::string name)
{
	return Meshes[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}