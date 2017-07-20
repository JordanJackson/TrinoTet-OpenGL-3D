#include "Material.h"

#include <iostream>

Material::Material()
	: shader(nullptr), diffuse(nullptr)
{

}

Material::Material(Shader& shader, Texture& diffuse)
	: shader(&shader), diffuse(&diffuse)
{
	std::cout << "Material Constructor: " << this->shader->ID << std::endl;
}

Shader& Material::SetActive()
{
	//std::cout << shader->ID << std::endl;
	return shader->Use();
	// bind textures etc.
}