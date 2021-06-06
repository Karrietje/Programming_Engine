#pragma once
#include <Component.h>

namespace dae
{
	class TileComponent;
	class QBertComponent;
	class SpinningDisksComponent final : public Component
	{
	public:
		SpinningDisksComponent(TileComponent* pReturnTile);

		void Initialize();
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void JumpOn(QBertComponent* pQbert);

		glm::vec2 GetPosition() const;
	private:
		bool m_StartReturn;

		float m_Timer;
		const float m_ReturnTimer;

		TileComponent* m_pReturnTile;
		QBertComponent* m_pQbert;
	};
}