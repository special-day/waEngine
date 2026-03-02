#include "waPlayerScript.h"
#include "waInput.h"
#include "waTransform.h"
#include "waTime.h"
#include "waGameObject.h"
#include "waAnimator.h"
#include "waMonster.h"
#include "waMonScript.h"
#include "waObject.h"
#include "waCollider.h"
#include "waResources.h"

namespace wa
{
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::Stand)
		, mAnimator(nullptr)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case wa::PlayerScript::eState::Stand:
			stand();
			break;
		case wa::PlayerScript::eState::Walk:
			walk();
			break;
		case wa::PlayerScript::eState::Run:
			run();
			break;
		case wa::PlayerScript::eState::Crouch:
		{
			if (Input::GetKeyUp(eKeyCode::Down))
			{
				mState = PlayerScript::eState::Stand;
				mAnimator->PlayAnimation(L"RightStand");
			}
		}
			break;
		case wa::PlayerScript::eState::Slide:
			slide();
			break;
		default:
			break;
		}

	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hdc)
	{
	}
	void PlayerScript::AttackEffect()
	{
		Monster* WaddleDee = object::Instantiate<Monster>(enums::eLayerType::Monster);
		WaddleDee->AddComponent<MonScript>();

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

		WaddleDee->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
	}

	void PlayerScript::stand()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = PlayerScript::eState::Slide;
			mAnimator->PlayAnimation(L"Slide", false);
		}

		if (Input::GetKey(eKeyCode::Right))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalk");
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			mState = PlayerScript::eState::Crouch;
			mAnimator->PlayAnimation(L"Crouch");
		}
	}
	void PlayerScript::walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 100.0f * Time::DT();

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = PlayerScript::eState::Run;
				mAnimator->PlayAnimation(L"RightRun");
			}
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 100.0f * Time::DT();

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = PlayerScript::eState::Run;
				mAnimator->PlayAnimation(L"LeftRun");
			}
		}

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"RightStand");
		}

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"LeftStand");
		}
	}

	void PlayerScript::run()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 200.0f * Time::DT();

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				mAnimator->PlayAnimation(L"RightWalk");
			}
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 200.0f * Time::DT();

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				mAnimator->PlayAnimation(L"LeftWalk");
			}
		}

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"RightStand");
		}

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"LeftStand");
		}
	}

	void PlayerScript::slide()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Stand;
			mAnimator->PlayAnimation(L"RightStand");
		}
	}

	void PlayerScript::attack()
	{
	}

}