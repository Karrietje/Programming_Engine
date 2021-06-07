#include "BeginScreenComponent.h"
#include <Windows.h>
#include "../3rdParty/imgui-1.81/imgui.h"
#include "SceneManager.h"
#include "GameManagerComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Audio.h"
#include "AudioLocator.h"

void dae::BeginScreenComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::BeginScreenComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);

	//Making buttons with IMGUI
	static ImVec4 color = ImVec4(114.f / 255.f, 144.f / 255.f, 154.f / 255.f, 200.f / 255.f);
	ImGui::Begin("Window", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(230.f, 250.f));
	ImGui::Text("GameModes:");
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.f, 0.6f, 0.6f));
	if (ImGui::Button("Single Player", ImVec2(200.f, 50.f)))
	{
		auto& soloScene = SceneManager::GetInstance().CreateScene("GameSolo");

		GameObject* pGameObject = new GameObject();
		GameManagerComponent* pGameManager = new GameManagerComponent(&soloScene, GameManagerComponent::GameMode::Single);

		pGameObject->AddComponent(ComponentType::GameManagerComponent, pGameManager);
		soloScene.Add(pGameObject, 0);
		SceneManager::GetInstance().SetCurrentScene("GameSolo");
		AudioLocator::GetAudioSystem()->PlaySoundW(0);
		
	}
	if (ImGui::Button("Coop", ImVec2(200.f, 50.f)))
	{
		auto& coopScene = SceneManager::GetInstance().CreateScene("GameCoop");
		GameObject* pGameObject = new GameObject();
		GameManagerComponent* pGameManager = new GameManagerComponent(&coopScene, GameManagerComponent::GameMode::Coop);

		pGameObject->AddComponent(ComponentType::GameManagerComponent, pGameManager);
		coopScene.Add(pGameObject, 0);

		SceneManager::GetInstance().SetCurrentScene("GameCoop");
		AudioLocator::GetAudioSystem()->PlaySoundW(0);
	}
	ImGui::PopStyleColor(1);
	ImGui::End();
}
