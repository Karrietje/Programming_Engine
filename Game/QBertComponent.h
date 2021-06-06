#pragma once
#include <Component.h>

namespace dae
{
	class TileComponent; 
	class Scene;
	class QBertComponent final : public Component
	{
	public:
		enum class MoveDirections
		{
			TopRight, BottomRight, BottomLeft, TopLeft
		};

		QBertComponent();

		void Initialize(TileComponent* pStartTile, Scene* pScene);
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void Move(MoveDirections moveDirection);
		void Reset(TileComponent* pStartTile);
	private:
		TileComponent* m_pCurrentTile;
		std::vector<GameObject*> m_pHearts;
		
		int m_MaxHearts = 3;

		const float m_JumpTime; 
		float m_Timer; 
	};
}

