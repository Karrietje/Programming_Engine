#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class TileManager;
	class SubjectComponent; 
	class SpinningDisksComponent;
	class TileComponent final : public Component
	{

	public:
		struct Neighbours
		{
			TileComponent* TopRight;
			TileComponent* BottomRight;
			TileComponent* BottomLeft;
			TileComponent* TopLeft;
			TileComponent* Left;
			TileComponent* Right;
		};

		TileComponent();
		
		void Initialize(Scene* pScene, glm::vec2 position, TileManager* pTileManager, int level = 0);
		void JumpOn(SubjectComponent* pSubjectComponent);
		void SetTopRightTile(TileComponent* pTile);
		void SetBottomRightTile(TileComponent* pTile);
		void SetBottomLeftTile(TileComponent* pTile);
		void SetTopLeftTile(TileComponent* pTile);
		void SetLeftTile(TileComponent* pTile);
		void SetRightTile(TileComponent* pTile);
		void SetSpinningDisk(SpinningDisksComponent* pSpinningDisk);
		void Revert(); 

		void SetCoily(GameObject* pCoily);
		void SetSlickSam(GameObject* pEnemy);
		void SetUggWrongway(GameObject* pEnemy);

		SpinningDisksComponent* GetSpinningDisk() const;
		Neighbours GetNeighbours() const;
		glm::vec2 GetPosition() const;
		glm::vec2 GetSidePosition(bool left) const;
		GameObject* GetSlickSam() const;
		GameObject* GetUggWrongway() const;
		GameObject* GetCoily() const;

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
		bool m_IsRightColor;
		bool m_ColorCyclesBack;

		int m_CurrentColor;
		
		TileManager* m_pTileManager;
		Neighbours m_Neighbours;

		GameObject* m_pCoily;
		GameObject* m_pSlickSam; 
		GameObject* m_pUggWrongway;

		std::vector<GameObject*> m_pColors;
		SpinningDisksComponent* m_pSpinningDisk;
	};
}

