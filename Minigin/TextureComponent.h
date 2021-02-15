#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent() = default;

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SetTexture(const std::string& filename);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}