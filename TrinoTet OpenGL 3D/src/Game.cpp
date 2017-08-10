#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "GameObject.h"
#include "GLDebugger.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

bool keys[GLFW_KEY_LAST];

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	

	window = glfwCreateWindow(540, 800, "TrinoTet3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (!glewInit())
	{
		return false;
	}

	glViewport(0, 0, 540, 800);

	// initialization successful
	return true;
}

bool Game::Load()
{
	// Load shaders
	ResourceManager::LoadShader("Shaders/standard.vert", "Shaders/standard.frag", nullptr, "Standard");

	// Load textures
	ResourceManager::LoadTexture("Resources/Textures/Default.png", GL_FALSE, "Default");
	ResourceManager::LoadTexture("Resources/Models/Paladin/textures/Paladin_Diffuse.png", GL_FALSE, "Paladin_Diffuse");
	ResourceManager::LoadTexture("Resources/Models/Paladin/textures/Paladin_specular.png", GL_FALSE, "Paladin_Specular");
	ResourceManager::LoadTexture("Resources/Models/Paladin/textures/Paladin_normal.png", GL_FALSE, "Paladin_Normal");
	ResourceManager::LoadTexture("Resources/Textures/container2_specular.png", GL_TRUE, "Square");
	ResourceManager::LoadTexture("Resources/Textures/PixelBlock.png", GL_FALSE, "PixelBlock");
	ResourceManager::LoadTexture("Resources/Textures/grass.png", GL_TRUE, "Grass");
	ResourceManager::LoadTexture("Resources/Textures/Cracked-Dirt.jpg", GL_FALSE, "Dirt");


	// load a Model
	ResourceManager::LoadModel("Resources/Models/Paladin/Paladin_J_Nordstrom.dae");
	ResourceManager::LoadModel("Resources/Models/Paladin_Idle/idle.dae");

	return true;
}

