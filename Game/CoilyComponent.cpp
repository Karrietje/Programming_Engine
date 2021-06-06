#include <Windows.h>
#include "CoilyComponent.h"
#include "GameObject.h"
#include "GameComponents.h"	
#include "Components.h"
#include "Scene.h"

dae::CoilyComponent::CoilyComponent()
	: m_IsEgg{true}
	, m_IsHatching{false}
	, m_Timer{0.f}
	, m_HatchTimer{2.f}
	, m_pHatchTile{nullptr}
	, m_pQbert{nullptr}
	, m_pEggSpriteSheet{nullptr}
	, m_pCoilySpriteSheet{nullptr}
{
}

void dae::CoilyComponent::Initialize(dae::TileComponent* pStartTile, Scene* pScene, QBertComponent* pQbert)
{
	m_pQbert = pQbert;
	m_pEggSpriteSheet = new GameObject();

	SpriteSheetComponent* pSpriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 3;
	spriteInfo.colums = 2;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(2, 2);

	pSpriteComponent->SetSprite("Slimes.png", spriteInfo);
	pSpriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft);
	pSpriteComponent->SetScale(2.f);

	m_pEggSpriteSheet->AddComponent(ComponentType::SpriteSheetComponent, pSpriteComponent);
	m_pGameObject->AddChild(m_pEggSpriteSheet);
	pScene->Add(m_pEggSpriteSheet, 2);

	m_pCoilySpriteSheet = new GameObject();

	pSpriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo1;
	spriteInfo1.rows = 4;
	spriteInfo1.colums = 2;

	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::TopRight] = std::make_pair(0, 2);
	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::TopLeft] = std::make_pair(1, 2);
	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(2, 2);
	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(3, 2);

	pSpriteComponent->SetSprite("Coily.png", spriteInfo1);
	pSpriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft);
	pSpriteComponent->SetScale(2.f);

	m_pCoilySpriteSheet->AddComponent(ComponentType::SpriteSheetComponent, pSpriteComponent);
	m_pGameObject->AddChild(m_pCoilySpriteSheet);
	pScene->Add(m_pCoilySpriteSheet, 2);
	m_pCoilySpriteSheet->SetActive(false);

	AiComponent* pAiComponent = new AiComponent(pStartTile, AiComponent::Type::Coily);
	m_pGameObject->AddComponent(ComponentType::AiComponent, pAiComponent);
	pAiComponent->Initialize();
	pAiComponent->SetCoilyComponent(this);
	m_pGameObject->GetTransform()->SetPosition(pStartTile->GetPosition());
}

void dae::CoilyComponent::Update(float elapsedSec)
{
	if (m_IsHatching && m_IsEgg)
	{
		m_Timer += elapsedSec;

		if (m_Timer >= m_HatchTimer)
		{
			m_IsHatching = false;
			m_IsEgg = false;
			m_pEggSpriteSheet->SetActive(false);
			m_pCoilySpriteSheet->SetActive(true);

			glm::vec2 pos{ m_pHatchTile->GetPosition() };
			pos.y -= 30;
			m_pGameObject->GetTransform()->SetPosition(pos);
		}
	}
}

void dae::CoilyComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}

bool dae::CoilyComponent::IsEgg() const
{
	return m_IsEgg;
}

bool dae::CoilyComponent::IsHatching() const
{
	return m_IsHatching;
}

void dae::CoilyComponent::Hatch(TileComponent* pHatchTile)
{
	m_IsHatching = true;
	m_pHatchTile = pHatchTile;
}

dae::QBertComponent* dae::CoilyComponent::GetQbert() const
{
	return m_pQbert;
}

void dae::CoilyComponent::Reset(TileComponent* pTile)
{
	m_IsEgg = true;
	m_IsHatching = false;
	m_Timer = 0.f;

	m_pEggSpriteSheet->SetActive(true);
	m_pCoilySpriteSheet->SetActive(false);

	m_pGameObject->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(pTile);
}
