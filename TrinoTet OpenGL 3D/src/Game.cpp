#include "Game.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"

Game::Game()
	: window(nullptr)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(540, 800, "TrinoTet3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!glewInit())
	{
		return false;
	}
	// initialization successful
	return true;
}

bool Game::Load()
{
	ResourceManager::LoadShader("Shaders/standard.vert", "Shaders/standard.frag", nullptr, "Standard");

	GameObject block;
	block.AddComponent(new MeshRenderer());

	// loading successful
	return true;
}

void Game::Loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.2f, 0.65f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}
