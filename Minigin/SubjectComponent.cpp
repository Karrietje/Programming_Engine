#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "Observer.h"

dae::SubjectComponent::SubjectComponent()
	:m_pObservers{}
{
}

void dae::SubjectComponent::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver); 
	pObserver->SetSubjectComponent(this); 
}

void dae::SubjectComponent::Notify(Event event)
{
	for (std::shared_ptr<Observer> pObserver : m_pObservers)
	{
		pObserver->Notify(event); 
	}
}

void dae::SubjectComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::SubjectComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}
