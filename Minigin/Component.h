#pragma once
#include "Utils.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <unordered_map>

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component();

		virtual void Update(float elapsedSec) = 0;
		virtual void Render(glm::vec2 position) = 0;

		void SetGameObject(GameObject* pGameObject);
		inline GameObject* GetGameObject()const;

	protected:
		GameObject* m_pGameObject;
	};

	inline GameObject* dae::Component::GetGameObject() const
	{
		return m_pGameObject;
	}
}

