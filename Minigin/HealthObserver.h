#pragma once
#include "Observer.h"


namespace dae
{
	class HealthComponent; 
	class HealthObserver final : public Observer
	{
	public:
		HealthObserver(std::weak_ptr<HealthComponent> health);

		virtual void Notify(Event event) override;


	private:
		std::weak_ptr<HealthComponent> m_pHealth; 
	};
}

