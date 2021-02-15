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
