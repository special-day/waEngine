#pragma once
#include "..\\waEngine_SOURCE\\waScene.h"

namespace wa
{
	class Level1 : public Scene
	{
	public:
		Level1();
		~Level1();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
		class Player* mPlayer;
	};

}