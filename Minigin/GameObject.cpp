#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

using namespace dae;

dae::GameObject::GameObject(const std::string& name)
	:m_Name(name)
{
	m_pTransform = std::make_shared<TransformComponent>();
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{
	for (std::pair<ComponentType, std::shared_ptr<Component>> component : m_pComponents)
	{
		component.second->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for (std::pair<ComponentType, std::shared_ptr<Component>> component : m_pComponents)
	{
		component.second->Render(m_pTransform->GetPosition());
	}
}

void dae::GameObject::AddComponent(ComponentType type, std::shared_ptr<Component> pComponent)
{
	m_pComponents.insert(std::make_pair(type, pComponent));
	pComponent->SetGameObject(this);
}
