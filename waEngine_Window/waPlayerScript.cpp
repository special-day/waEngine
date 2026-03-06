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
#include "waRigidBody.h"


namespace wa
{
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::Stand)
		, mPrevState(PlayerScript::eState::Stand)
		, mDir(eDirection::Right)
		, mPrevDir(eDirection::Right)
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
		case wa::PlayerScript::eState::Stand: stand(); break;
		case wa::PlayerScript::eState::Walk: walk(); break;
		case wa::PlayerScript::eState::Run: run(); break;
		case wa::PlayerScript::eState::Jump: jump(); break;
		case wa::PlayerScript::eState::Fall: fall(); break;
		case wa::PlayerScript::eState::Crouch: crouch(); break;
		case wa::PlayerScript::eState::Slide: slide(); break;
		case wa::PlayerScript::eState::Inhale: inhale(); break;
		case wa::PlayerScript::eState::Full: full(); break;
		case wa::PlayerScript::eState::Attack: attack(); break;
		case wa::PlayerScript::eState::Hit: hit(); break;
		default: break;
		}

		updateAnimation();
		updateCollider();

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
		// 충돌한 대상의 레이어가 몬스터라면
		if (other->GetOwner()->GetLayerType() == enums::eLayerType::Monster)
		{
			// 내가 지금 슬라이딩 중일 때만 공격 성공
			if (mState == eState::Slide)
			{
				// 몬스터에게 대미지를 주거나 삭제
			}
			else
			{
				// 슬라이딩 중이 아닐 때 부딪히면 커비가 대미지를 입음
			}
		}

		if (other->GetOwner()->GetLayerType() == enums::eLayerType::Ground)
		{
			RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
			if (rb)
			{
				Vector2 velocity = rb->GetVelocity();
				if (velocity.y > 0.0f)
				{
					velocity.y = 0.0f;
					rb->SetVelocity(velocity);
				}

				rb->SetGround(true);

				if (mState == eState::Jump || mState == eState::Fall)
				{
					mState = eState::Stand;
				}
			}
		}
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == enums::eLayerType::Ground)
		{
			RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
			if (rb)
			{
				rb->SetGround(false);
			}
		}
	}

	void PlayerScript::stand()
	{
		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			mState = eState::Walk;
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			mState = eState::Walk;
		}

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eState::Crouch;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = eState::Slide;
		}
	}
	void PlayerScript::walk()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float moveSpeed = 150.0f;

		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			pos.x += moveSpeed * Time::DT();

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = eState::Run;
				return;
			}
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			pos.x -= moveSpeed * Time::DT();

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = eState::Run;
				return;
			}
		}
		else
		{
			mState = eState::Stand;
		}

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eState::Crouch;
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::run()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float runSpeed = 250.0f;

		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			pos.x += runSpeed * Time::DT();

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				return;
			}
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			pos.x -= runSpeed * Time::DT();

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				return;
			}
		}
		else
		{
			mState = eState::Stand;
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::jump()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();

		if (Input::GetKeyUp(eKeyCode::X))
		{
			Vector2 velocity = rb->GetVelocity();
			if (velocity.y < 0.0f) {
				velocity.y *= 0.5f;
				rb->SetVelocity(velocity);
			}
		}

		if (rb->GetVelocity().y > 0.0f)
		{
			mState = eState::Fall;
		}
	}

	void PlayerScript::fall()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();

		if (rb->GetGround())
		{
			mState = eState::Stand;
		}

		float airControl = 100.0f;
		if (Input::GetKey(eKeyCode::Right)) rb->AddForce(Vector2(airControl, 0.0f));
		if (Input::GetKey(eKeyCode::Left))  rb->AddForce(Vector2(-airControl, 0.0f));
	}

	void PlayerScript::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mState = eState::Stand;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::Right))
			mDir = eDirection::Right;
		if (Input::GetKeyDown(eKeyCode::Left))
			mDir = eDirection::Left;

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = eState::Slide;
			return;
		}
	}

	void PlayerScript::slide()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		float slideSpeed = 400.0f;

		if (mDir == eDirection::Right)
			pos.x += slideSpeed * Time::DT();
		else
			pos.x -= slideSpeed * Time::DT();

		tr->SetPosition(pos);

		if (mAnimator->IsComplete())
		{
			mState = eState::Stand;
		}
	}

	void PlayerScript::inhale()
	{
	}

	void PlayerScript::full()
	{
	}

	void PlayerScript::attack()
	{
	}

	void PlayerScript::hit()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Stand;
		}
	}

	void PlayerScript::updateAnimation()
	{
		std::wstring animName = (mDir == eDirection::Right) ? L"Right" : L"Left";

		switch (mState)
		{
		case eState::Stand:  animName += L"Stand";  break;
		case eState::Walk:   animName += L"Walk";   break;
		case eState::Run:    animName += L"Run";    break;
		case eState::Jump:   animName += L"Jump";    break;
		case eState::Fall:   animName += L"Fall";    break;
		case eState::Crouch: animName += L"Crouch"; break;
		case eState::Slide:  animName += L"Slide";  break;
		case eState::Inhale: animName += L"Inhale"; break;
		case eState::Full:   animName += L"Full";    break;
		case eState::Attack: animName += L"Attack";    break;
		case eState::Hit:    animName += L"Hit";    break;
		default: break;
		}

		// 상태가 변했을 때만 새로 재생
		if (mPrevState != mState || mPrevDir != mDir)
		{
			bool loop = (mState == eState::Slide) ? false : true;

			mAnimator->PlayAnimation(animName, loop); // Slide는 false로 설정

			mPrevState = mState;
			mPrevDir = mDir;
		}
	}

	void PlayerScript::updateCollider()
	{
		Collider* col = GetOwner()->GetComponent<Collider>();
		if (!col) return;

		if (mState == eState::Crouch)
		{
			col->SetSize(Vector2(1.0f, 0.5f));
			col->SetOffset(Vector2(-30, -30));
		}
		else
		{
			col->SetSize(Vector2(1.0f, 1.0f));
			col->SetOffset(Vector2(-30, -60));
		}
	}

}