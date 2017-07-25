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