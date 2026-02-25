#pragma once
#include "waGameObject.h"


namespace wa
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	};
}
