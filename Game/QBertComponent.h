#pragma once
#include <Component.h>

namespace dae
{
	class TileComponent; 
	class Scene;
	class GameManagerComponent;
	class QBertComponent final : public Component
	{
	public:
		enum class MoveDirections
		{
			TopRight, BottomRight, BottomLeft, TopLeft
		};

		QBertComponent();

		void Initialize(TileComponent* pStartTile, Scene* pScene, int player, GameManagerComponent* pGameManagerComponent);
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		int GetLives() const;

		void KilledCoily();
		void Move(MoveDirections moveDirection);
		void Reset(TileComponent* pStartTile);

	private:
		void SetCurrentTile(TileComponent* pTile);
		friend class SpinningDisksComponent;

		bool m_CanMove;

		int m_MaxHearts = 3;
		
		const float m_JumpTime; 
		float m_Timer; 

		GameManagerComponent* m_pGameManagerComponent;
		TileComponent* m_pCurrentTile;

		std::vector<GameObject*> m_pHearts;
	};
}

