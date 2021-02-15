#pragma once
#include "SceneObject.h"
#include "Utils.h"
#include <unordered_map>

namespace dae
{
	class Component;
	class TransformComponent;
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update(float elapsedSec) override;
		void Render() const override;

		void AddComponent(ComponentType type, std::shared_ptr<Component> pComponent);

		inline std::shared_ptr<TransformComponent> GetTransform() const;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::shared_ptr<TransformComponent> m_pTransform;
		std::unordered_multimap<ComponentType, std::shared_ptr<Component>> m_pComponents;
	};

	inline std::shared_ptr<TransformComponent> dae::GameObject::GetTransform() const
	{
		return m_pTransform;
	}
}
