#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void dae::TextureComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::TextureComponent::Render(glm::vec2 position)
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
