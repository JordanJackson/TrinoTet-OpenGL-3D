#ifndef _SRC_RENDERSYSTEM_H_
#define _SRC_RENDERSYSTEM_H_
#pragma once

#include <algorithm>
#include <vector>

#include "Camera.h"

class IRenderable;

class RenderSystem
{
private:
	Camera* camera;

private:
	std::vector<IRenderable*> renderables;

public:
	// singleton Instance accessor
	inline static RenderSystem& Instance()
	{
		static RenderSystem instance;
		return instance;
	}

	void Render();

	inline const Camera& GetCamera() const { return *camera; }
	inline void SetCamera(Camera* camera) { this->camera = camera; camera->Initialize(); }

	void AddRenderable(IRenderable* renderable);
	void RemoveRenderable(IRenderable* renderable);

private:
	void LoadSettings();

// enforces singleton
private:
	RenderSystem() = default;
	~RenderSystem() = default;
	RenderSystem(RenderSystem const&) = delete;
};

#endif