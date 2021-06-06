#include "AiComponent.h"
#include "Components.h"
#include "GameComponents.h"
#include "GameObject.h"
#include "TileManager.h"

dae::AiComponent::AiComponent(TileComponent* pStartTile, Type type, bool left)
	:m_pCurrentTile{pStartTile}
	, m_MoveTime{ 1.f }
	, m_Timer{0.f}
	, m_Type{type}
	, m_IsLeftOnTile{left}
{
	
}

void dae::AiComponent::Initialize()
{
	switch (m_Type)
	{
	case dae::AiComponent::Type::SlickSam:
		m_pCurrentTile->SetSlickSam(m_pGameObject);
		break;
	case dae::AiComponent::Type::Coily:
		m_pCoilyComponent = m_pGameObject->GetComponent<CoilyComponent>(ComponentType::CoilyComponent);
		m_pCurrentTile->SetCoily(m_pGameObject);
		break;
	case dae::AiComponent::Type::UggWrongway:
		break;
	}
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
		switch (m_Type)
		{
		case dae::AiComponent::Type::SlickSam:
			SlickSamUpdate();
			break;
		case dae::AiComponent::Type::Coily:
			CoilyUpdate();
			break;
		case dae::AiComponent::Type::UggWrongway:
			UggWrongwayUpdate();
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
	m_Timer = 0.f;
	m_pGameObject->SetActive(false);
	
	switch (m_Type)
	{
	case dae::AiComponent::Type::SlickSam:
		m_pCurrentTile->SetSlickSam(nullptr);
		m_pCurrentTile = pTile;
		m_pCurrentTile->SetSlickSam(m_pGameObject);
		m_pGameObject->GetTransform()->SetPosition(pTile->GetPosition());
		break;
	case dae::AiComponent::Type::Coily:
		m_pCurrentTile->SetCoily(nullptr);
		m_pCurrentTile = pTile;
		m_pCurrentTile->SetCoily(m_pGameObject);
		m_pGameObject->GetTransform()->SetPosition(pTile->GetPosition());
		break;
	case dae::AiComponent::Type::UggWrongway:
		if (m_IsLeftOnTile)
		{
			if (m_pCurrentTile->GetNeighbours().BottomLeft)
			{
				m_pCurrentTile->GetNeighbours().BottomLeft->SetUggWrongway(nullptr);
			}
			m_pGameObject->GetTransform()->SetPosition(pTile->GetSidePosition(true));
		}
		else
		{
			if (m_pCurrentTile->GetNeighbours().BottomRight)
			{
				m_pCurrentTile->GetNeighbours().BottomRight->SetUggWrongway(nullptr);
			}
			m_pGameObject->GetTransform()->SetPosition(pTile->GetSidePosition(false));
		}
		m_pCurrentTile = pTile;
		break;
	}
}

void dae::AiComponent::SlickSamUpdate()
{
	int choice = 0;
	TileComponent* pNewTile{ nullptr };
	//Randomize how Sam picks his tiles
	choice = std::rand() % 2;
	if (choice == 0)
	{
		pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
		if (pNewTile)
		{
			if (pNewTile->GetSlickSam())
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
			}
			m_pCurrentTile->SetSlickSam(nullptr);
			pNewTile->SetSlickSam(m_pGameObject);
			m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
			m_pCurrentTile = pNewTile;
			m_pCurrentTile->Revert();
		}
		else
		{
			m_pGameObject->SetActive(false);
		}
	}
	else if (choice == 1)
	{

		pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
		if (pNewTile)
		{
			if (pNewTile->GetSlickSam())
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
			}
			m_pCurrentTile->SetSlickSam(nullptr);
			pNewTile->SetSlickSam(m_pGameObject);
			m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
			m_pCurrentTile = pNewTile;
			m_pCurrentTile->Revert();
		}
		else
		{
			m_pGameObject->SetActive(false);
		}
	}
}

