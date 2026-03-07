#pragma once
#include "..\\waEngine_SOURCE\\\waScript.h"

namespace wa
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Stand, Walk, Run, Jump, Fall,
			Crouch, Slide, Inhale, Full, Attack, Hit
		};

		enum class eDirection {Left, Right};


		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void AttackEffect();

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

	private:
		void stand();
		void walk();
		void run();
		void jump();
		void fall();
		void crouch();
		void slide();
		void inhale();
		void full();
		void attack();
		void hit();

		void updateAnimation();
		void updateCollider();
		void initJump();
		void pullMonster(GameObject* monster, Vector2 playerPos);
		void eatMonster(GameObject* monster);

	private:
		eState mState;
		eState mPrevState;
		eDirection mDir;
		eDirection mPrevDir;
		class Animator* mAnimator;

		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}