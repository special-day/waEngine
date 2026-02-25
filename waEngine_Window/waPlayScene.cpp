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
#include "waMonster.h"
#include "waMonScript.h"

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
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(512.0f, 384.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// Player
		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();

		cameraComp->SetTarget(mPlayer);

		graphics::Texture* KirbyRight = Resources::Find<graphics::Texture>(L"Kirby_Right");
		graphics::Texture* KirbyLeft = Resources::Find<graphics::Texture>(L"Kirby_Left");

		Animator* playerAnimator = mPlayer->AddComponent<Animator>();
		playerAnimator->CreateAnimation(L"Stand", KirbyRight
			, Vector2(0.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->CreateAnimation(L"Crouch", KirbyRight
			, Vector2(456.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->CreateAnimation(L"RightWalk", KirbyRight
			, Vector2(1368.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 10, 0.2f);
		playerAnimator->CreateAnimation(L"LeftWalk", KirbyLeft
			, Vector2(1344.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 10, 0.2f);

		playerAnimator->CreateAnimation(L"RightRun", KirbyRight
			, Vector2(1368.0f, 228.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 8, 0.2f);
		playerAnimator->CreateAnimation(L"LeftRun", KirbyLeft
			, Vector2(1344.0f, 228.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 8, 0.2f);

		playerAnimator->PlayAnimation(L"Stand", true);

		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(512.0f, 384.0f));
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));

		// Monster
		//Monster* mon = object::Instantiate<Monster>(enums::eLayerType::Monster);
		//mon->AddComponent<MonScript>();

		//graphics::Texture* MonTexture = Resources::Find<graphics::Texture>(L"Enemies");

		//Animator* monAnimator = mon->AddComponent<Animator>();
		//monAnimator->CreateAnimation(L"Idle", MonTexture
		//	, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//monAnimator->CreateAnimation(L"DownWalk", MonTexture
		//	, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//monAnimator->CreateAnimation(L"LeftWalk", MonTexture
		//	, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//monAnimator->CreateAnimation(L"UpWalk", MonTexture
		//	, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//monAnimator->CreateAnimation(L"RightWalk", MonTexture
		//	, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//monAnimator->PlayAnimation(L"Idle", true);

		//mon->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
		//mon->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

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