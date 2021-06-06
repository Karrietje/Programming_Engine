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
	auto& beginScene = SceneManager::GetInstance().CreateScene("BeginScene");

	GameObject* pGameObject = new GameObject();
	BeginScreenComponent* pBeginScreenComponent = new BeginScreenComponent();
	pGameObject->AddComponent(ComponentType::BeginScreenComponent, pBeginScreenComponent);

	beginScene.Add(pGameObject, 0);

	auto& endScene = SceneManager::GetInstance().CreateScene("EndScene");

	pGameObject = new GameObject();
	TextureComponent* pTextureComponent = new TextureComponent();
	pTextureComponent->SetTexture("background.jpg");
	pGameObject->AddComponent(ComponentType::TextureComponent, pTextureComponent);

	endScene.Add(pGameObject, 0);

	SceneManager::GetInstance().SetCurrentScene("BeginScene");
}