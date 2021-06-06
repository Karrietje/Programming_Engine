#pragma once
#include "Observer.h"


namespace dae
{
	class HealthComponent; 
	class HealthObserver final : public Observer
	{
	public:
		HealthObserver(HealthComponent* health);

		virtual void Notify(Event event) override;


	private:
		HealthComponent* m_pHealth; 
	};
}

