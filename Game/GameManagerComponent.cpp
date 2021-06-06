#include <Windows.h>
#include <iostream>
#include "GameManagerComponent.h"
#include "SceneManager.h"
#include "GameComponents.h"
#include "Components.h"
#include "GameObject.h"
#include "Scene.h"
#include "AudioLocator.h"
#include "TileManager.h"
#include "Audio.h"
#include "ResourceManager.h"
#include "Observers.h"

using namespace dae; 
dae::GameManagerComponent::GameManagerComponent(Scene* pScene, GameMode gameMode)
	:m_SlickSpawnTime{3.f}
	,m_SamSpawnTime{6.f}
	, m_UggSpawnTime{4.5f}
	, m_WrongWaySpawnTime{7.5f}
	, m_CoilySpawnTime{10.f}
	, m_GameTime{ 0.f }
	, m_SpawnSlick{true}
	, m_SpawnSam{true}
	, m_SpawnUgg{true}
	, m_SpawnWrongWay{true}
	, m_SpawnCoily{true}
	, m_Level{0}
	, m_MaxLevel{3}
	, m_pScene{pScene}
{
	
	auto go = new GameObject();

	auto textureComp = new TextureComponent();
	textureComp->SetTexture("background.jpg");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	pScene->Add(go, 0);

	/*go = new GameObject();*/

	/*textureComp = new TextureComponent();
	textureComp->SetTexture("logo.png");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	go->GetTransform()->SetPosition(216, 180);

	scene.Add(go);*/

	/*go = new GameObject();

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComp = new TextComponent();
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");
	go->AddComponent(ComponentType::TextComponent, textComp);

	go->GetTransform()->SetPosition(80, 20);

	scene.Add(go);*/

	/*go = new GameObject();

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FPSComp = new FPSComponent();
	FPSComp->SetFont(font);
	go->AddComponent(ComponentType::FPSComponent, FPSComp);

	go->GetTransform()->SetPosition(10, 10);

	scene.Add(go);*/

	AudioLocator::GetAudioSystem()->AddSoundEffect(0, "QbertDead.wav");

	TileManager::GetInstance().CreateLevels("Levels/Level1.txt", pScene, m_MaxLevel);
	TileManager::GetInstance().SetGameManager(this);

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
	pGameObject->AddComponent(ComponentType::PointComponent, pointComp);

	GameObject* pQbert{ nullptr };
	QBertComponent* pQbertComp{ nullptr };
	PointObserver* pPointObserver{ nullptr };
	switch (gameMode)
	{
	case dae::GameManagerComponent::GameMode::Single:
		pQbert = new GameObject();
		pQbertComp = new QBertComponent();
		pQbert->AddComponent(ComponentType::QBertComponent, pQbertComp);
		pQbertComp->Initialize(TileManager::GetInstance().GetTiles(m_Level)[0][0], pScene, 0, this);
		pScene->Add(pQbert, 2);

		pPointObserver = new PointObserver(pointComp, textComp);
		pQbert->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->AddObserver(pPointObserver);
		m_pQBerts.push_back(pQbert);
		break;
	case dae::GameManagerComponent::GameMode::Coop:
		pQbert = new GameObject();
		pQbertComp = new QBertComponent();
		pQbert->AddComponent(ComponentType::QBertComponent, pQbertComp);
		pQbertComp->Initialize(TileManager::GetInstance().GetTiles(m_Level)[6][0], pScene, 0, this);
		pScene->Add(pQbert, 2);

		pPointObserver = new PointObserver(pointComp, textComp);
		pQbert->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->AddObserver(pPointObserver);
		m_pQBerts.push_back(pQbert);

		pQbert = new GameObject();
		pQbertComp = new QBertComponent();
		pQbert->AddComponent(ComponentType::QBertComponent, pQbertComp);
		pQbertComp->Initialize(TileManager::GetInstance().GetTiles(m_Level)[6][6], pScene, 1, this);
		pScene->Add(pQbert, 2);

		pPointObserver = new PointObserver(pointComp, textComp);
		pQbert->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->AddObserver(pPointObserver);
		m_pQBerts.push_back(pQbert);
		break;
	}

	m_pSlick = new GameObject();

	m_pSlick->GetTransform()->SetPosition(TileManager::GetInstance().GetTiles(m_Level)[1][0]->GetPosition());
	auto spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 2;
	spriteInfo.colums = 4;

	//On row 0, there are 4 sprites
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(0, 4);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(1, 4);

	spriteComponent->SetSprite("Slick.png", spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
	spriteComponent->SetScale(2.f);

	m_pSlick->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	AiComponent* pAiComponent = new AiComponent(TileManager::GetInstance().GetTiles(m_Level)[1][0], AiComponent::Type::SlickSam);
	m_pSlick->AddComponent(ComponentType::AiComponent, pAiComponent);
	pAiComponent->Initialize();

	m_pSlick->SetActive(false);
	pScene->Add(m_pSlick, 2);


	m_pSam = new GameObject();

	m_pSam->GetTransform()->SetPosition(TileManager::GetInstance().GetTiles(m_Level)[1][1]->GetPosition());
	spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo1;
	spriteInfo1.rows = 2;
	spriteInfo1.colums = 4;

	//On row 0, there are 4 sprites
	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(0, 4);
	spriteInfo1.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(1, 4);

	spriteComponent->SetSprite("Sam.png", spriteInfo1);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomRight);
	spriteComponent->SetScale(2.f);

	m_pSam->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	AiComponent* pAiComponent1 = new AiComponent(TileManager::GetInstance().GetTiles(m_Level)[1][1], AiComponent::Type::SlickSam);
	m_pSam->AddComponent(ComponentType::AiComponent, pAiComponent1);
	pAiComponent1->Initialize(); 
	m_pSam->SetActive(false);
	pScene->Add(m_pSam, 2);

	m_pWrongWay = new GameObject();

	m_pWrongWay->GetTransform()->SetPosition(TileManager::GetInstance().GetTiles(m_Level)[6][0]->GetSidePosition(true));
	spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo2;
	spriteInfo2.rows = 2;
	spriteInfo2.colums = 4;

	//On row 0, there are 4 sprites
	spriteInfo2.SheetInfo[SpriteSheetComponent::SpriteState::BottomRight] = std::make_pair(0, 4);
	spriteInfo2.SheetInfo[SpriteSheetComponent::SpriteState::TopRight] = std::make_pair(1, 4);

	spriteComponent->SetSprite("Wrongway.png", spriteInfo2);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::TopRight);
	spriteComponent->SetScale(2.f);

	m_pWrongWay->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	pAiComponent1 = new AiComponent(TileManager::GetInstance().GetTiles(m_Level)[6][0], AiComponent::Type::UggWrongway, true);
	m_pWrongWay->AddComponent(ComponentType::AiComponent, pAiComponent1);
	pAiComponent1->Initialize();
	m_pWrongWay->SetActive(false);
	pScene->Add(m_pWrongWay, 2);

	m_pUgg = new GameObject();

	m_pUgg->GetTransform()->SetPosition(TileManager::GetInstance().GetTiles(m_Level)[6][6]->GetSidePosition(false));
	spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo3;
	spriteInfo3.rows = 2;
	spriteInfo3.colums = 4;

	//On row 0, there are 4 sprites
	spriteInfo3.SheetInfo[SpriteSheetComponent::SpriteState::BottomLeft] = std::make_pair(0, 4);
	spriteInfo3.SheetInfo[SpriteSheetComponent::SpriteState::TopLeft] = std::make_pair(1, 4);

	spriteComponent->SetSprite("Ugg.png", spriteInfo3);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::BottomLeft);
	spriteComponent->SetScale(2.f);

	m_pUgg->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	pAiComponent1 = new AiComponent(TileManager::GetInstance().GetTiles(m_Level)[6][6], AiComponent::Type::UggWrongway, false);
	m_pUgg->AddComponent(ComponentType::AiComponent, pAiComponent1);
	pAiComponent1->Initialize();
	m_pUgg->SetActive(false);
	pScene->Add(m_pUgg, 2);

	m_pCoily = new GameObject();

	CoilyComponent* pCoilyComponent = new CoilyComponent();
	m_pCoily->AddComponent(ComponentType::CoilyComponent, pCoilyComponent);
	pCoilyComponent->Initialize(TileManager::GetInstance().GetTiles(m_Level)[1][0], pScene, pQbertComp);
	m_pCoily->SetActive(false);

	pScene->Add(m_pCoily, 2);

	//go = new GameObject("Player 1");

	//textureComp = new TextureComponent();
	//textureComp->SetTexture("Qbert.png");
	//go->AddComponent(ComponentType::TextureComponent, textureComp);

	////Components
	//auto healthComp = new HealthComponent(3);
	//go->AddComponent(ComponentType::HealthComponent, healthComp);

	//auto pointComp = new PointComponent();
	//go->AddComponent(ComponentType::PointComponent, pointComp);

	////SubjectComponent
	//auto subjectComp = new SubjectComponent();
	//go->AddComponent(ComponentType::SubjectComponent, subjectComp);

	////Observers
	//auto pointObserver = new PointObserver(pointComp);
	//subjectComp->AddObserver(pointObserver);

	//auto healthObserver = new HealthObserver(healthComp);
	//subjectComp->AddObserver(healthObserver);

	////Button input
	//KillCommand* pKill{ new KillCommand(subjectComp) };
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_A, InputType::KeyDown }, pKill);

	//ColorChangeCommand* pColorChange{ new ColorChangeCommand {subjectComp} };
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_B, InputType::KeyDown }, pColorChange);

	//KillByFlyingDiscCommand* pKillByFlyingDisc{ new KillByFlyingDiscCommand {subjectComp} };
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_Y, InputType::KeyDown }, pKillByFlyingDisc);

	//RemainingDiscCommand* pRemainingDisc{ new RemainingDiscCommand {subjectComp} };
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_X, InputType::KeyDown }, pRemainingDisc);

	//CatchingCommand* pCatching{ new CatchingCommand {subjectComp} };
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_RSHOULDER, InputType::KeyDown }, pCatching);

	//scene.Add(go);

	////Player 2

	//go = std::make_shared<GameObject>("Player 2");

	//textureComp = std::make_shared<TextureComponent>();
	//textureComp->SetTexture("Qbert.png");
	//go->AddComponent(ComponentType::TextureComponent, textureComp);

	////Components
	//healthComp = std::make_shared<HealthComponent>(3);
	//go->AddComponent(ComponentType::HealthComponent, healthComp);

	//pointComp = std::make_shared<PointComponent>();
	//go->AddComponent(ComponentType::PointComponent, pointComp);

	////SubjectComponent
	//subjectComp = std::make_shared<SubjectComponent>();
	//go->AddComponent(ComponentType::SubjectComponent, subjectComp);

	////Observers
	//pointObserver = std::make_shared<PointObserver>(pointComp);
	//subjectComp->AddObserver(pointObserver);

	//healthObserver = std::make_shared<HealthObserver>(healthComp);
	//subjectComp->AddObserver(healthObserver);

	////Button input
	//pKill = std::make_shared<KillCommand>(subjectComp);
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_DOWN, InputType::KeyDown }, pKill);

	//pColorChange = std::make_shared<ColorChangeCommand>(subjectComp);
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_RIGHT, InputType::KeyDown }, pColorChange);

	//pKillByFlyingDisc = std::make_shared<KillByFlyingDiscCommand>(subjectComp);
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_UP, InputType::KeyDown }, pKillByFlyingDisc);

	//pRemainingDisc = std::make_shared<RemainingDiscCommand>(subjectComp);
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_LEFT, InputType::KeyDown }, pRemainingDisc);

	//pCatching = std::make_shared<CatchingCommand>(subjectComp);
	//InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_LSHOULDER, InputType::KeyDown }, pCatching);

	//scene.Add(go);
}

