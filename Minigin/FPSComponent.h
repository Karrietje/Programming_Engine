#pragma once
#include "Component.h"

namespace dae
{
    class Font;
    class TextComponent;
    class FPSComponent final : public Component
    {
    public:
        FPSComponent();

        virtual void Update(float elapsedSec) override;
        virtual void Render(glm::vec2 position) override;


        void SetFont(std::shared_ptr<Font> pFont);

    private:
        int m_Frames;
        int m_FPS;
        float m_Elapsed;
        std::shared_ptr<Font> m_pFont;
        std::shared_ptr<TextComponent> m_pText;
    };
}