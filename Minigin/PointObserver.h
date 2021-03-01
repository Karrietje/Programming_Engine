#pragma once
#include "Observer.h"

namespace dae
{
	class PointComponent;
	class PointObserver final : public Observer
	{
	public:
		PointObserver(std::weak_ptr<PointComponent> point);

		virtual void Notify(Event event) override;


	private:
		std::weak_ptr<PointComponent> m_pPoints;
	};
}
