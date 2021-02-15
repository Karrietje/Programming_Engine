#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		TextComponent();

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> pFont);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

