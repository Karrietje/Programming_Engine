#include <Windows.h>
#include "TileComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "Scene.h"
#include "TileManager.h"


using namespace dae; 
dae::TileComponent::TileComponent()
	:m_Neighbours {}
	, m_ColorCyclesBack{ false }
	, m_IsRightColor{ false }
	, m_pTileManager{ nullptr }
{
}

void dae::TileComponent::Initialize(Scene* pScene, glm::vec2 position, TileManager* pTileManager, int level)
{
	m_pTileManager = pTileManager; 
	m_pGameObject->GetTransform()->SetPosition(position.x, position.y);

	GameObject* pObject = nullptr;
	TextureComponent* textureComp = nullptr;

	switch (level)
	{
	case 0:
		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeRed.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);

		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeBlue.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);
		pObject->SetActive(false);
		break;
	case 1:
		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeRed.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);

		pObject = new GameObject();
		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeYellow.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject,0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);
		pObject->SetActive(false);

		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeBlue.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);
		pObject->SetActive(false);
		break;
	case 2:
		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeRed.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);

		pObject = new GameObject();

		textureComp = new TextureComponent();
		textureComp->SetTexture("CubeBlue.png");
		pObject->AddComponent(ComponentType::TextureComponent, textureComp);

		pScene->Add(pObject, 0);
		m_pGameObject->AddChild(pObject);
		m_pColors.push_back(pObject);
		pObject->SetActive(false);
		m_ColorCyclesBack = true;
		break;
	}
}

void dae::TileComponent::SetTopRightTile(TileComponent* pTile)
{
	m_Neighbours.TopRight = pTile;
}

void dae::TileComponent::SetBottomRightTile(TileComponent* pTile)
{
	m_Neighbours.BottomRight = pTile;
}

void dae::TileComponent::SetBottomLeftTile(TileComponent* pTile)
{
	m_Neighbours.BottomLeft = pTile;
}

void dae::TileComponent::SetTopLeftTile(TileComponent* pTile)
{
	m_Neighbours.TopLeft = pTile;

}

void dae::TileComponent::SetLeftTile(TileComponent* pTile)
{
	m_Neighbours.Left = pTile;
}

void dae::TileComponent::SetRightTile(TileComponent* pTile)
{
	m_Neighbours.Right = pTile;
}

SpinningDisksComponent* dae::TileComponent::GetSpinningDisk() const
{
	return m_pSpinningDisk;
}

void dae::TileComponent::SetSpinningDisk(SpinningDisksComponent* pSpinningDisk)
{
	m_pSpinningDisk = pSpinningDisk;
}

void dae::TileComponent::JumpOn(SubjectComponent* pSubjectComponent)
{
	int tempColor = (m_CurrentColor + 1) % m_pColors.size();
	if (tempColor == 0 && !m_ColorCyclesBack)
	{
		return;
	}
	pSubjectComponent->Notify(Event::ColorChange);
	m_pColors[m_CurrentColor]->SetActive(false);
	m_pColors[tempColor]->SetActive(true);
	m_CurrentColor = tempColor;
	if (tempColor == 0)
		m_pTileManager->SetTile(false);
	else if (m_CurrentColor == int(m_pColors.size() - 1))
		m_pTileManager->SetTile(true);
		
}

void dae::TileComponent::Revert()
{
	int tempColor = m_CurrentColor - 1; 
	if (tempColor < 0)
	{
		return; 
	}
	m_pColors[m_CurrentColor]->SetActive(false);
	m_pColors[tempColor]->SetActive(true);
	m_CurrentColor = tempColor;
	m_pTileManager->SetTile(m_CurrentColor == int(m_pColors.size() - 1));
}


TileComponent::Neighbours dae::TileComponent::GetNeighbours() const
{
	return m_Neighbours;
}

glm::vec2 dae::TileComponent::GetPosition() const
{
	glm::vec2 position{ m_pGameObject->GetTransform()->GetPosition() };
	position.x += 10;
	position.y -= 10;
	return position;
}

glm::vec2 dae::TileComponent::GetSidePosition(bool left) const
{
	glm::vec2 position{ m_pGameObject->GetTransform()->GetPosition() };
	if (!left)
	{
		position.x += 40;
	}
	position.y += 30;
	return position;
}

GameObject* dae::TileComponent::GetSlickSam() const
{
	return m_pSlickSam; 
}

GameObject* dae::TileComponent::GetUggWrongway() const
{
	return m_pUggWrongway;
}

GameObject* dae::TileComponent::GetCoily() const
{
	return m_pCoily;
}

void dae::TileComponent::SetSlickSam(GameObject* pEnemy)
{
	m_pSlickSam = pEnemy; 
}

void dae::TileComponent::SetUggWrongway(GameObject* pEnemy)
{
	m_pUggWrongway = pEnemy;
}

void dae::TileComponent::SetCoily(GameObject* pCoily)
{
	m_pCoily = pCoily;
}

void dae::TileComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::TileComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position); 
}
