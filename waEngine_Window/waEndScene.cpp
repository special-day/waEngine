#include "waEndScene.h"

namespace wa
{
	EndScene::EndScene()
	{
	}
	EndScene::~EndScene()
	{
	}
	void EndScene::Initialize()
	{
		for (size_t i = 0; i < 5; i++)
		{
			GameObject* obj = new GameObject();
			obj->SetPosition(rand() % 1600, rand() % 900);
			AddGameObject(obj);
		}

	}
	void EndScene::Update()
	{
		Scene::Update();
	}
	void EndScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}