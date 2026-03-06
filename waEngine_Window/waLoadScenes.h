#pragma once
#include "..\\waEngine_SOURCE\\waSceneManager.h"

#include "waPlayScene.h"
#include "waEndScene.h"
#include "waTitleScene.h"
#include "waLevel1.h"

namespace wa
{


	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndScene>(L"EndScene");
		SceneManager::CreateScene<Level1>(L"Level1");

		SceneManager::LoadScene(L"Level1");
	}
}