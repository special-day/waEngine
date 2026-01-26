#pragma once
#include "..\\waEngine_SOURCE\\waSceneManager.h"
#include "waPlayScene.h"
#include "waEndScene.h"

namespace wa
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndScene>(L"EndScene");
		// SceneManager::CreateScene<TitleScene>(L"TitleScene");

		SceneManager::LoadScene(L"EndScene");
	}
}