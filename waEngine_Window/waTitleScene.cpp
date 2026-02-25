#include "waTitleScene.h"
#include "waInput.h"
#include "waPlayScene.h"
#include "waSceneManager.h"
#include "waBackground.h"
#include "waObject.h"
#include "waSpriteRenderer.h"
#include "waResources.h"

namespace wa
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Background* bg = object::Instantiate<Background>(enums::eLayerType::BackGround);
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		graphics::Texture* bgTex = Resources::Find<graphics::Texture>(L"Title_Back");
		
		Background* bgUI = object::Instantiate<Background>(enums::eLayerType::UI);
		SpriteRenderer* sr1 = bgUI->AddComponent<SpriteRenderer>();
		graphics::Texture* bgUITex = Resources::Find<graphics::Texture>(L"Title_Stage");

		sr->SetTexure(bgTex);
		sr1->SetTexure(bgUITex);

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[50] = L"Title Scene";
		int len = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 0, str, len);
	}

}