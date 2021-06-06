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
		void SetTopRightTile(TileComponent* pTile);
		void SetBottomRightTile(TileComponent* pTile);
		void SetBottomLeftTile(TileComponent* pTile);
		void SetTopLeftTile(TileComponent* pTile);
		void SetLeftTile(TileComponent* pTile);
		void SetRightTile(TileComponent* pTile);

		SpinningDisksComponent* GetSpinningDisk() const;
		void SetSpinningDisk(SpinningDisksComponent* pSpinningDisk);

		void JumpOn(SubjectComponent* pSubjectComponent);
		void Revert(); 

		Neighbours GetNeighbours() const;
		glm::vec2 GetPosition() const;
		glm::vec2 GetSidePosition(bool left) const;
		GameObject* GetSlickSam() const;
		GameObject* GetUggWrongway() const;
		GameObject* GetCoily() const;
		void SetSlickSam(GameObject* pEnemy);
		void SetUggWrongway(GameObject* pEnemy);
		void SetCoily(GameObject* pCoily);

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
		

	private:
		bool m_IsRightColor;
		bool m_ColorCyclesBack;

		Neighbours m_Neighbours;
		TileManager* m_pTileManager;

		int m_CurrentColor;
		std::vector<GameObject*> m_pColors;
		GameObject* m_pSlickSam; 
		GameObject* m_pUggWrongway;
		GameObject* m_pCoily;

		SpinningDisksComponent* m_pSpinningDisk;
	};
}