void dae::AiComponent::CoilyUpdate()
{
	int choice{};
	TileComponent* pNewTile{ nullptr };

	if (m_pCoilyComponent->IsEgg() && !m_pCoilyComponent->IsHatching())
	{
		choice = std::rand() % 2;
		if (choice == 0)
		{
			pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
			if (pNewTile)
			{
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pCoilyComponent->Hatch(m_pCurrentTile);
			}
		}
		else if (choice == 1)
		{
			pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
			if (pNewTile)
			{
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetPosition());
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pCoilyComponent->Hatch(m_pCurrentTile);
			}
		}
	}
	else if (m_pCoilyComponent->IsHatching())
	{
		m_Timer = 0.f;
	}
	else
	{
		glm::vec2 qBertPos{ m_pCoilyComponent->GetQbert()->GetGameObject()->GetTransform()->GetPosition() };
		glm::vec2 pos{ m_pGameObject->GetTransform()->GetPosition() };

		if (qBertPos.x < pos.x)
		{
			if (qBertPos.y < pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
			}
			else if (qBertPos.y > pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
			}
			else
			{
				pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
				if (!pNewTile)
					pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
			}
		}
		else if (qBertPos.x > pos.x)
		{
			if (qBertPos.y < pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
			}
			else if (qBertPos.y > pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
			}
			else
			{
				pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
				if (!pNewTile)
					pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
			}
		}
		else
		{
			if (qBertPos.y < pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
				if (!pNewTile)
					pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
			}
			else if (qBertPos.y > pos.y)
			{
				pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
				if (!pNewTile)
					pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
			}
		}

		if (pNewTile)
		{
			glm::vec2 newPos{ pNewTile->GetPosition() };
			newPos.y -= 30;
			m_pGameObject->GetTransform()->SetPosition(newPos);
			m_pCurrentTile->SetCoily(nullptr);
			pNewTile->SetCoily(m_pGameObject);
			m_pCurrentTile = pNewTile;
		}
		else
		{
			SpinningDisksComponent* pSpinningDiskComponent = m_pCurrentTile->GetSpinningDisk();
			if (pSpinningDiskComponent)
			{
				m_pCoilyComponent->GetQbert()->KilledCoily();
				m_pGameObject->SetActive(false);
			}
		}
	}
}

void dae::AiComponent::UggWrongwayUpdate()
{
	TileComponent* pNewTile{ nullptr };

	if (m_Previous)
	{
		if (m_IsLeftOnTile)
		{
			pNewTile = m_pCurrentTile->GetNeighbours().Right;
			if (pNewTile)
			{
				m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight, false);
				if (pNewTile->GetUggWrongway())
				{
					pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
					m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight, false);
				}
				if (m_pCurrentTile->GetNeighbours().BottomLeft)
				{
					m_pCurrentTile->GetNeighbours().BottomLeft->SetUggWrongway(nullptr);
				}
				if (pNewTile->GetNeighbours().BottomLeft)
					pNewTile->GetNeighbours().BottomLeft->SetUggWrongway(m_pGameObject);
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetSidePosition(m_IsLeftOnTile));
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pGameObject->SetActive(false);
			}
		}
		else
		{
			pNewTile = m_pCurrentTile->GetNeighbours().Left;
			if (pNewTile)
			{
				m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft, false);
				if (pNewTile->GetUggWrongway())
				{
					pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
					m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopLeft, false);
				}
				if (m_pCurrentTile->GetNeighbours().BottomRight)
				{
					m_pCurrentTile->GetNeighbours().BottomRight->SetUggWrongway(nullptr);
				}
				if (pNewTile->GetNeighbours().BottomRight)
					pNewTile->GetNeighbours().BottomRight->SetUggWrongway(m_pGameObject);
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetSidePosition(m_IsLeftOnTile));
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pGameObject->SetActive(false);
			}
		}
		m_Previous = !m_Previous;
	}
	else
	{
		if (m_IsLeftOnTile)
		{
			pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
			if (pNewTile)
			{
				m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight, false);
				if (pNewTile->GetUggWrongway())
				{
					pNewTile = m_pCurrentTile->GetNeighbours().Right;
					m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight, false);
				}
				if (m_pCurrentTile->GetNeighbours().BottomLeft)
				{
					m_pCurrentTile->GetNeighbours().BottomLeft->SetUggWrongway(nullptr);
				}
				if (pNewTile->GetNeighbours().BottomLeft)
					pNewTile->GetNeighbours().BottomLeft->SetUggWrongway(m_pGameObject);
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetSidePosition(m_IsLeftOnTile));
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pGameObject->SetActive(false);
			}
		}
		else
		{
			pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
			if (pNewTile)
			{
				m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopLeft, false);
				if (pNewTile->GetUggWrongway())
				{
					pNewTile = m_pCurrentTile->GetNeighbours().Left;
					m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft, false);
				}
				if (m_pCurrentTile->GetNeighbours().BottomRight)
				{
					m_pCurrentTile->GetNeighbours().BottomRight->SetUggWrongway(nullptr);
				}
				if (pNewTile->GetNeighbours().BottomRight)
					pNewTile->GetNeighbours().BottomRight->SetUggWrongway(m_pGameObject);
				m_pGameObject->GetTransform()->SetPosition(pNewTile->GetSidePosition(m_IsLeftOnTile));
				m_pCurrentTile = pNewTile;
			}
			else
			{
				m_pGameObject->SetActive(false);
			}
		}
		m_Previous = !m_Previous;
	}
}

void dae::AiComponent::SetCoilyComponent(CoilyComponent* pCoilyComponent)
{
	m_pCoilyComponent = pCoilyComponent;
}
