#include "QBertComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "TileComponent.h"
#include "Observers.h"
#include "AiComponent.h"
#include "ResourceManager.h"

dae::QBertComponent::QBertComponent()
	:m_JumpTime{0.f}
	, m_Timer{0.f}
{
	
}

void dae::QBertComponent::Move(MoveDirections moveDirection)
{
	if (m_Timer < m_JumpTime)
	{
		return; 
	}

	TileComponent* pNewTile{};
	switch (moveDirection)
	{
	case dae::QBertComponent::MoveDirections::TopRight:
		pNewTile = m_pCurrentTile->GetNeighbours().TopRight;
		if (pNewTile)
		{
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight);
		}
		break;
	case dae::QBertComponent::MoveDirections::BottomRight:
		pNewTile = m_pCurrentTile->GetNeighbours().BottomRight;
		if (pNewTile)
		{
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
			m_pCurrentTile = pNewTile;
			glm::vec2 newTilePos{ pNewTile->GetPosition() };
			m_pGameObject->GetTransform()->SetPosition(newTilePos);
			m_pCurrentTile->JumpOn(m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent));
			m_pGameObject->GetComponent<SpriteSheetComponent>(ComponentType::SpriteSheetComponent)->SetSpriteState(SpriteSheetComponent::SpriteState::TopLeft);
		}
		break;
	}

	m_Timer = 0.f; 
}

void dae::QBertComponent::Reset(TileComponent* pStartTile)
{
	m_pGameObject->GetTransform()->SetPosition(pStartTile->GetPosition());
	m_pCurrentTile = pStartTile; 
}

void dae::QBertComponent::Initialize(TileComponent* pStartTile, Scene* pScene)
{
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

	spriteComponent->SetSprite("Qbert.png", spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
	spriteComponent->SetScale(2.f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	//TextComponent
	GameObject* pGameObject = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto textComp = new TextComponent();
	textComp->SetFont(font);
	textComp->SetText("Points: ");
	pGameObject->AddComponent(ComponentType::TextComponent, textComp);
	pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(0.f, 64.f);

	pGameObject = new GameObject(); 
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComp = new TextComponent();
	textComp->SetFont(font);
	textComp->SetText("0");
	pGameObject->AddComponent(ComponentType::TextComponent, textComp);
	pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(80.f, 64.f);

	auto pointComp = new PointComponent();
	m_pGameObject->AddComponent(ComponentType::PointComponent, pointComp);

	//SubjectComponent
	auto subjectComp = new SubjectComponent();
	m_pGameObject->AddComponent(ComponentType::SubjectComponent, subjectComp);

	//Observers
	auto pointObserver = new PointObserver(pointComp, textComp);
	subjectComp->AddObserver(pointObserver);

	glm::vec2 tilePos{ pStartTile->GetPosition() };
	m_pGameObject->GetTransform()->SetPosition(tilePos);



	MoveUpRightCommand* pMoveUpRight{ new MoveUpRightCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_UP, InputType::KeyDown }, pMoveUpRight);

	MoveDownRightCommand* pMoveDownRight{ new MoveDownRightCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_RIGHT, InputType::KeyDown }, pMoveDownRight);

	MoveDownLeftCommand* pMoveDownLeft{ new MoveDownLeftCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_DOWN, InputType::KeyDown }, pMoveDownLeft);

	MoveUpLeftCommand* pMoveUpLeft{ new MoveUpLeftCommand(this) };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_LEFT, InputType::KeyDown }, pMoveUpLeft);

	for (int i = 0; i < m_MaxHearts; i++)
	{
		GameObject* pObject = new GameObject();
		TextureComponent* pTexture = new TextureComponent();
		pTexture->SetTexture("Heart.png");
		pObject->AddComponent(ComponentType::TextureComponent, pTexture);
		pObject->GetTransform()->SetPosition(i * 32.f, 32.f);
		pScene->Add(pObject, 1);
		m_pHearts.push_back(pObject);
	}
}

void dae::QBertComponent::Update(float elapsedSec)
{
	m_Timer += elapsedSec;
	GameObject* pEnemy{ m_pCurrentTile->GetEnemy() };
	if (pEnemy && pEnemy->IsActive())
	{
		switch (pEnemy->GetComponent<AiComponent>(ComponentType::AiComponent)->GetType())
		{
		case AiComponent::Type::SlickSam:
			m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::CatchingSlickSam);
			pEnemy->SetActive(false); 
			break; 
		default:
			break;
		}
	}
}

void dae::QBertComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position); 
}
