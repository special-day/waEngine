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

		if (Input::GetKeyDown(eKeyCode::V))
		{
			mState = eState::Inhale;
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			initJump();
			mState = eState::Jump;
		}
	}
	void PlayerScript::walk()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		if (!rb) return;

		float walkSpeed = 150.0f;
		Vector2 velocity = rb->GetVelocity();

		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			velocity.x = walkSpeed;

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = eState::Run;
				return;
			}
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			velocity.x = -walkSpeed;

			if (Input::GetKeyDown(eKeyCode::C))
			{
				mState = eState::Run;
				return;
			}
		}
		else
		{
			velocity.x = 0.0f;
			mState = eState::Stand;
		}

		rb->SetVelocity(velocity);

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eState::Crouch;
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			initJump();
			mState = eState::Jump;
			return;
		}
	}
	void PlayerScript::run()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		if (!rb) return;

		float runSpeed = 250.0f;
		Vector2 velocity = rb->GetVelocity();

		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			velocity.x = runSpeed;

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				return;
			}
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			velocity.x = -runSpeed;

			if (Input::GetKeyUp(eKeyCode::C))
			{
				mState = PlayerScript::eState::Walk;
				return;
			}
		}
		else
		{
			velocity.x = 0.0f;
			mState = eState::Stand;
		}

		rb->SetVelocity(velocity);

		if (Input::GetKeyDown(eKeyCode::X)) // 점프 키를 누르는 순간
		{
			initJump();
			mState = eState::Jump;
			return;
		}
	}

	void PlayerScript::jump()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		Vector2 velocity = rb->GetVelocity();
		float airSpeed = 150.0f;

		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			velocity.x = airSpeed;
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			velocity.x = -airSpeed;
		}
		else
		{
			velocity.x = 0.0f;
		}

		// 가변 점프: 키를 떼면 상승 속도를 줄여서 살짝 점프하게 함
		if (Input::GetKeyUp(eKeyCode::X))
		{
			if (velocity.y < 0.0f)
			{
				velocity.y *= 0.4f;
			}
		}

		rb->SetVelocity(velocity);

		if (rb->GetVelocity().y > 0.0f)
		{
			mState = eState::Fall;
		}
	}

	void PlayerScript::fall()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		Vector2 velocity = rb->GetVelocity();
		float airSpeed = 150.0f;

		// 공중 좌우 이동
		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			velocity.x = airSpeed;
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			velocity.x = -airSpeed;
		}
		else
		{
			velocity.x = 0.0f;
		}

		rb->SetVelocity(velocity);

		if (rb->GetGround())
		{
			mState = eState::Stand;
		}
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
		if (Input::GetKeyUp(eKeyCode::V))
		{
			mState = eState::Stand;
			return;
		}

		// 2. 흡입 범위 설정 (커비의 위치와 방향 기준)
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// 흡입 중심점 (커비의 앞쪽)
		float inhaleDist = 100.0f;
		Vector2 inhaleCenter = pos;
		inhaleCenter.x += (mDir == eDirection::Right) ? inhaleDist : -inhaleDist;
		
		const std::vector<GameObject*>& monsters = SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster)->GetGameObjects();

		for (GameObject* monster : monsters)
		{
			Transform* monTr = monster->GetComponent<Transform>();
			Vector2 monPos = monTr->GetPosition();

			float dist = (inhaleCenter - monPos).length();

			// 4. 흡입 범위(예: 150 픽셀) 안에 있다면 끌어당기기
			if (dist < 150.0f)
			{
				pullMonster(monster, pos);
			}
		}
	}

	void PlayerScript::full()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float moveSpeed = 100.0f; // 평소(150.0f)보다 느리게 설정

		// 좌우 이동은 가능하지만, 점프나 대시는 제한할 수 있습니다.
		if (Input::GetKey(eKeyCode::Right))
		{
			mDir = eDirection::Right;
			pos.x += moveSpeed * Time::DT();
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			mDir = eDirection::Left;
			pos.x -= moveSpeed * Time::DT();
		}

		// 공격(별 발사) 또는 삼키기
		if (Input::GetKeyDown(eKeyCode::V)) // 다시 V를 누르면 발사!
		{
			mState = eState::Attack;
		}

		// 아래 키를 누르면 능력을 카피하거나 그냥 삼킴 (선택 사항)
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eState::Stand; // 능력이 없다면 그냥 일반 상태로
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::attack()
	{
		// 1. 별 오브젝트 생성 (Instantiate)
	// 이 부분은 작성하신 AttackEffect() 로직을 응용하면 됩니다.
	// 예: Star* star = object::Instantiate<Star>(eLayerType::PlayerProjectile);

	// 2. 애니메이션이 한 번 재생 완료되면 다시 Stand로
		if (mAnimator->IsComplete())
		{
			mState = eState::Stand;
		}
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

		if (mPrevState != mState || mPrevDir != mDir)
		{
			bool loop = true;

			if (mState == eState::Attack || mState == eState::Hit || mState == eState::Slide)
				loop = false;

			mAnimator->PlayAnimation(animName, loop);

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

	void PlayerScript::initJump()
	{
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		if (rb)
		{
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);

			rb->SetGround(false);
		}
	}

	void PlayerScript::pullMonster(GameObject* monster, Vector2 playerPos)
	{
		Transform* monTr = monster->GetComponent<Transform>();
		Vector2 monPos = monTr->GetPosition();

		Vector2 dir = playerPos - monPos;
		float dist = dir.length();

		if (dist < 20.0f)
		{
			eatMonster(monster);
			return;
		}

		dir = dir.normalize();
		monPos += dir * 300.0f * Time::DT();
		monTr->SetPosition(monPos);

	}

	void PlayerScript::eatMonster(GameObject* monster)
	{
		monster->SetActive(false);

		mState = eState::Full;
	}

}