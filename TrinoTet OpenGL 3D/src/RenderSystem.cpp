#include "RenderSystem.h"

#include "IRenderable.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

void RenderSystem::Render()
{

	// set light uniforms
	Shader s = ResourceManager::GetShader("Standard");
	SetLightUniforms(s);


	for (auto renderable : opaqueRenderables)
	{
		renderable->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}

	for (auto renderable : transparentRenderables)
	{
		renderable->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
}

void RenderSystem::SetLightUniforms(Shader& s)
{
	// Directional lights
	int numDirLight = directionalLights.size();
	s.SetInteger("dirLightCount", numDirLight, GL_TRUE);
	check_gl_error();
	for (GLuint i = 0; i < numDirLight; ++i)
	{
		std::string idx = std::to_string(i);
		s.SetVector3f(("dirLights[" + idx + "].direction").c_str(), directionalLights[i]->Transform().Forward(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].ambient").c_str(), directionalLights[i]->Ambient(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].diffuse").c_str(), directionalLights[i]->Diffuse(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].specular").c_str(), directionalLights[i]->Specular(), GL_FALSE);
	}
	check_gl_error();
	// Point lights
	int numPointLight = pointLights.size();
	s.SetInteger("pointLightCount", numPointLight, GL_FALSE);
	check_gl_error();
	for (GLuint i = 0; i < numPointLight; ++i)
	{
		std::string idx = std::to_string(i);
		s.SetVector3f(("pointLights[" + idx + "].position").c_str(), pointLights[i]->Transform().GetPosition(), GL_FALSE);
		s.SetVector3f(("pointLights[" + idx + "].ambient").c_str(), pointLights[i]->Ambient(), GL_FALSE);
		s.SetVector3f(("pointLights[" + idx + "].diffuse").c_str(), pointLights[i]->Diffuse(), GL_FALSE);
		s.SetVector3f(("pointLights[" + idx + "].specular").c_str(), pointLights[i]->Specular(), GL_FALSE);
		s.SetFloat(("pointLights[" + idx + "].constant").c_str(), pointLights[i]->Constant(), GL_FALSE);
		s.SetFloat(("pointLights[" + idx + "].linear").c_str(), pointLights[i]->Linear(), GL_FALSE);
		s.SetFloat(("pointLights[" + idx + "].quadratic").c_str(), pointLights[i]->Quadratic(), GL_FALSE);
	}
	check_gl_error();
	// Spot lights
	int numSpotLight = spotLights.size();
	s.SetInteger("spotLightCount", numSpotLight, GL_FALSE);
	check_gl_error();
	for (GLuint i = 0; i < numSpotLight; ++i)
	{
		std::string idx = std::to_string(i);
		s.SetVector3f(("spotLights[" + idx + "].position").c_str(), spotLights[i]->Transform().GetPosition(), GL_FALSE);
		s.SetVector3f(("spotLights[" + idx + "].direction").c_str(), spotLights[i]->Transform().Forward(), GL_FALSE);
		s.SetVector3f(("spotLights[" + idx + "].ambient").c_str(), spotLights[i]->Ambient(), GL_FALSE);
		s.SetVector3f(("spotLights[" + idx + "].diffuse").c_str(), spotLights[i]->Diffuse(), GL_FALSE);
		s.SetVector3f(("spotLights[" + idx + "].specular").c_str(), spotLights[i]->Specular(), GL_FALSE);
		s.SetFloat(("spotLights[" + idx + "].constant").c_str(), spotLights[i]->Constant(), GL_FALSE);
		s.SetFloat(("spotLights[" + idx + "].linear").c_str(), spotLights[i]->Linear(), GL_FALSE);
		s.SetFloat(("spotLights[" + idx + "].quadratic").c_str(), spotLights[i]->Quadratic(), GL_FALSE);
		s.SetFloat(("spotLights[" + idx + "].cutOff").c_str(), spotLights[i]->CutOff(), GL_FALSE);
		s.SetFloat(("spotLights[" + idx + "].outerCutOff").c_str(), spotLights[i]->OuterCutOff(), GL_FALSE);
	}
	check_gl_error();
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