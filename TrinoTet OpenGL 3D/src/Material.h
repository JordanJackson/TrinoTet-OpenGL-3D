#ifndef _SRC_MATERIAL_H_
#define _SRC_MATERIAL_H_
#pragma once

#include "GLDebugger.h"
#include "Shader.h"
#include "Texture.h"

enum TextureID
{
	DIFFUSE,
	SPECULAR,
	EMISSION,
	NORMAL,
};

class Material
{
	// change back to private
private:
	Shader* shader;
	Texture* diffuse;
	glm::vec4 color;
	bool transparent;

public:
	Material();
	Material(Shader& shader, Texture& diffuse);
	Material(Shader& shader, Texture& diffuse, glm::vec4 color);

	Shader& SetActive();

	inline bool Transparent() { return transparent; }
};

#endif