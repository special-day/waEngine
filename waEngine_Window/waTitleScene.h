#pragma once
#include "..\\waEngine_SOURCE\\waScene.h"
#include "waInput.h"
#include "waPlayScene.h"
#include "waSceneManager.h"
#include "waBackground.h"
#include "waObject.h"
#include "waSpriteRenderer.h"
#include "waResources.h"

namespace wa
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	};

}