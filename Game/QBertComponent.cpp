#include <Windows.h>
#include "QBertComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "GameComponents.h"
#include "Observers.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <string>
#include "Audio.h"
#include "AudioLocator.h"

using namespace dae;
dae::QBertComponent::QBertComponent()
	: m_CanMove{true}
	, m_JumpTime{1.f}
	, m_Timer{0.f}
	, m_pCurrentTile{nullptr}
	, m_pGameManagerComponent{nullptr}
{
	
}

void dae::QBertComponent::Move(MoveDirections moveDirection)
{
	if ((m_Timer < m_JumpTime) || !m_CanMove)
	{
		return; 
	}

	TileComponent* pNewTile{};
	SpinningDisksComponent* pSpinningDisk{};
	switch (moveDirection)
	{
	case dae::QBertComponent::MoveDirections::TopRight:
		pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
		if (pNewTile)
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight);
			break;
		}
		pSpinningDisk = m_pCurrentTile->GetSpinningDisk();
		if (pSpinningDisk && pSpinningDisk->GetGameObject()->IsActive())
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			glm::vec2 newPos{ pSpinningDisk->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newPos);
			pSpinningDisk->JumpOn(this);
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight);
			m_CanMove = false;
		}
		break;
	case dae::QBertComponent::MoveDirections::BottomRight:
		pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
		if (pNewTile)
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
		}
		break;
	case dae::QBertComponent::MoveDirections::BottomLeft:
		pNewTile = m_pCurrentTile->GetNeighbours().BottomLeft;
		if (pNewTile)
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft);
		}
		break;
	case dae::QBertComponent::MoveDirections::TopLeft:
		pNewTile = m_pCurrentTile->GetNeighbours().TopLeft;
		if (pNewTile)
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopLeft);
			break;
		}
		pSpinningDisk = m_pCurrentTile->GetSpinningDisk();
		if (pSpinningDisk && pSpinningDisk->GetGameObject()->IsActive())
		{
			AudioLocator::GetAudioSystem()->PlaySoundW(2);
			glm::vec2 newPos{ pSpinningDisk->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newPos);
			pSpinningDisk->JumpOn(this);
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopLeft);
			m_CanMove = false;
		}
		break;
	}

	m_Timer = 0.f; 
}

void dae::QBertComponent::Reset(TileComponent* pStartTile)
{
	m_pGameObject->GetTransform()->SetPosition(pStartTile->GetPosition());
	m_pCurrentTile = pStartTile; 
	m_CanMove = true;
}

void dae::QBertComponent::KilledCoily()
{
	m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::KillByFlyingDisc);
}

void dae::QBertComponent::SetCurrentTile(TileComponent* pTile)
{
	m_pCurrentTile = pTile;
}

void dae::QBertComponent::Initialize(TileComponent* pStartTile, Scene* pScene, int player, GameManagerComponent* pGameManagerComponent)
{
	m_pGameManagerComponent = pGameManagerComponent;
	m_pCurrentTile = pStartTile;

	auto spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 4;
	spriteInfo.colums = 2;

	//On row 0, there are 2 sprites
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::TopRight] = std::make_pair(0, 2);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::TopLeft] = std::make_pair(1, 2);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(2, 2);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(3, 2);

	std::string spriteName{ "Qbert" + std::to_string(player) + ".png" };
	spriteComponent->SetSprite(spriteName, spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
	spriteComponent->SetScale(2.f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	glm::vec2 tilePos{ pStartTile->GetPosition() };
	m_pGameObject->GetTransform()->SetPosition(tilePos);

	MoveUpRightCommand* pMoveUpRight{ new MoveUpRightCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ (player == 0 ? SDLK_w : SDLK_UP), VK_PAD_DPAD_UP, InputType::KeyDown, player }, pMoveUpRight);

	MoveDownRightCommand* pMoveDownRight{ new MoveDownRightCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ (player == 0 ? SDLK_d : SDLK_RIGHT), VK_PAD_DPAD_RIGHT, InputType::KeyDown, player }, pMoveDownRight);

	MoveDownLeftCommand* pMoveDownLeft{ new MoveDownLeftCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ (player == 0 ? SDLK_s : SDLK_DOWN),  VK_PAD_DPAD_DOWN, InputType::KeyDown, player }, pMoveDownLeft);

	MoveUpLeftCommand* pMoveUpLeft{ new MoveUpLeftCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ (player == 0 ? SDLK_a : SDLK_LEFT), VK_PAD_DPAD_LEFT, InputType::KeyDown, player }, pMoveUpLeft);

	for (int i = 0; i < m_MaxHearts; i++)
	{
		GameObject* pObject = new GameObject();
		TextureComponent* pTexture = new TextureComponent();
		pTexture->SetTexture("Heart.png");
		pObject->AddComponent(ComponentType::TextureComponent, pTexture);
		if (player == 0)
		{
			pObject->GetTransform()->SetPosition(10 + (i * 32.f), 32.f);
		}
		else if (player == 1)
		{
			pObject->GetTransform()->SetPosition(600 - (i * 32.f), 32.f);
		}
		pScene->Add(pObject, 1);
		m_pHearts.push_back(pObject);
	}

	auto healthComp = new HealthComponent(m_MaxHearts);
	m_pGameObject->AddComponent(ComponentType::HealthComponent, healthComp);

	//SubjectComponent
	auto subjectComp = new SubjectComponent();
	m_pGameObject->AddComponent(ComponentType::SubjectComponent, subjectComp);

	//Observers
	auto healthObserver = new HealthObserver(healthComp, m_pHearts);
	subjectComp->AddObserver(healthObserver);
}

void dae::QBertComponent::Update(float elapsedSec)
{
	m_Timer += elapsedSec;
	GameObject* pEnemy{ m_pCurrentTile->GetSlickSam() };
	if (pEnemy && pEnemy->IsActive())
	{
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::CatchingSlickSam);

		pEnemy->SetActive(false);
	}
	pEnemy = m_pCurrentTile->GetUggWrongway();
	if (pEnemy && pEnemy->IsActive())
	{
		AudioLocator::GetAudioSystem()->PlaySoundW(1);
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Kill);
		m_pGameManagerComponent->SoftReset();
	}
	pEnemy = m_pCurrentTile->GetCoily();
	if (pEnemy && pEnemy->IsActive())
	{
		AudioLocator::GetAudioSystem()->PlaySoundW(1);
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Kill);
		m_pGameManagerComponent->SoftReset();
	}
}

void dae::QBertComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position); 
}

int dae::QBertComponent::GetLives() const
{
	return m_pGameObject->GetComponent<HealthComponent>(ComponentType::HealthComponent)->GetHealth();
}
