#include "waPlayScene.h"
#include "waGameObject.h"
#include "waTransform.h"
#include "waSpriteRenderer.h"
#include "waPlayer.h"
#include "waInput.h"
#include "waTitleScene.h"
#include "waSceneManager.h"

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
			Player* bg = new Player();
			Transform* tr = bg->AddComponent<Transform>();
			tr->SetPos(Vector2(0, 0));

			tr->SetName(L"TR");

			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");
			sr->ImageLoad(L"C:\\wa\\waEngine\\Resources\\simple.png");

			AddGameObject(bg, eLayerType::BackGround);
		}

	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if(Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[50] = L"Play Scene";
		int len = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 0, str, len);
	}
	void PlayScene::OnEnter()
	{
	}

	void PlayScene::OnExit()
	{
		Transform* tr = bg->AddComponent<Transform>();
		tr->SetPos(Vector2(0, 0));
	}
}