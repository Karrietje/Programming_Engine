#include "TileManager.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "Scene.h"
#include "GameComponents.h"
#include "Components.h"

void dae::TileManager::CreateLevels(const std::string& file, Scene* pScene, int levels)
{
	std::string filePath{ ResourceManager::GetInstance().GetDataPath() + file };
	std::fstream* pReader{ new std::fstream() };
	pReader->open(filePath);
	if (!pReader)
	{
		std::cout << "Couldn't open file}\n";
	}

	std::string line{};
	std::getline(*pReader, line);

	int nrRows{};
	nrRows = std::stoi(line);

	std::getline(*pReader, line);

	int size{};
	size = std::stoi(line);

	pReader->close();
	delete pReader;

	for (int level = 0; level < levels; level++)
	{
		m_pTiles[level] = std::vector<std::vector<TileComponent*>>();
		float startX{ float(320 - size) };
		float startY{ float(size) };

		for (int row{}; row < nrRows; row++)
		{
			m_pTiles[level].push_back(std::vector<TileComponent*>());
			for (int i{}; i < row + 1; i++)
			{
				GameObject* pGameObject = new GameObject();
				pScene->Add(pGameObject, 0);
				TileComponent* pTileComponent = new TileComponent();
				pGameObject->AddComponent(ComponentType::TileComponent, pTileComponent);
				pTileComponent->Initialize(pScene, { startX + (i * size), startY }, this, level);
				m_pTiles[level][row].push_back(pTileComponent);

				if (level != 0)
					pGameObject->SetActive(false);
			}
			startX -= (size / 2.f);

			if (row == ((nrRows / 2) + 1))
			{
				GameObject* pGameObject = new GameObject();
				pScene->Add(pGameObject, 0);
				SpinningDisksComponent* pSpinningDiskComponent = new SpinningDisksComponent(m_pTiles[level][0][0]);
				pGameObject->AddComponent(ComponentType::SpinningDisksComponent, pSpinningDiskComponent);
				pSpinningDiskComponent->Initialize();
				m_pTiles[level][row][0]->SetSpinningDisk(pSpinningDiskComponent);
				pGameObject->GetTransform()->SetPosition(startX + (size / 4), startY - (size / 2));

				if (level != 0)
					pGameObject->SetActive(false);
				m_pSpinningDisks[level].push_back(pSpinningDiskComponent);

				pGameObject = new GameObject();
				pScene->Add(pGameObject, 0);
				pSpinningDiskComponent = new SpinningDisksComponent(m_pTiles[level][0][0]);
				pGameObject->AddComponent(ComponentType::SpinningDisksComponent, pSpinningDiskComponent);
				pSpinningDiskComponent->Initialize();
				m_pTiles[level][row][row]->SetSpinningDisk(pSpinningDiskComponent);
				pGameObject->GetTransform()->SetPosition(startX + ((row + 1) * size) + (size / 4), startY - (size / 2));

				if (level != 0)
					pGameObject->SetActive(false);
				m_pSpinningDisks[level].push_back(pSpinningDiskComponent);
			}

			startY += (size * 3.f / 4.f);
		}

		for (size_t row{}; row < m_pTiles[level].size(); row++)
		{
			for (size_t tileIdx{}; tileIdx < m_pTiles[level][row].size(); tileIdx++)
			{
				if (row != 0)
				{
					if (tileIdx != 0)
					{
						m_pTiles[level][row][tileIdx]->SetTopLeftTile(m_pTiles[level][row - 1][tileIdx - 1]);
						m_pTiles[level][row][tileIdx]->SetLeftTile(m_pTiles[level][row][tileIdx - 1]);
					}
					else
					{
						m_pTiles[level][row][tileIdx]->SetTopLeftTile(nullptr);
					}

					if (tileIdx != (m_pTiles[level][row].size() - 1))
					{
						m_pTiles[level][row][tileIdx]->SetTopRightTile(m_pTiles[level][row - 1][tileIdx]);
						m_pTiles[level][row][tileIdx]->SetRightTile(m_pTiles[level][row][tileIdx + 1]);
					}
					else
					{
						m_pTiles[level][row][tileIdx]->SetTopRightTile(nullptr);
					}
				}
				else
				{
					m_pTiles[level][row][tileIdx]->SetTopLeftTile(nullptr);
					m_pTiles[level][row][tileIdx]->SetTopRightTile(nullptr);
				}

				if (row != (m_pTiles[level].size() - 1))
				{
					m_pTiles[level][row][tileIdx]->SetBottomLeftTile(m_pTiles[level][row + 1][tileIdx]);
					m_pTiles[level][row][tileIdx]->SetBottomRightTile(m_pTiles[level][row + 1][tileIdx + 1]);
				}
				else
				{
					m_pTiles[level][row][tileIdx]->SetBottomLeftTile(nullptr);
					m_pTiles[level][row][tileIdx]->SetBottomRightTile(nullptr);
				}
			}
		}

	}

	for (std::vector<TileComponent*> pTiles : m_pTiles[0])
		m_NrTiles += pTiles.size();
	
}

const std::vector<std::vector<dae::TileComponent*>>& dae::TileManager::GetTiles(int level) const
{
	return m_pTiles.at(level);
}

const std::vector<dae::SpinningDisksComponent*>& dae::TileManager::GetSpinningDisks(int level) const
{
	return m_pSpinningDisks.at(level);
}

void dae::TileManager::SetTile(bool right)
{
	if (right)
		m_NrRightTiles++;
	else
		m_NrRightTiles--;

	if (m_NrTiles == m_NrRightTiles)
	{
		m_NrRightTiles = 0;
		m_pGameComponent->NextLevel();
	}
}

void dae::TileManager::SetGameManager(GameManagerComponent* pGameComponent)
{
	m_pGameComponent = pGameComponent;
}
