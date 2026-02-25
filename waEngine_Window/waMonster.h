#pragma once
#include "..\\waEngine_SOURCE\\waGameObject.h"


namespace wa
{
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

	};
}
