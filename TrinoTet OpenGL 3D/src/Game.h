#ifndef _SRC_GAME_H_
#define _SRC_GAME_H_
#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "Transform.h"

class Game
{
private:
	GLFWwindow* window;

	GLfloat width = 540;
	GLfloat height = 800;

	Mesh* _mesh;

public:
	Game();
	~Game();


	GameObject* go;

	bool Initialize();
	bool Load();
	void Loop();
};

#endif