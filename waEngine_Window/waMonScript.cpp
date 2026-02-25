#include "waMonScript.h"
#include "waPlayerScript.h"
#include "waInput.h"
#include "waTransform.h"
#include "waTime.h"
#include "waGameObject.h"
#include "waAnimator.h"

namespace wa
{
	MonScript::MonScript()
		: mState(MonScript::eState::Idle)
		, mAnimator(nullptr)
		, mTime(0.0f)
	{
	}
	MonScript::~MonScript()
	{
	}
	void MonScript::Initialize()
	{
	}
	void MonScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case wa::MonScript::eState::Idle:
			idle();
			break;
		case wa::MonScript::eState::Walk:
			move();
			break;
		default:
			break;
		}

	}
	void MonScript::LateUpdate()
	{
	}
	void MonScript::Render(HDC hdc)
	{
	}
	void MonScript::idle()
	{
		mTime += Time::DT();
		if (mTime > 3.0f)
		{
			mState = MonScript::eState::Walk;
			int direction = (rand() % 4);
			mDirection = (eDirection)direction;
			playWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
		}
	}
	void MonScript::move()
	{
		mTime += Time::DT();
		if (mTime > 2.0f)
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		translate(tr);

		//if (Input::GetKey(eKeyCode::D))
		//{
		//	pos.x += 100.0f * Time::DT();
		//}
		//if (Input::GetKey(eKeyCode::A))
		//{
		//	pos.x -= 100.0f * Time::DT();
		//}
		//if (Input::GetKey(eKeyCode::W))
		//{
		//	pos.y -= 100.0f * Time::DT();
		//}
		//if (Input::GetKey(eKeyCode::S))
		//{
		//	pos.y += 100.0f * Time::DT();
		//}

		//tr->SetPosition(pos);

		//if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
		//	|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		//{
		//	mState = MonScript::eState::Idle;
		//	mAnimator->PlayAnimation(L"Idle");
		//}

	}

	void MonScript::playWalkAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case wa::MonScript::eDirection::Left:
			mAnimator->PlayAnimation(L"LeftWalk", true);
			break;
		case wa::MonScript::eDirection::Right:
			mAnimator->PlayAnimation(L"RightWalk", true);
			break;
		case wa::MonScript::eDirection::Down:
			mAnimator->PlayAnimation(L"DownWalk", true);
			break;
		case wa::MonScript::eDirection::Up:
			mAnimator->PlayAnimation(L"UpWalk", true);
			break;
		case wa::MonScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
	}

	void MonScript::translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case wa::MonScript::eDirection::Left:
			pos.x -= 100.0f * Time::DT();
			break;
		case wa::MonScript::eDirection::Right:
			pos.x += 100.0f * Time::DT();
			break;
		case wa::MonScript::eDirection::Down:
			pos.y += 100.0f * Time::DT();
			break;
		case wa::MonScript::eDirection::Up:
			pos.y -= 100.0f * Time::DT();
			break;
		case wa::MonScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}

		tr->SetPosition(pos);
	}
}