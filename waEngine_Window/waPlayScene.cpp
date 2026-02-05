#include "waPlayScene.h"
#include "waGameObject.h"
#include "waTransform.h"
#include "waSpriteRenderer.h"
#include "waPlayer.h"
#include "waInput.h"
#include "waTitleScene.h"
#include "waSceneManager.h"
#include "waObject.h"
#include "waTexture.h"
#include "waResources.h"

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
		// 게임 오브젝트 만들기 전에 리소스들 전부 Load해 두면 좋다.

		{
			bg = object::Instantiate<Player>
				(enums::eLayerType::BackGround, Vector2(100.0f, 100.0f));
			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();

			graphics::Texture* bg = Resources::Find<graphics::Texture>(L"BG");
			sr->SetTexure(bg);

			/*graphics::Texture* tex = new graphics::Texture();
			tex->Load(L"C:\\wa\\waEngine\\Resources\\simple.png");*/

			// sr->ImageLoad(L"C:\\wa\\waEngine\\Resources\\simple.png");
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
		//Transform* tr = bg->AddComponent<Transform>();
		//tr->SetPosition(Vector2(0, 0));
	}
}