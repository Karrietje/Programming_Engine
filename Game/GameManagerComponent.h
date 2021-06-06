#pragma once
#include <Component.h>

namespace dae
{
	class Scene; 
	class GameObject; 
	class GameManagerComponent final : public Component
	{
	public:
		GameManagerComponent(Scene* pScene);

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void NextLevel(); 
	private:
		float m_SlickSpawnTime;
		float m_SamSpawnTime; 
		float m_GameTime; 

		bool m_SpawnSlick;
		bool m_SpawnSam;

		GameObject* m_pSlick;
		GameObject* m_pSam;
		GameObject* m_pQBert; 

		int m_Level;
		const int m_MaxLevel; 
		Scene* m_pScene; 
	};

}

