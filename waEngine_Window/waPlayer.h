#pragma once
#include "waGameObject.h"


namespace wa
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

	};
}
