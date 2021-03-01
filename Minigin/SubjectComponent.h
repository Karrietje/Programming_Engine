#pragma once
#include "Component.h"
#include "Utils.h"
#include <vector>
#include <memory>

namespace dae
{
	class Observer; 
	class SubjectComponent : public Component
	{
	public:
		SubjectComponent(); 

		void AddObserver(std::shared_ptr<Observer> pObserver);
		void Notify(Event event); 

		// Inherited via Component
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers; 

	};

}
