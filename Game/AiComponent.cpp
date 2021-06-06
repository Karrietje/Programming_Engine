#include "AiComponent.h"
#include "Components.h"
#include "TileComponent.h"
#include "GameObject.h"

dae::AiComponent::AiComponent(TileComponent* pStartTile, Type type)
	:m_pCurrentTile{pStartTile}
	, m_MoveTime{ 1.f }
	, m_Timer{0.f}
	, m_Type{type}
{
	
}

void dae::AiComponent::Initialize()
{
	m_pCurrentTile->SetEnemy(m_pGameObject);
}

dae::AiComponent::Type dae::AiComponent::GetType() const
{
	return m_Type;
}

void dae::AiComponent::Update(float elapsedSec)
{
	m_Timer += elapsedSec;
	if (m_Timer >= m_MoveTime)
	{
		m_Timer = 0; 
		TileComponent* pNewTile{ nullptr };
		int slickChoice = 0; 
		switch (m_Type)
		{
		case dae::AiComponent::Type::SlickSam:
			//Randomize how Sam picks his tiles
			slickChoice = std::rand() % 2;
			if (slickChoice == 0)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
				if (pNewTile)
				{
					if (pNewTile->GetEnemy())
					{
						pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
					}
					m_pCurrentTile->SetEnemy(nullptr);
					pNewTile->SetEnemy(m_pGameObject); 
					m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
					m_pCurrentTile = pNewTile;
					m_pCurrentTile->Revert();
				}
				else
				{
					m_pGameObject->SetActive(false);
				}
			}
			else if (slickChoice == 1)
			{

				pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
				if (pNewTile)
				{
					if (pNewTile->GetEnemy())
					{
						pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
					}
					m_pCurrentTile->SetEnemy(nullptr);
					pNewTile->SetEnemy(m_pGameObject);
					m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
					m_pCurrentTile = pNewTile;
					m_pCurrentTile->Revert();
				}
				else
				{
					m_pGameObject->SetActive(false);
				}
			}
			break;
		case dae::AiComponent::Type::Coily:
			break;
		case dae::AiComponent::Type::UggWrongway:
			break;
		default:
			break;
		}
	}
}

void dae::AiComponent::Render(glm::vec2)
{
	
}

void dae::AiComponent::Reset(TileComponent* pTile)
{
	m_pGameObject->SetActive(false);
	m_pGameObject->GetTransform()->SetPosition(pTile->GetPosition());
	m_pCurrentTile = pTile; 
}
