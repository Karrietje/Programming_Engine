#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"
#include "HealthObserver.h"
#include "Command.h"
#include "PointComponent.h"
#include "PointObserver.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();

	auto textureComp = std::make_shared<TextureComponent>();
	textureComp->SetTexture("background.jpg");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	scene.Add(go);

	go = std::make_shared<GameObject>();

	textureComp = std::make_shared<TextureComponent>();
	textureComp->SetTexture("logo.png");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	go->GetTransform()->SetPosition(216, 180);

	scene.Add(go);

	go = std::make_shared<GameObject>();

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComp = std::make_shared<TextComponent>();
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");
	go->AddComponent(ComponentType::TextComponent, textComp);

	go->GetTransform()->SetPosition(80, 20);

	scene.Add(go);

	go = std::make_shared<GameObject>();

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FPSComp = std::make_shared<FPSComponent>();
	FPSComp->SetFont(font);
	go->AddComponent(ComponentType::FPSComponent, FPSComp);

	go->GetTransform()->SetPosition(10, 10);

	scene.Add(go);


	go = std::make_shared<GameObject>("Player 1");

	textureComp = std::make_shared<TextureComponent>();
	textureComp->SetTexture("Qbert.png");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	//Components
	auto healthComp = std::make_shared<HealthComponent>(3);
	go->AddComponent(ComponentType::HealthComponent, healthComp);
	
	auto pointComp = std::make_shared<PointComponent>();
	go->AddComponent(ComponentType::PointComponent, pointComp);
	
	//SubjectComponent
	auto subjectComp = std::make_shared<SubjectComponent>();
	go->AddComponent(ComponentType::SubjectComponent, subjectComp); 

	//Observers
	auto pointObserver = std::make_shared<PointObserver>(pointComp);
	subjectComp->AddObserver(pointObserver);
	
	auto healthObserver = std::make_shared<HealthObserver>(healthComp);
	subjectComp->AddObserver(healthObserver);

	//Button input
	std::shared_ptr<KillCommand> pKill{ new KillCommand(subjectComp) };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_A, InputType::KeyDown }, pKill);

	std::shared_ptr<ColorChangeCommand> pColorChange{ new ColorChangeCommand {subjectComp} };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_B, InputType::KeyDown }, pColorChange);

	std::shared_ptr<KillByFlyingDiscCommand> pKillByFlyingDisc{ new KillByFlyingDiscCommand {subjectComp} };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_Y, InputType::KeyDown }, pKillByFlyingDisc);

	std::shared_ptr<RemainingDiscCommand> pRemainingDisc{ new RemainingDiscCommand {subjectComp} };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_X, InputType::KeyDown }, pRemainingDisc);

	std::shared_ptr<CatchingCommand> pCatching{ new CatchingCommand {subjectComp} };
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_RSHOULDER, InputType::KeyDown }, pCatching);

	scene.Add(go);

	//Player 2

	go = std::make_shared<GameObject>("Player 2");

	textureComp = std::make_shared<TextureComponent>();
	textureComp->SetTexture("Qbert.png");
	go->AddComponent(ComponentType::TextureComponent, textureComp);

	//Components
	healthComp = std::make_shared<HealthComponent>(3);
	go->AddComponent(ComponentType::HealthComponent, healthComp);

	pointComp = std::make_shared<PointComponent>();
	go->AddComponent(ComponentType::PointComponent, pointComp);

	//SubjectComponent
	subjectComp = std::make_shared<SubjectComponent>();
	go->AddComponent(ComponentType::SubjectComponent, subjectComp);

	//Observers
	pointObserver = std::make_shared<PointObserver>(pointComp);
	subjectComp->AddObserver(pointObserver);

	healthObserver = std::make_shared<HealthObserver>(healthComp);
	subjectComp->AddObserver(healthObserver);

	//Button input
	pKill = std::make_shared<KillCommand>(subjectComp) ;
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_DOWN, InputType::KeyDown }, pKill);

	pColorChange = std::make_shared<ColorChangeCommand>(subjectComp) ;
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_RIGHT, InputType::KeyDown }, pColorChange);

	pKillByFlyingDisc = std::make_shared<KillByFlyingDiscCommand> (subjectComp) ;
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_UP, InputType::KeyDown }, pKillByFlyingDisc);

	pRemainingDisc = std::make_shared<RemainingDiscCommand> (subjectComp);
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_DPAD_LEFT, InputType::KeyDown }, pRemainingDisc);

	pCatching = std::make_shared<CatchingCommand> (subjectComp);
	InputManager::GetInstance().AddCommand(ControllerInput{ VK_PAD_LSHOULDER, InputType::KeyDown }, pCatching);

	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = high_resolution_clock::now();
		float lag = 0.f;
		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			
			while (lag >= Time::GetInstance().GetMsPerUpdate())
			{
				Time::GetInstance().Update(Time::GetInstance().GetMsPerUpdate());
				sceneManager.Update(Time::GetInstance().GetElapsed());
				lag -= Time::GetInstance().GetMsPerUpdate();
			}
			renderer.Render();
		}
	}

	Cleanup();
}