void dae::GameManagerComponent::Update(float elapsedSec)
{
	m_GameTime += elapsedSec;
	if (m_GameTime >= m_SlickSpawnTime && !m_pSlick->IsActive() && m_SpawnSlick)
	{
		m_pSlick->SetActive(true); 
		m_SpawnSlick = false; 
	}

	if (m_GameTime >= m_SamSpawnTime && !m_pSam->IsActive() && m_SpawnSam)
	{
		m_pSam->SetActive(true);
		m_SpawnSam = false; 
	}

	if (m_GameTime >= m_UggSpawnTime && !m_pUgg->IsActive() && m_SpawnUgg)
	{
		m_pUgg->SetActive(true);
		m_SpawnUgg = false;
	}

	if (m_GameTime >= m_WrongWaySpawnTime && !m_pWrongWay->IsActive() && m_SpawnWrongWay)
	{
		m_pWrongWay->SetActive(true);
		m_SpawnWrongWay = false;
	}

	if (m_GameTime >= m_CoilySpawnTime && !m_pCoily->IsActive() && m_SpawnCoily)
	{
		m_pCoily->SetActive(true);
		m_SpawnCoily = false;
	}

	size_t playersDead{ 0 };
	for (GameObject* pQbert : m_pQBerts)
	{
		if (pQbert->GetComponent<QBertComponent>(ComponentType::QBertComponent)->GetLives() == 0)
			playersDead++;
	}

	if (playersDead == m_pQBerts.size())
	{
		SceneManager::GetInstance().SetCurrentScene("EndScene");
	}
}

