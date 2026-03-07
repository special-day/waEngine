#include "waLevel1.h"
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
#include "waRigidBody.h"
#include "waAudioClip.h"
#include "waAudioListener.h"
#include "waAudioSource.h"

namespace wa
{
	Level1::Level1()
	{
	}
	Level1::~Level1()
	{
	}
	void Level1::Initialize()
	{
		// main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(512.0f, 384.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		AudioSource* as = camera->AddComponent<AudioSource>();

		// Background
		Background* bg = object::Instantiate<Background>(enums::eLayerType::BackGround, Vector2::Zero);
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		graphics::Texture* bgTex = Resources::Find<graphics::Texture>(L"Level1");

		sr->SetTexure(bgTex);

		// ColMap
		graphics::Texture* colMap = Resources::Find<graphics::Texture>(L"Level1_ColMap");
		this->SetColMap(colMap);

		// Player
		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		// object::DontDestroyOnLoad(mPlayer);

		mPlayer->AddComponent<AudioListener>();

		RigidBody* rb = mPlayer->AddComponent<RigidBody>();
		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		collider->SetOffset(Vector2(-30, -60));

		cameraComp->SetTarget(mPlayer);

		graphics::Texture* KirbyRight = Resources::Find<graphics::Texture>(L"Kirby_Right");
		graphics::Texture* KirbyLeft = Resources::Find<graphics::Texture>(L"Kirby_Left");
		graphics::Texture* KirbyJumpRight = Resources::Find<graphics::Texture>(L"Kirby_Jump_Right");
		graphics::Texture* KirbyJumpLeft = Resources::Find<graphics::Texture>(L"Kirby_Jump_Left");

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

		playerAnimator->CreateAnimation(L"RightCrouch", KirbyRight
			, Vector2(456.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.5f);
		playerAnimator->CreateAnimation(L"LeftCrouch", KirbyLeft
			, Vector2(448.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 2, 0.5f);

		playerAnimator->CreateAnimation(L"RightSlide", KirbyRight
			, Vector2(912.0f, 0.0f), Vector2(228.0f, 228.0f), Vector2::Zero, 2, 0.1f);
		playerAnimator->CreateAnimation(L"LeftSlide", KirbyLeft
			, Vector2(896.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 2, 0.1f);

		playerAnimator->CreateAnimation(L"RightJump", KirbyJumpRight
			, Vector2(0.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 9, 0.5f);
		playerAnimator->CreateAnimation(L"LefttJump", KirbyJumpLeft
			, Vector2(0.0f, 0.0f), Vector2(224.0f, 224.0f), Vector2::Zero, 9, 0.5f);


		playerAnimator->PlayAnimation(L"RightStand", true);

		// playerAnimator->GetCompleteEvent(L"Slide") = std::bind(&PlayerScript::AttackEffect, plScript);

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


		AudioClip* ac = Resources::Load<AudioClip>(L"BGM", L"..\\Resources\\Sound\\Play1.mp3");
		as->SetClip(ac);
		as->Play();
		

		// 게임 오브젝트 생성 후에 레이어와 게임오브젝트들의 init 함수를 호출
		Scene::Initialize();
	}
	void Level1::Update()
	{
		Scene::Update();
	}
	void Level1::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Level1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Level1::OnEnter()
	{
		Scene::OnEnter();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

	}
	void Level1::OnExit()
	{
		Scene::OnExit();
	}


}