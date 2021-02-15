#pragma once
#include "Component.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent();

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		inline const glm::vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
	private:
		glm::vec2 m_Position;
	};
}