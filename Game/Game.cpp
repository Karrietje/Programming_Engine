// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <Minigin.h>
#include "SceneManager.h"
#include "GameManagerComponent.h"
#include "BeginScreenComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include <vld.h>

using namespace dae;

void Initialize(); 

int main(int, char* []) 
{
	Minigin engine;
	engine.Initialize();

	Initialize(); 

	engine.Run();

	return 0;
}

void Initialize()
{
	//Begin scene with background
	auto& beginScene = SceneManager::GetInstance().CreateScene("BeginScene");

	GameObject* pGameObject = new GameObject();
	BeginScreenComponent* pBeginScreenComponent = new BeginScreenComponent();
	pGameObject->AddComponent(ComponentType::BeginScreenComponent, pBeginScreenComponent);
	beginScene.Add(pGameObject, 0);
	
	GameObject* pGameObjectFont = new GameObject();
	TextureComponent* pTextureComponentBegin = new TextureComponent();
	pTextureComponentBegin->SetTexture("BeginScreen.png");
	pGameObjectFont->AddComponent(ComponentType::TextureComponent, pTextureComponentBegin);
	beginScene.Add(pGameObjectFont, 0);

	//End scene with background
	auto& endScene = SceneManager::GetInstance().CreateScene("EndScene");

	pGameObject = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
	auto textComp = new TextComponent();
	textComp->SetFont(font);
	textComp->SetText("Game Over!");
	pGameObject->AddComponent(ComponentType::TextComponent, textComp);
	endScene.Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(200.f, 200.f);

	pGameObject = new GameObject();
	TextureComponent* pTextureComponentEnd = new TextureComponent();
	pTextureComponentEnd->SetTexture("background.jpg");
	pGameObject->AddComponent(ComponentType::TextureComponent, pTextureComponentEnd);

	endScene.Add(pGameObject, 0);

	SceneManager::GetInstance().SetCurrentScene("BeginScene");
}