#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"

dae::HealthObserver::HealthObserver(std::weak_ptr<HealthComponent> health)
	:m_pHealth{health}
{
}

void dae::HealthObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::Kill:
		if (!m_pHealth.expired())
		{
			//lock = temporary change to real pointer
			m_pHealth.lock()->LoseHealth();
			if (m_pHealth.lock()->GetHealth() != 0)
			{
				std::cout << m_pSubject->GetGameObject()->GetName() << " loses HP!\n Remaining HP: " << m_pHealth.lock()->GetHealth() << '\n';
			}
			else
			{
				std::cout << m_pSubject->GetGameObject()->GetName() << " died!\n";
			}
		}
		break;
	}
}
