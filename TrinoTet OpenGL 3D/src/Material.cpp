#include "Material.h"

#include <iostream>

Material::Material()
	: shader(nullptr), diffuse(nullptr), color(glm::vec4(1.0f))
{

}

Material::Material(Shader& shader, Texture& diffuse)
	: shader(&shader), diffuse(&diffuse), color(glm::vec4(1.0f))
{

}

Material::Material(Shader& shader, Texture& diffuse, glm::vec4 color)
	: shader(&shader), diffuse(&diffuse), color(color)
{

}

Shader& Material::SetActive()
{
	// use shader program
	shader->Use();
	// bind provided textures
	if (diffuse != nullptr)
	{
		diffuse->Bind();
	}
	// send color to shader
	shader->SetVector4f("material.color", color, GL_FALSE);

	return *shader;
}