void Game::Loop()
{
	std::vector<Vertex> localVerts =
	{
		// Back face
		Vertex(glm::vec3(-0.5f, -0.5f,  -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,	-0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,	-0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,	-0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f,  -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 1.0f)),
		// Front face
		Vertex(glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.0f)),
		// Left face
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f)),
		// Right face
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec2(0.0f, 0.0f)),
		// Bottom face
		Vertex(glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		// Top face
		Vertex(glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec2(0.0f, 0.0f)),
	};

	Mesh m = Mesh(localVerts);

	// create Camera
	GameObject* cameraObject = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f));
	Camera* cameraComponent = new Camera(glm::perspective(45.0f, width / height, 0.1f, 100.0f));
	cameraObject->AddComponent(cameraComponent);
	RenderSystem::Instance().SetCamera(cameraComponent);
	std::vector<GameObject*> gameObjects;

	// Directional Light
	GameObject* dirLightObj = new GameObject(glm::vec3(0.0f), glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(1.0f));
	DirectionalLight* dLightC = new DirectionalLight(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.15f, 0.15f, 0.15f), glm::vec3(0.2f, 0.2f, 0.2f));
	dirLightObj->AddComponent(dLightC);
	Material* lightMat = new Material(ResourceManager::GetShader("Standard"), ResourceManager::GetTexture("Default"), glm::vec4(1.0f));
	dirLightObj->AddComponent(new MeshRenderer(*lightMat, m));
	gameObjects.push_back(dirLightObj);


	//// Point lights
	//for (int i = 0; i < 2; ++i)
	//{
	//	for (int j = 0; j < 2; ++j)
	//	{
	//		GameObject* pointLightObj = new GameObject(glm::vec3(i * 2.0f, 1.0f, j * 2.0f), glm::quat(), glm::vec3(1.0f));
	//		pointLightObj->AddComponent(new PointLight(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f));
	//		gameObjects.push_back(pointLightObj);
	//	}
	//}


	gameObjects.push_back(cameraObject);

	GameObject* block = new GameObject(glm::vec3(0.0f, -2.0f, -10.0f), glm::quat(), glm::vec3(0.01f));

	Mesh paladin = ResourceManager::GetMesh("Paladin_J_NordstromMesh");
	Material mat = Material(ResourceManager::GetShader("Standard"), ResourceManager::GetTexture("Paladin_Diffuse"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	MeshRenderer mRenderer = MeshRenderer(mat, paladin);
	block->AddComponent(&mRenderer);

	//cameraObject->transform->SetParent(*block->transform);
	// Big box
	GameObject* bigBox = new GameObject(glm::vec3(0.0f, 0.0f, -5.0f), glm::quat(), glm::vec3(1.0f));
	Material* bigBoxMat = new Material(ResourceManager::GetShader("Standard"), ResourceManager::GetTexture("Square"), glm::vec4(0.0f, 0.0f, 1.0f, 0.75f));
	MeshRenderer* bigBoxRenderer = new MeshRenderer(*bigBoxMat, m);
	bigBox->AddComponent(bigBoxRenderer);

	gameObjects.push_back(bigBox);

	gameObjects.push_back(block);
	int NUM_BLOCKS = 3;
	
	for (int i = 0; i < 3; i++)
	{
		GameObject* childBlock = new GameObject(glm::vec3(100.0f * (i+ 1), 0.0f, 100.0f * (i + 1)), glm::quat(), glm::vec3(1.0f));
		childBlock->AddComponent(new MeshRenderer(mat, paladin));
		block->transform->AddChild(*childBlock->transform);
		gameObjects.push_back(childBlock);
	}

	// ground boxes
	float offsetPos = -10.0f;
	Material* groundMaterial = new Material(ResourceManager::GetShader("Standard"), ResourceManager::GetTexture("Dirt"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			GameObject* groundBlock = new GameObject(glm::vec3(offsetPos + i * 5.0f, -2.5f, offsetPos + j * 5.0f), glm::quat(), glm::vec3(5.0f, 1.0f, 5.0f));
			MeshRenderer* groundMRenderer = new MeshRenderer(*groundMaterial, m);
			groundBlock->AddComponent(groundMRenderer);
			gameObjects.push_back(groundBlock);
		}
	}

	// enable blending
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// enable face-culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	// enable stencil buffer testing
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!glfwWindowShouldClose(window))
	{
		// TODO this needs to be called only when camera position changes
		RenderSystem::Instance().SortRenderablesByDistance();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwPollEvents();
		
		ProcessInput();

		dirLightObj->transform->Rotate(glfwGetTime() * 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

		if (keys[GLFW_KEY_UP])
		{
			block->transform->Translate(glm::vec3(0.0f, 0.0f, -0.1f));
		}
		if (keys[GLFW_KEY_DOWN])
		{
			block->transform->Translate(glm::vec3(0.0f, 0.0f, 0.1f));
		}

		if (keys[GLFW_KEY_W])
		{
			cameraObject->transform->Translate(cameraObject->transform->Forward() * 0.1f);
		}
		if (keys[GLFW_KEY_S])
		{
			cameraObject->transform->Translate(-cameraObject->transform->Forward() * 0.1f);
		}

		if (keys[GLFW_KEY_A])
		{
			cameraObject->transform->Translate(cameraObject->transform->Right() * 0.1f);
		}
		if (keys[GLFW_KEY_D])
		{
			cameraObject->transform->Translate(-cameraObject->transform->Right() * 0.1f);
		}

		if (keys[GLFW_KEY_Q])
		{
			cameraObject->transform->Rotate(0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (keys[GLFW_KEY_E])
		{
			cameraObject->transform->Rotate(-0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		glClearColor(0.0f, 0.2f, 0.35f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		RenderSystem::Instance().Render();
		check_gl_error();


		glfwSwapBuffers(window);
	}
}

void Game::Close()
{
	ResourceManager::Clear();

	glfwTerminate();
}

void Game::key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keys[keycode] = true;
	}
	else
	{
		keys[keycode] = false;
	}
}

void Game::ProcessInput()
{
	if (keys[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}