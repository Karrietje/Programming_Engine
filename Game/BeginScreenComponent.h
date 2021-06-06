#pragma once
#include <Component.h>

namespace dae
{
	class BeginScreenComponent final : public Component
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
	};
}