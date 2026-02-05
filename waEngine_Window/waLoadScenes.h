#pragma once
#include "..\\waEngine_SOURCE\\waSceneManager.h"

#include "waPlayScene.h"
#include "waEndScene.h"
#include "waTitleScene.h"

namespace wa
{


	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndScene>(L"EndScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}