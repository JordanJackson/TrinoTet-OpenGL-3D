#include "RenderSystem.h"

#include "IRenderable.h"

void RenderSystem::Render()
{
	for (auto renderable : renderables)
	{
		renderable->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
}

void RenderSystem::AddRenderable(IRenderable* renderable)
{
	renderables.push_back(renderable);
}

void RenderSystem::RemoveRenderable(IRenderable* renderable)
{
	std::vector<IRenderable*>::iterator it;
	it = std::find(renderables.begin(), renderables.end(), renderable);
	// if it exists in renderables, erase
	if (it != renderables.end())
	{
		renderables.erase(it);
	}
	// TODO consider changing this to erase/remove idiom
}