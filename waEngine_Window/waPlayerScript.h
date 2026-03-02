#pragma once
#include "..\\waEngine_SOURCE\\\waScript.h"

namespace wa
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Stand,
			Walk,
			Run,
			Crouch,
			Slide,
		};


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
		void slide();
		void attack();


	private:
		eState mState;
		class Animator* mAnimator;

		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}