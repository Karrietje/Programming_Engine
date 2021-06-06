#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class TileManager;
	class SubjectComponent; 
	class TileComponent final : public Component
	{

	public:
		struct Neighbours
		{
			TileComponent* TopRight;
			TileComponent* BottomRight;
			TileComponent* BottomLeft;
			TileComponent* TopLeft;
		};

		TileComponent();
		
		void Initialize(Scene* pScene, glm::vec2 position, TileManager* pTileManager, int level = 0);
		void SetTopRightTile(TileComponent* pTile);
		void SetBottomRightTile(TileComponent* pTile);
		void SetBottomLeftTile(TileComponent* pTile);
		void SetTopLeftTile(TileComponent* pTile);

		void JumpOn(SubjectComponent* pSubjectComponent);
		void Revert(); 

		Neighbours GetNeighbours() const;
		glm::vec2 GetPosition() const;
		GameObject* GetEnemy() const; 
		void SetEnemy(GameObject* pEnemy);

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
		

	private:
		bool m_IsRightColor;
		bool m_ColorCyclesBack;

		Neighbours m_Neighbours;
		TileManager* m_pTileManager;

		int m_CurrentColor;
		std::vector<GameObject*> m_pColors;
		GameObject* m_pEnemy; 

	};
}

