#include "waRigidBody.h"
#include "waTime.h"
#include "waTransform.h"
#include "waGameObject.h"
#include "waTexture.h"
#include "waSceneManager.h"
#include "waScene.h"

namespace wa
{
	RigidBody::RigidBody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mGravity(300.0f)
		, mbGround(false)
		, mMaxVelocity(300.0f)
		, mForce(Vector2::Zero)
		, mAccel(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
	}
	RigidBody::~RigidBody()
	{
	}
	void RigidBody::Initialize()
	{
	}
	void RigidBody::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// F = ma
		mAccel = mForce / mMass;
		if (!mbGround) mAccel.y += mGravity;

		mVelocity += mAccel * Time::DT();

		if (mbGround && abs(mVelocity.x) > 0.0f)
		{
			applyFriction();
		}

		limitVelocity();

		Vector2 nextPos = pos + mVelocity * Time::DT();

		graphics::Texture* colMap = SceneManager::GetActiveScene()->GetColMap();

		if (colMap)
		{
			// 이동하려는 옆면에 벽이 있는지 확인
			float sideX = (mVelocity.x >= 0) ? nextPos.x + 20 : nextPos.x - 20;
			if (colMap->GetPixel((int)sideX, (int)pos.y) == RGB(0, 0, 0))
			{
				nextPos.x = pos.x; // 벽이 있으면 X이동 차단
				mVelocity.x = 0;
			}

			// 이동하려는 아래에 바닥이 있는지 확인
			int footX = (int)nextPos.x;
			int footY = (int)nextPos.y + 10; // 발바닥 오프셋

			if (colMap->GetPixel(footX, footY) == RGB(0, 0, 0))
			{
				// 하강 중일 때만 바닥에 붙이기 (점프 중일 땐 통과)
				if (mVelocity.y >= 0)
				{
					mbGround = true;
					mVelocity.y = 0;

					// 땅 위로 위치 고정
					while (colMap->GetPixel(footX, footY - 1) == RGB(0, 0, 0))
					{
						footY--;
					}
					nextPos.y = (float)(footY - 20);
				}
			}
			else
			{
				mbGround = false;
			}
		}

		pos += mVelocity * Time::DT();
		tr->SetPosition(pos);

		mForce.clear();
	}
	void RigidBody::LateUpdate()
	{
	}
	void RigidBody::Render(HDC hdc)
	{
	}

	void RigidBody::applyFriction()
	{
		// X축 마찰력만 계산
		if (abs(mVelocity.x) > 0.1f)
		{
			float frictionDir = (mVelocity.x > 0) ? -1.0f : 1.0f;
			float frictionForce = mFriction * mMass * Time::DT();

			if (abs(mVelocity.x) <= frictionForce)
				mVelocity.x = 0.0f;
			else
				mVelocity.x += frictionDir * frictionForce;
		}
	}

	void RigidBody::limitVelocity()
	{
		if (mVelocity.length() > mMaxVelocity)
		{
			mVelocity = mVelocity.normalize() * mMaxVelocity;
		}
	}


}