void dae::GameManagerComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position); 
}

void dae::GameManagerComponent::SoftReset()
{
	m_GameTime = 0.f;
	m_SpawnSam = true;
	m_SpawnSlick = true;
	m_SpawnUgg = true;
	m_SpawnWrongWay = true;
	m_SpawnCoily = true;

	m_pSlick->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][0]);
	m_pSam->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][1]);
	m_pUgg->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][6]);
	m_pWrongWay->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][0]);
	m_pCoily->GetComponent<CoilyComponent>(ComponentType::CoilyComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][0]);
}

void dae::GameManagerComponent::NextLevel()
{
	m_Level++; 
	if (m_Level ==  m_MaxLevel)
	{
		std::cout << "Game Won! Change scene!\n"; 
		//SceneManager::GetInstance().SetCurrentScene("EndScene");
	}
	else
	{
		m_GameTime = 0.f;
		m_SpawnSam = true;
		m_SpawnSlick = true;
		m_SpawnUgg = true;
		m_SpawnWrongWay = true;
		m_SpawnCoily = true;

		if (m_pQBerts.size() == 1)
		{
			m_pQBerts[0]->GetComponent<QBertComponent>(ComponentType::QBertComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[0][0]);
		}
		else if (m_pQBerts.size() == 2)
		{
			m_pQBerts[0]->GetComponent<QBertComponent>(ComponentType::QBertComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][0]);
			m_pQBerts[1]->GetComponent<QBertComponent>(ComponentType::QBertComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][6]);
		}
		m_pSlick->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][0]);
		m_pSam->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][1]);
		m_pUgg->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][6]);
		m_pWrongWay->GetComponent<AiComponent>(ComponentType::AiComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[6][0]);
		m_pCoily->GetComponent<CoilyComponent>(ComponentType::CoilyComponent)->Reset(TileManager::GetInstance().GetTiles(m_Level)[1][0]);

		for (const std::vector<TileComponent*>& pTiles : TileManager::GetInstance().GetTiles(m_Level - 1))
		{
			for (TileComponent* pTile : pTiles)
			{
				pTile->GetGameObject()->SetActive(false);
			}
		}

		for (const std::vector<TileComponent*>& pTiles : TileManager::GetInstance().GetTiles(m_Level))
		{
			for (TileComponent* pTile : pTiles)
			{
				pTile->GetGameObject()->SetActive(true);
			}
		}

		for (const SpinningDisksComponent* pDisk : TileManager::GetInstance().GetSpinningDisks(m_Level - 1))
		{
			pDisk->GetGameObject()->SetActive(false);
		}

		for (const SpinningDisksComponent* pDisk : TileManager::GetInstance().GetSpinningDisks(m_Level))
		{
			pDisk->GetGameObject()->SetActive(true);
		}
	}
}
