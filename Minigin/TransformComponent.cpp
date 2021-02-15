#include "MiniginPCH.h"
#include "TransformComponent.h"

using namespace dae;

TransformComponent::TransformComponent()
	: Component()
	, m_Position{0.f, 0.f}
{
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TransformComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}
