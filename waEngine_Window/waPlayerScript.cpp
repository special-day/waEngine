#include "waPlayerScript.h"
#include "waInput.h"
#include "waTransform.h"
#include "waTime.h"
#include "waGameObject.h"
#include "waAnimator.h"

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
				mAnimator->PlayAnimation(L"Stand");
			}
		}
			break;
		case wa::PlayerScript::eState::Slide:
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
	}
	void PlayerScript::stand()
	{
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

		if (Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::Left))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"Stand");
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

		if (Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::Left))
		{
			mState = PlayerScript::eState::Stand;
			mAnimator->PlayAnimation(L"Stand");
		}
	}

}