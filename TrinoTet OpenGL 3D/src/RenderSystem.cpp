#include "RenderSystem.h"

#include "IRenderable.h"

void RenderSystem::Render()
{
	for (auto renderable : opaqueRenderables)
	{
		renderable->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}

	for (auto renderable : transparentRenderables)
	{
		renderable->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
}

void RenderSystem::AddRenderable(IRenderable* renderable)
{
	if (renderable->GetMaterial().Transparent())
	{
		transparentRenderables.push_back(renderable);
	}
	else
	{
		opaqueRenderables.push_back(renderable);
	}
}

void RenderSystem::RemoveRenderable(IRenderable* renderable)
{
	if (renderable->GetMaterial().Transparent())
	{
	std::vector<IRenderable*>::iterator it;
	it = std::find(transparentRenderables.begin(), transparentRenderables.end(), renderable);
	// if it exists in renderables, erase
	if (it != transparentRenderables.end())
	{
		transparentRenderables.erase(it);
	}
	}
	else
	{
		std::vector<IRenderable*>::iterator it;
		it = std::find(transparentRenderables.begin(), transparentRenderables.end(), renderable);
		// if it exists in renderables, erase
		if (it != transparentRenderables.end())
		{
			transparentRenderables.erase(it);
		}
	}
	// TODO consider changing this to erase/remove idiom
}

void RenderSystem::AddDirLight(DirectionalLight* light)
{
	directionalLights.push_back(light);
}

void RenderSystem::RemoveDirLight(DirectionalLight* light)
{
	auto it = std::find(directionalLights.begin(), directionalLights.end(), light);
	if (it != directionalLights.end())
	{
		directionalLights.erase(it);
	}
}

void RenderSystem::AddPointLight(PointLight* light)
{
	pointLights.push_back(light);
}

void RenderSystem::RemovePointLight(PointLight* light)
{
	auto it = std::find(pointLights.begin(), pointLights.end(), light);
	if (it != pointLights.end())
	{
		pointLights.erase(it);
	}
}

void RenderSystem::AddSpotLight(SpotLight* light)
{
	spotLights.push_back(light);
}

void RenderSystem::RemoveSpotLight(SpotLight* light)
{
	auto it = std::find(spotLights.begin(), spotLights.end(), light);
	if (it != spotLights.end())
	{
		spotLights.erase(it);
	}
}

void RenderSystem::SortRenderablesByDistance()
{
	if (camera == nullptr)
	{
		return;
	}
	std::sort(transparentRenderables.begin(), transparentRenderables.end(), [this](IRenderable* a, IRenderable* b)
	{
		return 
			glm::distance2(this->GetCamera().Transform().GetPosition(), a->Transform().GetPosition())
			>
			glm::distance2(this->GetCamera().Transform().GetPosition(), b->Transform().GetPosition());
	});
}