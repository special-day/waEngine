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
#include "waBoxCollider2D.h"
#include "waCircleCollider2D.h"
#include "waCollisionManager.h"

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
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(512.0f, 384.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// Player
		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		collider->SetOffset(Vector2(-50, -75));

		// cameraComp->SetTarget(mPlayer);

		graphics::Texture* KirbyRight = Resources::Find<graphics::Texture>(L"Kirby_Right");
		graphics::Texture* KirbyLeft = Resources::Find<graphics::Texture>(L"Kirby_Left");

		Animator* playerAnimator = mPlayer->AddComponent<Animator>();
		playerAnimator->CreateAnimation(L"RightStand", KirbyRight
			, Vector2(0.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);
		playerAnimator->CreateAnimation(L"LeftStand", KirbyLeft
			, Vector2(0.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->CreateAnimation(L"RightWalk", KirbyRight
			, Vector2(1368.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 10, 0.1f);
		playerAnimator->CreateAnimation(L"LeftWalk", KirbyLeft
			, Vector2(1344.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 10, 0.1f);

		playerAnimator->CreateAnimation(L"RightRun", KirbyRight
			, Vector2(1368.0f, 228.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 8, 0.1f);
		playerAnimator->CreateAnimation(L"LeftRun", KirbyLeft
			, Vector2(1344.0f, 228.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 8, 0.1f);

		playerAnimator->CreateAnimation(L"Crouch", KirbyRight
			, Vector2(456.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->CreateAnimation(L"Slide", KirbyRight
			, Vector2(1140.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->PlayAnimation(L"RightStand", true);

		playerAnimator->GetCompleteEvent(L"Slide") = std::bind(&PlayerScript::AttackEffect, plScript);

		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(512.0f, 384.0f));
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));

		// Monster
		Monster* WaddleDee = object::Instantiate<Monster>(enums::eLayerType::Monster);
		WaddleDee->AddComponent<MonScript>();
		CircleCollider2D* monCollider = WaddleDee->AddComponent<CircleCollider2D>();
		monCollider->SetOffset(Vector2(-50, -75));


		graphics::Texture* WaddleDee_Left = Resources::Find<graphics::Texture>(L"BigWaddleDee_Left");
		graphics::Texture* WaddleDee_Right = Resources::Find<graphics::Texture>(L"BigWaddleDee_Right");

		Animator* monAnimator = WaddleDee->AddComponent<Animator>();
		monAnimator->CreateAnimation(L"Idle", WaddleDee_Left
			, Vector2(0.0f, 448.0f), Vector2(448.0f, 448.0f), Vector2::Zero, 1, 0.1f);
		monAnimator->CreateAnimation(L"LeftWalk", WaddleDee_Left
			, Vector2(0.0f, 0.0f), Vector2(448.0f, 448.0f), Vector2::Zero, 5, 0.1f);
		monAnimator->CreateAnimation(L"RightWalk", WaddleDee_Right
			, Vector2(0.0f, 0.0f), Vector2(448.0f, 448.0f), Vector2::Zero, 5, 0.1f);
		monAnimator->PlayAnimation(L"Idle", true);

		WaddleDee->GetComponent<Transform>()->SetPosition(Vector2(412.0f, 384.0f));

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