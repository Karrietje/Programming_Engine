#include "SpinningDisksComponent.h"
#include "GameComponents.h"
#include "Components.h"
#include "GameObject.h"
#include <Windows.h>

dae::SpinningDisksComponent::SpinningDisksComponent(TileComponent* pReturnTile)
	: m_StartReturn{false}
	, m_Timer{0.f}
	, m_ReturnTimer{1.5f}
	, m_pReturnTile(pReturnTile)
{
}

void dae::SpinningDisksComponent::Initialize()
{
	auto spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 1;
	spriteInfo.colums = 5;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(0, 4);

	spriteComponent->SetSprite("Disc.png", spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
	spriteComponent->SetScale(2.f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);
}

void dae::SpinningDisksComponent::Update(float elapsedSec)
{
	if (m_StartReturn)
	{
		m_Timer += elapsedSec;

		if (m_Timer >= m_ReturnTimer)
		{
			m_pQbert->GetGameObject()->GetTransform()->SetPosition(m_pReturnTile->GetPosition());
			m_pQbert->SetCurrentTile(m_pReturnTile);
			m_pGameObject->SetActive(false);
			m_pQbert->m_CanMove = true;
		}
	}
}

void dae::SpinningDisksComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}

void dae::SpinningDisksComponent::JumpOn(QBertComponent* pQbert)
{
	m_StartReturn = true;
	m_pQbert = pQbert;
}

glm::vec2 dae::SpinningDisksComponent::GetPosition() const
{
	glm::vec2 position{ m_pGameObject->GetTransform()->GetPosition() };
	position.x += 10;
	position.y -= 10;
	return position;
}
