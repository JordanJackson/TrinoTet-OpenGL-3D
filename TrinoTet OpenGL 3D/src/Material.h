#ifndef _SRC_MATERIAL_H_
#define _SRC_MATERIAL_H_
#pragma once

#include "GLDebugger.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
	// change back to private
public:
	Shader* shader;
	Texture* diffuse;

public:
	Material();
	Material(Shader& shader, Texture& diffuse);

	Shader& SetActive();
};

#endif