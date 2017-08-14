#ifndef _SRC_RENDERSYSTEM_H_
#define _SRC_RENDERSYSTEM_H_
#pragma once

#include <algorithm>
#include <vector>

#include "Camera.h"
#include "Component.h"
#include "ResourceManager.h"

class IRenderable;
class DirectionalLight;
class PointLight;
class SpotLight;

#define MAX_DIR_LIGHTS 4
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 4

class RenderSystem
{
private:
	Camera* camera;

private:
	std::vector<IRenderable*> opaqueRenderables;
	std::vector<IRenderable*> transparentRenderables;

	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

public:
	// singleton Instance accessor
	inline static RenderSystem& Instance()
	{
		static RenderSystem instance;
		return instance;
	}

	void Render();

	inline Camera& GetCamera() const { return *camera; }
	inline void SetCamera(Camera* camera) { this->camera = camera; camera->Initialize(); }

	void AddRenderable(IRenderable* renderable);
	void RemoveRenderable(IRenderable* renderable);
	void SortRenderablesByDistance();

	void AddDirLight(DirectionalLight* light);
	void RemoveDirLight(DirectionalLight* light);

	void AddPointLight(PointLight* light);
	void RemovePointLight(PointLight* light);

	void AddSpotLight(SpotLight* light);
	void RemoveSpotLight(SpotLight* light);

	inline std::vector<DirectionalLight*>& DirectionalLights() { return directionalLights; }
	inline std::vector<PointLight*>& PointLights() { return pointLights; }
	inline std::vector<SpotLight*>& SpotLights() { return spotLights; }

private:
	void LoadSettings();
	void SetLightUniforms(Shader& s);

// enforces singleton
private:
	RenderSystem() = default;
	~RenderSystem() = default;
	RenderSystem(RenderSystem const&) = delete;
};

#endif