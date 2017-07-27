#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "SOIL.h"


// Instantiate static variables
std::map<std::string, Texture>		ResourceManager::Textures;
std::map<std::string, Shader>		ResourceManager::Shaders;


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

void ProcessNode(aiNode& node)
{
	std::cout << "Mesh Count: " << node.mNumMeshes << std::endl;

	for (int i = 0; i < node.mNumChildren; ++i)
	{
		ProcessNode(*node.mChildren[i]);
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

	std::cout << "Loading Model at " << file << std::endl;
	std::cout << "Mesh Count: " << scene->mNumMeshes << std::endl;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		std::cout << "Mesh Name: " << scene->mMeshes[i]->mName.C_Str() << std::endl;
		std::cout << "Num Vertices: " << scene->mMeshes[i]->mNumVertices << std::endl;

	}
	std::cout << "Material Count: " << scene->mNumMaterials << std::endl;

	std::cout << "Root Node" << std::endl;
	std::cout << "Mesh Count: " << scene->mRootNode->mNumMeshes << std::endl;
	std::cout << "Child Count: " << scene->mRootNode->mNumChildren << std::endl;
	
	for (int i = 0; i < scene->mRootNode->mNumChildren; i++)
	{
		std::cout << std::endl;
		std::cout << "Child Node " << i << std::endl;
		ProcessNode(*scene->mRootNode->mChildren[i]);

	}


	return Model();
}



// Retrieves a stored model
Model ResourceManager::GetModel(std::string name)
{
	return Model();
}

Mesh ResourceManager::LoadMesh(const aiMesh& node)
{
	for (int i = 0; i < node.mNumVertices; i++)
	{

	}
}

Mesh ResourceManager::GetMesh(std::string name)
{
	return Mesh();
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