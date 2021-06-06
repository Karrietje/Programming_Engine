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

		void SoftReset();

		void NextLevel(); 
	private:
		float m_SlickSpawnTime;
		float m_SamSpawnTime; 
		float m_UggSpawnTime;
		float m_WrongWaySpawnTime;
		float m_CoilySpawnTime;
		float m_GameTime; 

		bool m_SpawnSlick;
		bool m_SpawnSam;
		bool m_SpawnUgg;
		bool m_SpawnWrongWay;
		bool m_SpawnCoily;

		int m_DeadPlayers;

		GameObject* m_pSlick;
		GameObject* m_pSam;
		GameObject* m_pUgg;
		GameObject* m_pWrongWay;
		GameObject* m_pCoily;

		std::vector<GameObject*> m_pQBerts; 

		int m_Level;
		const int m_MaxLevel; 
		Scene* m_pScene; 
	};

}

