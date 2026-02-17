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
#include "waPlayerScript.h"
#include "waCamera.h"
#include "waRenderer.h"
#include "waAnimator.h"

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
		// main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		// camera->AddComponent<PlayerScript>();

		mPlayer = object::Instantiate<Player>
			(enums::eLayerType::Player/*, Vector2(100.0f, 100.0f)*/);
		//SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
		//sr->SetSize(Vector2(3.0f, 3.0f));
		mPlayer->AddComponent<PlayerScript>();

		graphics::Texture* LinkTexture = Resources::Find<graphics::Texture>(L"Link");
		//sr->SetTexure(pacmanTexture);

		Animator* animator = mPlayer->AddComponent<Animator>();
		animator->CreateAnimation(L"Idle", LinkTexture
			, Vector2(0.0f, 0.0f), Vector2(102.4f, 111.0f), Vector2::Zero, 3, 0.1f);
		animator->CreateAnimation(L"DownWalk", LinkTexture
			, Vector2(0.0f, 444.0f), Vector2(102.4f, 111.0f), Vector2::Zero, 10, 0.1f);
		animator->CreateAnimation(L"LeftWalk", LinkTexture
			, Vector2(0.0f, 555.0f), Vector2(102.4f, 111.0f), Vector2::Zero, 10, 0.1f);
		animator->CreateAnimation(L"UpWalk", LinkTexture
			, Vector2(0.0f, 666.0f), Vector2(102.4f, 111.0f), Vector2::Zero, 10, 0.1f);
		animator->CreateAnimation(L"RightWalk", LinkTexture
			, Vector2(0.0f, 777.0f), Vector2(102.4f, 111.0f), Vector2::Zero, 10, 0.1f);
		animator->PlayAnimation(L"Idle", true);

		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));

		GameObject* bg = object::Instantiate<GameObject>
			(enums::eLayerType::BackGround/*, Vector2(100.0f, 100.0f)*/);
		SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
		// bgSr->SetSize(Vector2(3.0f, 3.0f));
		 
		graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Map");
		bgSr->SetTexure(bgTexture);

		// 게임 오브젝트 생성 후에 레이어와 게임오브젝트들의 init 함수를 호출
		Scene::Initialize();

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
		//wchar_t str[50] = L"Play Scene";
		//TextOut(hdc, 0, 0, str, 10);
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