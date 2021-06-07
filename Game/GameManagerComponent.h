#pragma once
#include <Component.h>
#include <vector>

namespace dae
{
	class Scene; 
	class GameObject; 
	class GameManagerComponent final : public Component
	{
	public:
		enum class GameMode
		{
			Single, Coop
		};

		GameManagerComponent(Scene* pScene, GameMode gameMode);

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void NextLevel(); 
		void SoftReset();

	private:
		float m_CoilySpawnTime;
		float m_GameTime; 
		float m_SlickSpawnTime;
		float m_SamSpawnTime; 
		float m_UggSpawnTime;
		float m_WrongWaySpawnTime;

		bool m_SpawnSlick;
		bool m_SpawnSam;
		bool m_SpawnUgg;
		bool m_SpawnWrongWay;
		bool m_SpawnCoily;

		int m_DeadPlayers;
		int m_Level;
		const int m_MaxLevel; 

		GameObject* m_pCoily;
		GameObject* m_pSlick;
		GameObject* m_pSam;
		GameObject* m_pUgg;
		GameObject* m_pWrongWay;

		Scene* m_pScene; 

		std::vector<GameObject*> m_pQBerts; 

	};

}

