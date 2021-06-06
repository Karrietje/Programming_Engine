#pragma once
#include <Component.h>

namespace dae
{
	class TileComponent;
	class AiComponent final : public Component
	{
	public:
		enum class Type
		{
			SlickSam,
			Coily,
			UggWrongway
		};
		AiComponent(TileComponent* pStartTile, Type type);
		/*~AiComponent(); */
		void Initialize(); 
		Type GetType() const; 
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
		void Reset(TileComponent* pTile); 

	private:

		TileComponent* m_pCurrentTile;
		Type m_Type; 

		const float m_MoveTime; 
		float m_Timer;
	};
}

