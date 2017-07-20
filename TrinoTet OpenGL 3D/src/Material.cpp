#include "Material.h"

Material::Material()
	: shader(nullptr), diffuse(nullptr)
{

}

Material::Material(Shader& shader, Texture& diffuse)
	: shader(&shader), diffuse(&diffuse)
{

}

void Material::SetActive()
{
	//shader->Use();

	check_gl_error();
	// bind textures etc.
}