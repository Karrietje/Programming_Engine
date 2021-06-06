#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace dae
{
	class TileComponent;
	class Scene;
	class GameManagerComponent; 
	class SpinningDisksComponent;
	class TileManager final : public Singleton<TileManager>
	{
	public:
		void CreateLevels(const std::string& file, Scene* pScene, int level);

		const std::vector<std::vector<TileComponent*>>& GetTiles(int level) const;
		const std::vector<SpinningDisksComponent*>& GetSpinningDisks(int level) const;

		void SetTile(bool right);
		void SetGameManager(GameManagerComponent* pGameComponent); 

	private:
		friend class Singleton<TileManager>;
		TileManager() = default;

		int m_NrTiles;
		int m_NrRightTiles;

		GameManagerComponent* m_pGameComponent; 
		std::map<int, std::vector<std::vector<TileComponent*>>> m_pTiles;
		std::map<int, std::vector<SpinningDisksComponent*>> m_pSpinningDisks;
	};
}