#include "MiniginPCH.h"
#include "PointObserver.h"
#include "PointComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"

dae::PointObserver::PointObserver(std::weak_ptr<PointComponent> point)
	:m_pPoints{point}
{
}

void dae::PointObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::ColorChange:
		if (!m_pPoints.expired())
		{
			m_pPoints.lock()->AddPoints(25);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 25 points!\n" << "Total points: " << m_pPoints.lock()->GetPoints() << " in total!\n";
		}
		break;
	case Event::KillByFlyingDisc:
		if (!m_pPoints.expired())
		{
			m_pPoints.lock()->AddPoints(500);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 500 points!\n" << "Total points: " << m_pPoints.lock()->GetPoints() << " in total!\n";
		}
		break;
	case Event::RemainingDisc:
		if (!m_pPoints.expired())
		{
			m_pPoints.lock()->AddPoints(50);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 50 points!\n" << "Total points: " << m_pPoints.lock()->GetPoints() << " in total!\n";
		}
		break;
	case Event::CatchingSlick:
		if (!m_pPoints.expired())
		{
			m_pPoints.lock()->AddPoints(300);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 300 points!\n" << "Total points: " << m_pPoints.lock()->GetPoints() << " in total!\n";
		}
		break;
	case Event::CatchingSam:
		if (!m_pPoints.expired())
		{
			m_pPoints.lock()->AddPoints(300);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 300 points!\n" << "Total points: " << m_pPoints.lock()->GetPoints() << " in total!\n";
		}
		break;
	default:
		break;
	}
}
