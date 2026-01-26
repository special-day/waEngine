#pragma once
#include "..\\waEngine_SOURCE\\waScene.h"

namespace wa
{
	class EndScene : public Scene
	{
	public:
		EndScene();
		~EndScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		
	};
}

