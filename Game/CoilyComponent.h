#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class GameObject;
	class TileComponent;
	class QBertComponent;
	class CoilyComponent final : public Component
	{
	public:
		CoilyComponent();

		void Initialize(TileComponent* pStartTile, Scene* pScene, QBertComponent* pQbert);
		virtual void Render(glm::vec2 position) override;
		virtual void Update(float elapsedSec) override;

		bool IsEgg() const;
		bool IsHatching() const;

		void Hatch(TileComponent* pHatchTile);
		void Reset(TileComponent* pTile);

		QBertComponent* GetQbert() const;

	private:
		bool m_IsEgg;
		bool m_IsHatching;

		float m_Timer;
		const float m_HatchTimer;

		TileComponent* m_pHatchTile;
		QBertComponent* m_pQbert;

		GameObject* m_pEggSpriteSheet;
		GameObject* m_pCoilySpriteSheet;
	};
}