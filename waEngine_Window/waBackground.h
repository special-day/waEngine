#pragma once
#include "waGameObject.h"

namespace wa
{
	class Background : public GameObject
	{
	public:
		Background();
		~Background();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	};
}
