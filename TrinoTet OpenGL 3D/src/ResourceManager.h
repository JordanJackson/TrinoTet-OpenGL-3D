#ifndef _SRC_RESOURCEMANAGER_H_
#define _SRC_RESOURCEMANAGER_H_
#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture.h"
#include "Shader.h"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>	Shaders;
	static std::map<std::string, Texture>	Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment and geometry shader source code.
	static Shader		LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	// Retrieves a stored shader
	static Shader		GetShader(std::string name);
	// Loads (and generates) a texture from file
	static Texture	LoadTexture(const GLchar* file, GLboolean alpha, std::string name);
	// Retrieves a stored texture
	static Texture	GetTexture(std::string name);
	// Properly de-allocates all loaded resources
	static void			Clear();
private:
	// Private constructor, singleton
	ResourceManager()
	{

	}
	// Loads and generates a shader from file
	static Shader		loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture		loadTextureFromFile(const GLchar* file, GLboolean alpha);
};

#endif