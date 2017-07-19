#ifndef _SRC_GAME_H_
#define _SRC_GAME_H_
#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "Transform.h"

class Game
{
private:
	GLFWwindow* window;

public:
	Game();
	~Game();

	bool Initialize();
	bool Load();
	void Loop();
};

#endif