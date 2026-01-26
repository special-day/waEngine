#include "waPlayScene.h"
#include "waGameObject.h"
#include "waTransform.h"
#include "waSpriteRenderer.h"
#include "waPlayer.h"

namespace wa
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			Player* p1 = new Player();
			Transform* tr = p1->AddComponent<Transform>();
			tr->SetPos(200.0f, 300.0f);

			tr->SetName(L"TR");

			SpriteRenderer* sr = p1->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(p1);
		}

	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}