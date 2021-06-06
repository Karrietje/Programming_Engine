#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"

dae::HealthObserver::HealthObserver(HealthComponent* health)
	:m_pHealth{health}
{
}

void dae::HealthObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::Kill:
		if (m_pHealth)
		{
			//lock = temporary change to real pointer
			m_pHealth->LoseHealth();
			if (m_pHealth->GetHealth() != 0)
			{
				std::cout << m_pSubject->GetGameObject()->GetName() << " loses HP!\n Remaining HP: " << m_pHealth->GetHealth() << '\n';
			}
			else
			{
				std::cout << m_pSubject->GetGameObject()->GetName() << " died!\n";
			}
		}
		break;
	}
}
