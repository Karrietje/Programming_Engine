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

		virtual void Render(glm::vec2 position) override;
		virtual void Update(float elapsedSec) override;
		
		void Initialize(); 
		void Reset(TileComponent* pTile); 
		
		Type GetType() const; 

	private:
		void CoilyUpdate();
		void SetCoilyComponent(CoilyComponent* pCoilyComponent);
		void SlickSamUpdate();
		void UggWrongwayUpdate();

		friend class CoilyComponent;

		bool m_Previous;
		bool m_IsLeftOnTile;

		float m_Timer;
		const float m_MoveTime; 
		
		CoilyComponent* m_pCoilyComponent;
		TileComponent* m_pCurrentTile;
		Type m_Type; 
	};
}

