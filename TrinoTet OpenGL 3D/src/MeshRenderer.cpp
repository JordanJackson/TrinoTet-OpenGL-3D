#include "MeshRenderer.h"

#include "RenderSystem.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

MeshRenderer::MeshRenderer(Material& material, Mesh& mesh)
	: IRenderable(material), mesh(&mesh)
{
	//std::cout << "MeshRenderer: " << material.shader->ID << std::endl;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Render(glm::mat4 view, glm::mat4 projection)
{
	//std::cout << "MeshRenderer Render: " << material->shader->ID << std::endl;
	Shader s = material->SetActive();
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "model"), 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// view position
	s.SetVector3f("viewPos", RenderSystem::Instance().GetCamera().Transform().GetPosition(), GL_FALSE);

	// Pass lights to shader
	std::vector<DirectionalLight*>& dirLights = RenderSystem::Instance().DirectionaLights();
	std::vector<PointLight*>& pointLights = RenderSystem::Instance().PointLights();
	std::vector<SpotLight*>& spotLights = RenderSystem::Instance().SpotLights();

	// Directional lights
	int numDirLight = dirLights.size();
	s.SetInteger("dirLightCount", numDirLight, GL_FALSE);
	for (GLuint i = 0; i < numDirLight; ++i)
	{
		std::string idx = std::to_string(i);
		s.SetVector3f(("dirLights[" + idx + "].direction").c_str(), dirLights[i]->Transform().Forward(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].ambient").c_str(), dirLights[i]->Ambient(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].diffuse").c_str(), dirLights[i]->Diffuse(), GL_FALSE);
		s.SetVector3f(("dirLights[" + idx + "].specular").c_str(), dirLights[i]->Specular(), GL_FALSE);
	}

	// Point lights
	int numPointLight = pointLights.size();
	s.SetInteger("pointLightCount", numPointLight, GL_FALSE);
	for (GLuint i = 0; i < numPointLight; ++i)
	{
		std::string idx = std::to_string(i);
		s.SetVector3f(("pointsLights[" + idx + "].position").c_str(), pointLights[i]->Transform().GetPosition(), GL_FALSE);
		s.SetVector3f(("pointsLights[" + idx + "].ambient").c_str(), pointLights[i]->Ambient(), GL_FALSE);
		s.SetVector3f(("pointsLights[" + idx + "].diffuse").c_str(), pointLights[i]->Diffuse(), GL_FALSE);
		s.SetVector3f(("pointsLights[" + idx + "].specular").c_str(), pointLights[i]->Specular(), GL_FALSE);
		s.SetFloat(("pointsLights[" + idx + "].constant").c_str(), pointLights[i]->Constant(), GL_FALSE);
		s.SetFloat(("pointsLights[" + idx + "].linear").c_str(), pointLights[i]->Linear(), GL_FALSE);
		s.SetFloat(("pointsLights[" + idx + "].quadratic").c_str(), pointLights[i]->Quadratic(), GL_FALSE);
	}

	// Spot lights
	int numSpotLight = spotLights.size();
	s.SetInteger("spotLightCount", numSpotLight, GL_FALSE);
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

	mesh->Draw();
}

void MeshRenderer::Update(GLfloat deltaTime)
{

}