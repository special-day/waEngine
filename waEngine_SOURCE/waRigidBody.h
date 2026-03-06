#pragma once
#include "waComponent.h"

namespace wa
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force) { mForce = force; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetGround(bool ground) { mbGround = ground; }
		Vector2 GetVelocity() { return mVelocity; }
		bool GetGround() { return mbGround; }

	private:
		void applyFriction();
		void limitVelocity();

	private:
		float mMass;
		float mFriction;
		float mGravity;
		float mMaxVelocity;
		bool mbGround;

		Vector2 mForce;
		Vector2 mAccel;
		Vector2 mVelocity;
	};

}
