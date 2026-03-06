#include "waRigidBody.h"
#include "waTime.h"
#include "waTransform.h"
#include "waGameObject.h"

namespace wa
{
	RigidBody::RigidBody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mGravity(9.8f)
		, mbGround(false)
		, mMaxVelocity(10.0f)
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
		// f = ma
		mAccel = mForce / mMass;
		if (!mbGround) mAccel.y += mGravity;

		mVelocity += mAccel * Time::DT();

		if (mbGround && abs(mVelocity.x) > 0.0f)
		{
			applyFriction();
		}

		limitVelocity();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
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