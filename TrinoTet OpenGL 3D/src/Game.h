#ifndef _SRC_GAME_H_
#define _SRC_GAME_H_
#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Transform.h"

class Game
{
private:
	GLFWwindow* window;

	GLfloat width = 540;
	GLfloat height = 800;

public:
	Game();
	~Game();

	bool Initialize();
	bool Load();
	void Loop();
	void Close();
	void ProcessInput();

private:
	static void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
};

#endif