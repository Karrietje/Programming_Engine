#pragma once
#include <Component.h>

namespace dae
{
	class TileComponent;
	class CoilyComponent;
	class AiComponent final : public Component
	{
	public:
		enum class Type
		{
			SlickSam,
			Coily,
			UggWrongway
		};
		AiComponent(TileComponent* pStartTile, Type type, bool left = false);
		/*~AiComponent(); */
		void Initialize(); 
		Type GetType() const; 
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
		void Reset(TileComponent* pTile); 

	private:
		bool m_IsLeftOnTile;
		bool m_Previous;

		TileComponent* m_pCurrentTile;
		CoilyComponent* m_pCoilyComponent;
		Type m_Type; 

		const float m_MoveTime; 
		float m_Timer;

		void SlickSamUpdate();
		void CoilyUpdate();
		void UggWrongwayUpdate();

		friend class CoilyComponent;
		void SetCoilyComponent(CoilyComponent* pCoilyComponent);
	};
}

