// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <Minigin.h>
#include "SceneManager.h"
#include <vld.h>
#include "GameManagerComponent.h"
#include "GameObject.h"
#include "Scene.h"

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
	auto& scene = SceneManager::GetInstance().CreateScene("Game");
	SceneManager::GetInstance().SetCurrentScene("Game");
	
	GameObject* pGameObject = new GameObject(); 
	GameManagerComponent* pGameManager = new GameManagerComponent(&scene); 
	
	pGameObject->AddComponent(ComponentType::GameManagerComponent, pGameManager); 
	scene.Add(pGameObject, 0); 

}