#ifndef _SRC_SHADER_H_
#define _SRC_SHADER_H_
#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLDebugger.h"

class Shader
{
public:
	// State
	GLuint ID;
	// Constructor
	Shader() = default;
	// Sets this shader as active
	Shader& Use();
	// Compiles the shader from given source code
	void	Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource);
	// Utility functions
	void	SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	// Checks if compilation or linking failed and prints any error logs
	void	CheckCompileErrors(GLuint object, std::string type);
};

#endif